 /*
 * Copyright (c) 2018 Samsung Electronics Co., Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <glib.h>
#include <Ecore.h>
#include <tizen.h>
#include <service_app.h>
#include <camera.h>
#include <mv_common.h>
#include <pthread.h>
#include "wiring.h"
#include "controller.h"
#include "controller_mv.h"
#include "controller_image.h"
#include "log.h"
#include "resource_camera.h"
#include "switch.h"
#include "servo-h.h"
#include "servo-v.h"
#include "servo-type.h"
#include "motion.h"
#include "st_thing_master.h"
#include "st_thing_resource.h"
#include "dht.h"

#define CAMERA_MOVE_INTERVAL_MS 150    //450
#define THRESHOLD_VALID_EVENT_COUNT 5  //2
#define VALID_EVENT_INTERVAL_MS 100    //200

#define IMAGE_FILE_PREFIX "CAM_"
#define EVENT_INTERVAL_SECOND 0.5f

#define DHT_pin	46
#define LED		26

//#define TEMP_IMAGE_FILENAME "/opt/usr/home/owner/apps_rw/org.tizen.smart-surveillance-camera/shared/data/tmp.jpg"
//#define LATEST_IMAGE_FILENAME "/opt/usr/home/owner/apps_rw/org.tizen.smart-surveillance-camera/shared/data/latest.jpg"

// #define ENABLE_SMARTTHINGS
#define APP_CALLBACK_KEY "controller"

typedef struct app_data_s {
	double current_servo_x;
	double current_servo_y;
	int motion_state;

	long long int last_moved_time;
	long long int last_valid_event_time;
	int valid_vision_result_x_sum;
	int valid_vision_result_y_sum;
	int valid_event_count;

	unsigned int latest_image_width;
	unsigned int latest_image_height;
	char *latest_image_info;
	int latest_image_type; // 0: image during camera repositioning, 1: single valid image but not completed, 2: fully validated image
	unsigned char *latest_image_buffer;

	Ecore_Thread *image_writter_thread;
	pthread_mutex_t mutex;

	char* temp_image_filename;
	char* latest_image_filename;
} app_data;

static long long int __get_monotonic_ms(void)
{
	long long int ret_time = 0;
	struct timespec time_s;

	if (0 == clock_gettime(CLOCK_MONOTONIC, &time_s))
		ret_time = time_s.tv_sec* 1000 + time_s.tv_nsec / 1000000;
	else
		_E("Failed to get time");

	return ret_time;
}

static mv_colorspace_e __convert_colorspace_from_cam_to_mv(camera_pixel_format_e format)
{
	mv_colorspace_e colorspace = MEDIA_VISION_COLORSPACE_INVALID;
	switch (format) {
	case CAMERA_PIXEL_FORMAT_NV12:
		colorspace = MEDIA_VISION_COLORSPACE_NV12;
		break;
	case CAMERA_PIXEL_FORMAT_NV21:
		colorspace = MEDIA_VISION_COLORSPACE_NV21;
		break;
	case CAMERA_PIXEL_FORMAT_YUYV:
		colorspace = MEDIA_VISION_COLORSPACE_YUYV;
		break;
	case CAMERA_PIXEL_FORMAT_UYVY:
		colorspace = MEDIA_VISION_COLORSPACE_UYVY;
		break;
	case CAMERA_PIXEL_FORMAT_422P:
		colorspace = MEDIA_VISION_COLORSPACE_422P;
		break;
	case CAMERA_PIXEL_FORMAT_I420:
		colorspace = MEDIA_VISION_COLORSPACE_I420;
		break;
	case CAMERA_PIXEL_FORMAT_YV12:
		colorspace = MEDIA_VISION_COLORSPACE_YV12;
		break;
	case CAMERA_PIXEL_FORMAT_RGB565:
		colorspace = MEDIA_VISION_COLORSPACE_RGB565;
		break;
	case CAMERA_PIXEL_FORMAT_RGB888:
		colorspace = MEDIA_VISION_COLORSPACE_RGB888;
		break;
	case CAMERA_PIXEL_FORMAT_RGBA:
		colorspace = MEDIA_VISION_COLORSPACE_RGBA;
		break;
	case CAMERA_PIXEL_FORMAT_NV12T:
	case CAMERA_PIXEL_FORMAT_NV16:
	case CAMERA_PIXEL_FORMAT_ARGB:
	case CAMERA_PIXEL_FORMAT_JPEG:
	case CAMERA_PIXEL_FORMAT_H264:
	case CAMERA_PIXEL_FORMAT_INVALID:
	default :
		colorspace = MEDIA_VISION_COLORSPACE_INVALID;
		_E("unsupported format : %d", format);
		break;
	}

	return colorspace;
}

static void __thread_write_image_file(void *data, Ecore_Thread *th)
{
	app_data *ad = (app_data *)data;
	unsigned int width = 0;
	unsigned int height = 0;
	unsigned char *buffer = 0;
	char *image_info = NULL;
	int ret = 0;

	pthread_mutex_lock(&ad->mutex);
	width = ad->latest_image_width;
	height = ad->latest_image_height;
	buffer = ad->latest_image_buffer;
	ad->latest_image_buffer = NULL;
	if (ad->latest_image_info) {
		image_info = ad->latest_image_info;
		ad->latest_image_info = NULL;
	} else {
		image_info = strdup("00");
	}
	pthread_mutex_unlock(&ad->mutex);

	ret = controller_image_save_image_file(ad->temp_image_filename, width, height, buffer, image_info, strlen(image_info));
	if (ret) {
		_E("failed to save image file");
	} else {
		ret = rename(ad->temp_image_filename, ad->latest_image_filename);
		if (ret != 0 )
			_E("Rename fail");
	}
	free(image_info);
	free(buffer);
}

static void __thread_end_cb(void *data, Ecore_Thread *th)
{
	app_data *ad = (app_data *)data;

	pthread_mutex_lock(&ad->mutex);
	ad->image_writter_thread = NULL;
	pthread_mutex_unlock(&ad->mutex);
}

static void __thread_cancel_cb(void *data, Ecore_Thread *th)
{
	app_data *ad = (app_data *)data;
	unsigned char *buffer = NULL;

	_E("Thread %p got cancelled.\n", th);
	pthread_mutex_lock(&ad->mutex);
	buffer = ad->latest_image_buffer;
	ad->latest_image_buffer = NULL;
	ad->image_writter_thread = NULL;
	pthread_mutex_unlock(&ad->mutex);

	free(buffer);
}

static void __copy_image_buffer(image_buffer_data_s *image_buffer, app_data *ad)
{
	unsigned char *buffer = NULL;

	pthread_mutex_lock(&ad->mutex);
	ad->latest_image_height = image_buffer->image_height;
	ad->latest_image_width = image_buffer->image_width;

	buffer = ad->latest_image_buffer;
	ad->latest_image_buffer = image_buffer->buffer;
	pthread_mutex_unlock(&ad->mutex);

	free(buffer);
}

static void __preview_image_buffer_created_cb(void *data)
{
	image_buffer_data_s *image_buffer = data;
	app_data *ad = (app_data *)image_buffer->user_data;
	mv_source_h source = NULL;
	mv_colorspace_e image_colorspace = MEDIA_VISION_COLORSPACE_INVALID;
	switch_state_e switch_state = SWITCH_STATE_OFF;
	char *info = NULL;

	ret_if(!image_buffer);
	ret_if(!ad);

	image_colorspace = __convert_colorspace_from_cam_to_mv(image_buffer->format);
	goto_if(image_colorspace == MEDIA_VISION_COLORSPACE_INVALID, FREE_ALL_BUFFER);

	__copy_image_buffer(image_buffer, ad);

	switch_state_get(&switch_state);
	if (switch_state == SWITCH_STATE_OFF) { /* SWITCH_STATE_OFF means automatic mode */
		source = controller_mv_create_source(image_buffer->buffer,
					image_buffer->buffer_size, image_buffer->image_width,
					image_buffer->image_height, image_colorspace);
	}

	pthread_mutex_lock(&ad->mutex);
	info = ad->latest_image_info;
	ad->latest_image_info = NULL;
	pthread_mutex_unlock(&ad->mutex);
	free(info);

	if (source)
		controller_mv_push_source(source);

	free(image_buffer);

	motion_state_set(ad->motion_state, APP_CALLBACK_KEY);
	ad->motion_state = 0;
	digitalWrite(LED, ad->motion_state);

	pthread_mutex_lock(&ad->mutex);
	if (!ad->image_writter_thread) {
		ad->image_writter_thread = ecore_thread_run(__thread_write_image_file, __thread_end_cb, __thread_cancel_cb, ad);
	} else {
		_E("Thread is running NOW");
	}
	pthread_mutex_unlock(&ad->mutex);

	return;

FREE_ALL_BUFFER:
	free(image_buffer->buffer);
	free(image_buffer);
}

static void __move_camera(int x, int y, void *user_data)
{
	app_data *ad = (app_data *)user_data;
	ret_if(!ad);

	// x, y Range : -10 ~ 10
	if (x > 20) x = 20;
	if (x < -20) x = -20;
	//if (y > 10) y = 10;
	//if (y < -10) y = -10;

	x *= -1; // The camera image is flipped left and right.
	double calculated_x = ad->current_servo_x + x * SERVO_MOTOR_HORIZONTAL_STEP;
	//double calculated_y = ad->current_servo_y + y * SERVO_MOTOR_VERTICAL_STEP;

	if (calculated_x > SERVO_MOTOR_HORIZONTAL_MAX)
		calculated_x = SERVO_MOTOR_HORIZONTAL_MAX;

	if (calculated_x < SERVO_MOTOR_HORIZONTAL_MIN)
		calculated_x = SERVO_MOTOR_HORIZONTAL_MIN;

	//if (calculated_y > SERVO_MOTOR_VERTICAL_MAX)
	//	calculated_y = SERVO_MOTOR_VERTICAL_MAX;

	//if (calculated_y < SERVO_MOTOR_VERTICAL_MIN)
	//	calculated_y = SERVO_MOTOR_VERTICAL_MIN;

	ad->current_servo_x = calculated_x;
	//ad->current_servo_y = calculated_y;



	servo_h_state_set(calculated_x, APP_CALLBACK_KEY);

	if((ad->motion_state)==1)
		servo_v_state_set(SERVO_MOTOR_VERTICAL_MAX, APP_CALLBACK_KEY);
	//else
		//servo_v_state_set(SERVO_MOTOR_VERTICAL_MIN, APP_CALLBACK_KEY);
	//servo_v_state_set(calculated_y, APP_CALLBACK_KEY);

	return;
}

static void __set_result_info(int result[], int result_count, app_data *ad, int image_result_type)
{
	char image_info[IMAGE_INFO_MAX + 1] = {'\0', };
	char *current_position;
	int current_index = 0;
	int string_count = 0;
	int i = 0;
	char *latest_image_info = NULL;
	char *info = NULL;

	current_position = image_info;

	current_position += snprintf(current_position, IMAGE_INFO_MAX, "%02d", image_result_type);
	string_count += 2;

	current_position += snprintf(current_position, IMAGE_INFO_MAX - string_count, "%02d", result_count);
	string_count += 2;

	for (i = 0; i < result_count; i++) {
		current_index = i * 4;
		if (IMAGE_INFO_MAX - string_count < 8)
			break;

		current_position += snprintf(current_position, IMAGE_INFO_MAX - string_count, "%02d%02d%02d%02d"
			, result[current_index], result[current_index + 1], result[current_index + 2], result[current_index + 3]);
		string_count += 8;
	}

	latest_image_info = strdup(image_info);
	pthread_mutex_lock(&ad->mutex);
	info = ad->latest_image_info;
	ad->latest_image_info = latest_image_info;
	pthread_mutex_unlock(&ad->mutex);
	free(info);
}

static void __mv_detection_event_cb(int horizontal, int vertical, int result[], int result_count, void *user_data)
{
	app_data *ad = (app_data *)user_data;
	long long int now = __get_monotonic_ms();

	ad->motion_state = 1;
	digitalWrite(LED, ad->motion_state);

	if (now < ad->last_moved_time + CAMERA_MOVE_INTERVAL_MS) {
		ad->valid_event_count = 0;
		pthread_mutex_lock(&ad->mutex);
		ad->latest_image_type = 0; // 0: image during camera repositioning
		pthread_mutex_unlock(&ad->mutex);
		__set_result_info(result, result_count, ad, 0);
		return;
	}

	if (now < ad->last_valid_event_time + VALID_EVENT_INTERVAL_MS) {
		ad->valid_event_count++;
	} else {
		ad->valid_event_count = 1;
	}

	ad->last_valid_event_time = now;

	if (ad->valid_event_count < THRESHOLD_VALID_EVENT_COUNT) {
		ad->valid_vision_result_x_sum += horizontal;
		ad->valid_vision_result_y_sum += vertical;
		pthread_mutex_lock(&ad->mutex);
		ad->latest_image_type = 1; // 1: single valid image but not completed
		pthread_mutex_unlock(&ad->mutex);
		__set_result_info(result, result_count, ad, 1);
		return;
	}

	ad->valid_event_count = 0;
	ad->valid_vision_result_x_sum += horizontal;
	ad->valid_vision_result_y_sum += vertical;

	int x = ad->valid_vision_result_x_sum / THRESHOLD_VALID_EVENT_COUNT;
	int y = ad->valid_vision_result_y_sum / THRESHOLD_VALID_EVENT_COUNT;

	x = 10 * x / (IMAGE_WIDTH / 2);
	y = 10 * y / (IMAGE_HEIGHT / 2);

	__move_camera((int) x, (int) y, ad);
	ad->last_moved_time = now;

	ad->valid_vision_result_x_sum = 0;
	ad->valid_vision_result_y_sum = 0;
	pthread_mutex_lock(&ad->mutex);
	ad->latest_image_type = 2; // 2: fully validated image
	pthread_mutex_unlock(&ad->mutex);

	__set_result_info(result, result_count, ad, 2);
}

static void __switch_changed(switch_state_e state, void* user_data)
{
	app_data *ad = (app_data *)user_data;
	_D("switch changed to - %d", state);
	ret_if(!ad);

	/* Move servo motors to initial position */
	if (state != SWITCH_STATE_ON)
		return;

	ad->current_servo_x = SERVO_MOTOR_HORIZONTAL_CENTER;
	ad->current_servo_y = SERVO_MOTOR_VERTICAL_CENTER;

	servo_h_state_set(ad->current_servo_x, APP_CALLBACK_KEY);
	servo_v_state_set(ad->current_servo_y, APP_CALLBACK_KEY);
}

static void __servo_v_changed(double value, void* user_data)
{
	app_data *ad = (app_data *)user_data;
	ret_if(!ad);

	_D("servo_v changed to - %lf", value);
	ad->current_servo_y = value;
}

static void __servo_h_changed(double value, void* user_data)
{
	app_data *ad = (app_data *)user_data;
	ret_if(!ad);

	_D("servo_h changed to - %lf", value);
	ad->current_servo_x = value;
}

static void __device_interfaces_fini(void)
{
	switch_finalize();
	servo_v_finalize();
	servo_h_finalize();
	motion_finalize();
}

static int __device_interfaces_init(app_data *ad)
{
	retv_if(!ad, -1);

	if (switch_initialize()) {
		_E("failed to switch_initialize()");
		return -1;
	}

	if (servo_v_initialize()) {
		_E("failed to servo_v_initialize()");
		goto ERROR;
	}

	if (servo_h_initialize()) {
		_E("failed to servo_h_initialize()");
		goto ERROR;
	}

	if (motion_initialize()) {
		_E("failed to motion_initialize()");
		goto ERROR;
	}

	switch_state_changed_cb_set(APP_CALLBACK_KEY, __switch_changed, ad);
	//servo_v_state_changed_cb_set(APP_CALLBACK_KEY, __servo_v_changed, ad);
	servo_h_state_changed_cb_set(APP_CALLBACK_KEY, __servo_h_changed, ad);
	// motion : only set result value, callback is not needed

	return 0;

ERROR :
	__device_interfaces_fini();
	return -1;
}

/*static inline int16_t dhtproc(dht_request_t req, uint16_t arg){
	switch(req){
		case DHT_READ_PIN:
			pinMode(DHT_pin, INPUT);
			return digitalRead(DHT_pin);
			break;
		case DHT_WRITE_PIN:
			pinMode(DHT_pin, OUTPUT);
			digitalWrite(DHT_pin, arg);
			return 0;
			break;
		case DHT_DELAY_MS:
			while(arg--) {
				delay(1);
			}
			break;
		case DHT_DELAY_US:
			while(arg--) {
				delayMicroseconds(1);
			}
			break;
		default:
			return -1;
	}
	return 0;
}*/

static bool service_app_create(void *data)
{
	app_data *ad = (app_data *)data;


	char* shared_data_path = app_get_shared_data_path();
	if (shared_data_path == NULL) {
		_E("Failed to get shared data path");
		goto ERROR;
	}
	ad->temp_image_filename = g_strconcat(shared_data_path, "tmp.jpg", NULL);
	ad->latest_image_filename = g_strconcat(shared_data_path, "latest.jpg", NULL);
	free(shared_data_path);

	_D("%s", ad->temp_image_filename);
	_D("%s", ad->latest_image_filename);

	controller_image_initialize();

	pthread_mutex_init(&ad->mutex, NULL);

	if (__device_interfaces_init(ad))
		goto ERROR;

	if (controller_mv_set_movement_detection_event_cb(__mv_detection_event_cb, data) == -1) {
		_E("Failed to set movement detection event callback");
		goto ERROR;
	}

	if (resource_camera_init(__preview_image_buffer_created_cb, ad) == -1) {
		_E("Failed to init camera");
		goto ERROR;
	}

	if (resource_camera_start_preview() == -1) {
		_E("Failed to start camera preview");
		goto ERROR;
	}

	/*if (DHT_Read11(&dht) == -1) {
		_E("Failed to read DHT");
		//goto ERROR;
	}*/

#ifdef ENABLE_SMARTTHINGS
	/* smartthings APIs should be called after camera start preview, they can't wait to start camera */
	if (st_thing_master_init())
		goto ERROR;

	if (st_thing_resource_init())
		goto ERROR;
#endif /* ENABLE_SMARTTHINGS */

	ad->current_servo_x = SERVO_MOTOR_HORIZONTAL_CENTER;
	//ad->current_servo_y = SERVO_MOTOR_VERTICAL_CENTER;

	servo_h_state_set(ad->current_servo_x, APP_CALLBACK_KEY);
	servo_v_state_set(SERVO_MOTOR_VERTICAL_MIN, APP_CALLBACK_KEY);

	return true;

ERROR:
	__device_interfaces_fini();

	resource_camera_close();
	controller_mv_unset_movement_detection_event_cb();
	controller_image_finalize();

#ifdef ENABLE_SMARTTHINGS
	st_thing_master_fini();
	st_thing_resource_fini();
#endif /* ENABLE_SMARTTHINGS */

	pthread_mutex_destroy(&ad->mutex);

	return false;
}

static void service_app_terminate(void *data)
{
	app_data *ad = (app_data *)data;
	Ecore_Thread *thread_id = NULL;
	unsigned char *buffer = NULL;
	char *info = NULL;
	gchar *temp_image_filename;
	gchar *latest_image_filename;
	_D("App Terminated - enter");

	resource_camera_close();
	controller_mv_unset_movement_detection_event_cb();

	pthread_mutex_lock(&ad->mutex);
	thread_id = ad->image_writter_thread;
	ad->image_writter_thread = NULL;
	pthread_mutex_unlock(&ad->mutex);

	if (thread_id)
		ecore_thread_wait(thread_id, 3.0); // wait for 3 second

	__device_interfaces_fini();

	controller_image_finalize();

#ifdef ENABLE_SMARTTHINGS
	st_thing_master_fini();
	st_thing_resource_fini();
#endif /* ENABLE_SMARTTHINGS */

	pthread_mutex_lock(&ad->mutex);
	buffer = ad->latest_image_buffer;
	ad->latest_image_buffer = NULL;
	info  = ad->latest_image_info;
	ad->latest_image_info = NULL;
	temp_image_filename = ad->temp_image_filename;
	ad->temp_image_filename = NULL;
	latest_image_filename = ad->latest_image_filename;
	ad->latest_image_filename = NULL;
	pthread_mutex_unlock(&ad->mutex);
	free(buffer);
	free(info);
	g_free(temp_image_filename);
	g_free(latest_image_filename);

	pthread_mutex_destroy(&ad->mutex);
	free(ad);
	_D("App Terminated - leave");
}

static void service_app_control(app_control_h app_control, void *data)
{
	/* APP_CONTROL */
}

int main(int argc, char* argv[])
{
	app_data *ad = NULL;

	//servo_v_state_set(SERVO_MOTOR_VERTICAL_MIN, APP_CALLBACK_KEY);

	/*dht_t dht;

	DHT_Init(&dht, dhtproc);
	DHT_Read11(&dht);
	if(((int)dht.temperature * 100)>20.0)
		servo_v_state_set(SERVO_MOTOR_VERTICAL_MAX, APP_CALLBACK_KEY);
	else
		servo_v_state_set(SERVO_MOTOR_VERTICAL_MIN, APP_CALLBACK_KEY);*/

	int ret = 0;
	service_app_lifecycle_callback_s event_callback;

	ad = calloc(1, sizeof(app_data));
	retv_if(!ad, -1);

	event_callback.create = service_app_create;
	event_callback.terminate = service_app_terminate;
	event_callback.app_control = service_app_control;


	ret = service_app_main(argc, argv, &event_callback, ad);

	return ret;
}
