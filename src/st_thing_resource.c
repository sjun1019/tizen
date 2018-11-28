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

#include <smartthings_resource.h>
#include <smartthings_payload.h>
#include <glib.h>
#include "log.h"
#include "switch.h"
#include "servo-h.h"
#include "servo-v.h"
#include "motion.h"

// switch
#define URI_SWITCH "/capability/switch/main/0"
#define KEY_SWITCH "power"
#define VALUE_SWITCH_ON "on"
#define VALUE_SWITCH_OFF "off"

// volume - servo v
#define URI_AUDIOVOLUME "/capability/audioVolume/main/0"
#define KEY_VOLUME "volume"
#define KEY_MUTE "mute"

// dim switch - servo h
#define URI_SWITCHLEVEL "/capability/switchLevel/main/0"
#define KEY_SWITCHLEVEL "dimmingSetting"

// motion
#define URI_MOTION "/capability/motionSensor/main/0"
#define KEY_MOTION "value"

#define RESOURCE_CALLBACK_KEY "st_thing_resource"

static smartthings_resource_h g_st_res_h;
static smartthings_resource_connection_status_e g_conn_status =
		SMARTTHINGS_RESOURCE_CONNECTION_STATUS_DISCONNECTED;


static const char *
__resource_error_to_str(smartthings_resource_error_e error)
{
	const char *err_str = NULL;

	switch (error) {
	case SMARTTHINGS_RESOURCE_ERROR_NONE:
		err_str = "SMARTTHINGS_RESOURCE_ERROR_NONE";
		break;
	case SMARTTHINGS_RESOURCE_ERROR_INVALID_PARAMETER:
		err_str = "SMARTTHINGS_RESOURCE_ERROR_INVALID_PARAMETER";
		break;
	case SMARTTHINGS_RESOURCE_ERROR_OUT_OF_MEMORY:
		err_str = "SMARTTHINGS_RESOURCE_ERROR_OUT_OF_MEMORY";
		break;
	case SMARTTHINGS_RESOURCE_ERROR_PERMISSION_DENIED:
		err_str = "SMARTTHINGS_RESOURCE_ERROR_PERMISSION_DENIED";
		break;
	case SMARTTHINGS_RESOURCE_ERROR_NO_DATA:
		err_str = "SMARTTHINGS_RESOURCE_ERROR_NO_DATA";
		break;
	case SMARTTHINGS_RESOURCE_ERROR_NOT_SUPPORTED:
		err_str = "SMARTTHINGS_RESOURCE_ERROR_NOT_SUPPORTED";
		break;
	case SMARTTHINGS_RESOURCE_ERROR_OPERATION_FAILED:
		err_str = "SMARTTHINGS_RESOURCE_ERROR_NOT_SUPPORTED";
		break;
	case SMARTTHINGS_RESOURCE_ERROR_SERVICE_UNAVAILABLE:
		err_str = "SMARTTHINGS_RESOURCE_ERROR_SERVICE_UNAVAILABLE";
		break;
	default:
		err_str = "Unknown error";
		break;
	}

	return err_str;
}

/* get and set request handlers */
static bool
handle_get_motion(smartthings_payload_h resp_payload, void *user_data)
{
	int state = 0;

	motion_state_get(&state);

	_D("GET request for motion : %d", state);
	smartthings_payload_set_bool(resp_payload, KEY_MOTION, state ? true : false);

	return true;
}

static bool
handle_set_motion(smartthings_payload_h payload,
	smartthings_payload_h resp_payload, void *user_data)
{
	bool bvalue = 0;

	if (smartthings_payload_get_bool(payload, KEY_MOTION, &bvalue) == 0) {
		_D("requested volume: [%d]", bvalue);
		motion_state_set((int)bvalue, RESOURCE_CALLBACK_KEY);
		smartthings_payload_set_bool(resp_payload, KEY_MOTION, bvalue);
	}

	return true;
}

static bool
handle_get_switch(smartthings_payload_h resp_payload, void *user_data)
{
	switch_state_e state = SWITCH_STATE_OFF;
	const char *switch_state_name = NULL;

	switch_state_get(&state);

	if (state == SWITCH_STATE_OFF)
		switch_state_name = VALUE_SWITCH_OFF;
	else
		switch_state_name = VALUE_SWITCH_ON;

	_D("GET request for switch : %s", switch_state_name);
	smartthings_payload_set_string(resp_payload, KEY_SWITCH, switch_state_name);

	return true;
}

static bool
handle_set_switch(smartthings_payload_h payload,
	smartthings_payload_h resp_payload, void *user_data)
{
	char *str_value = NULL;
	switch_state_e state = SWITCH_STATE_OFF;

	if (smartthings_payload_get_string(payload, KEY_SWITCH, &str_value) != 0) {
		_E("failed to smartthings_payload_get_string()");
		return false;
	}
	retv_if(!str_value, false);

	_D("SET request for switch: [%s]", str_value);

	if (0 == g_strcmp0(str_value, VALUE_SWITCH_ON))
		state = SWITCH_STATE_ON;

	switch_state_set(state, RESOURCE_CALLBACK_KEY);

	smartthings_payload_set_string(resp_payload, KEY_SWITCH, str_value);
	free(str_value);

	return true;
}

static bool
handle_get_audiovolume(smartthings_payload_h resp_payload, void *user_data)
{
	double value = 0.0f;

	servo_v_state_get(&value);

	_D("current volume: [%f]", value);
	smartthings_payload_set_int(resp_payload, KEY_VOLUME, (int)value);
	smartthings_payload_set_bool(resp_payload, KEY_MUTE, false);

	return true;
}

static bool
handle_set_audiovolume(smartthings_payload_h payload,
	smartthings_payload_h resp_payload, void *user_data)
{
	int ivalue = 0;

	if (smartthings_payload_get_int(payload, KEY_VOLUME, &ivalue) == 0) {
		_D("requested volume: [%d]", ivalue);
		servo_v_state_set((double)ivalue, RESOURCE_CALLBACK_KEY);
		smartthings_payload_set_int(resp_payload, KEY_VOLUME, ivalue);
	}

	smartthings_payload_set_bool(resp_payload, KEY_MUTE, false);

	return true;
}

static bool
handle_get_switchLevel(smartthings_payload_h resp_payload, void *user_data)
{

	double value = 0;

	servo_h_state_get(&value);

	_D("current switchLevel: [%f]", value);
	smartthings_payload_set_int(resp_payload, KEY_SWITCHLEVEL, (int)value);

	return true;

}

static bool
handle_set_switchLevel(smartthings_payload_h payload,
	smartthings_payload_h resp_payload, void *user_data)
{
	int ivalue = 0;

	if (smartthings_payload_get_int(payload, KEY_SWITCHLEVEL, &ivalue) == 0) {
		_D("requested dimming: [%d]", ivalue);
		servo_h_state_set((double)ivalue, RESOURCE_CALLBACK_KEY);
		smartthings_payload_set_int(resp_payload, KEY_SWITCHLEVEL, ivalue);
	}

	return true;
}

static void
_request_cb(smartthings_resource_h handle, int req_id,
	const char *uri, smartthings_resource_req_type_e req_type,
	smartthings_payload_h payload, void *user_data)
{
	smartthings_payload_h resp_payload = NULL;
	bool result = false;
	int error = SMARTTHINGS_RESOURCE_ERROR_NONE;

	_D("request on %s, type[%d], id[%d]", uri, req_type, req_id);

	smartthings_payload_create(&resp_payload);
	if (!resp_payload) {
		_E("Response payload is NULL");
		return;
	}

	if (req_type == SMARTTHINGS_RESOURCE_REQUEST_GET) {
		if (0 == g_strcmp0(uri, URI_SWITCH))
			result = handle_get_switch(resp_payload, user_data);
		else if (0 == g_strcmp0(uri, URI_AUDIOVOLUME))
			result = handle_get_audiovolume(resp_payload, user_data);
		else if (0 == g_strcmp0(uri, URI_SWITCHLEVEL))
			result = handle_get_switchLevel(resp_payload, user_data);
		else if (0 == g_strcmp0(uri, URI_MOTION))
			result = handle_get_motion(resp_payload, user_data);
		else
			_E("No matching Resource uri");
	} else if (req_type == SMARTTHINGS_RESOURCE_REQUEST_SET) {
		if (0 == g_strcmp0(uri, URI_SWITCH))
			result = handle_set_switch(payload, resp_payload, user_data);
		else if (0 == g_strcmp0(uri, URI_AUDIOVOLUME))
			result = handle_set_audiovolume(payload, resp_payload, user_data);
		else if (0 == g_strcmp0(uri, URI_SWITCHLEVEL))
			result = handle_set_switchLevel(payload, resp_payload, user_data);
		else if (0 == g_strcmp0(uri, URI_MOTION))
			result = handle_set_motion(payload, resp_payload, user_data);
		else
			_E("No matching Resource uri");
	} else {
		_E("Invalid request type - %d", req_type);
		smartthings_payload_destroy(resp_payload);
		return;
	}

	error = smartthings_resource_send_response(handle, req_id, uri, resp_payload, result);
	if (error != SMARTTHINGS_RESOURCE_ERROR_NONE) {
			smartthings_payload_destroy(resp_payload);
			_E("smartthings_resource_send_response() failed, [%s]",
				__resource_error_to_str(error));
			return;
	}

	if (req_type == SMARTTHINGS_RESOURCE_REQUEST_SET) {
			error = smartthings_resource_notify(handle, uri, resp_payload);
			if (error != SMARTTHINGS_RESOURCE_ERROR_NONE)
				_E("smartthings_resource_notify() failed, [%s]",
				__resource_error_to_str(error));
	}

	if (smartthings_payload_destroy(resp_payload))
		_E("smartthings_payload_destroy failed");

	return;
}

static void
_resource_connection_status_cb(smartthings_resource_error_e error,
	smartthings_resource_h handle,
	smartthings_resource_connection_status_e status, void *user_data)
{
	_D("result [%s], status=[%d]", __resource_error_to_str(error), status);

	g_conn_status = status;

	if (status == SMARTTHINGS_RESOURCE_CONNECTION_STATUS_CONNECTED) {
		if (smartthings_resource_set_request_cb(handle, _request_cb, NULL)) {
			_E("smartthings_resource_set_request_cb() is failed");
			return;
		}
	} else {
		_E("connection failed");
	}
	return;
}

static void __motion_changed(int value, void* user_data)
{
	smartthings_resource_h handle = user_data;
	smartthings_payload_h payload = NULL;
	int error = SMARTTHINGS_RESOURCE_ERROR_NONE;

	ret_if(!handle);

	_D("motion changed to - %d", value);

	ret_if(g_conn_status != SMARTTHINGS_RESOURCE_CONNECTION_STATUS_CONNECTED);

	smartthings_payload_create(&payload);
	if (!payload) {
		_E("failed to create payload is NULL");
		return;
	}

	smartthings_payload_set_bool(payload, KEY_MOTION, value ? true : false);

	error = smartthings_resource_notify(handle, URI_MOTION, payload);
	if (error != SMARTTHINGS_RESOURCE_ERROR_NONE)
		_E("smartthings_resource_notify() failed, [%s]",
			__resource_error_to_str(error));

	smartthings_payload_destroy(payload);
}

static void __switch_changed(switch_state_e state, void* user_data)
{
	smartthings_resource_h handle = user_data;
	smartthings_payload_h payload = NULL;
	int error = SMARTTHINGS_RESOURCE_ERROR_NONE;
	const char *switch_state_name = NULL;

	_D("switch changed to - %d", state);
	ret_if(!handle);
	ret_if(g_conn_status != SMARTTHINGS_RESOURCE_CONNECTION_STATUS_CONNECTED);

	smartthings_payload_create(&payload);
	if (!payload) {
		_E("failed to create payload is NULL");
		return;
	}

	if (state == SWITCH_STATE_OFF)
		switch_state_name = VALUE_SWITCH_OFF;
	else
		switch_state_name = VALUE_SWITCH_ON;

	smartthings_payload_set_string(payload, KEY_SWITCH, switch_state_name);

	error = smartthings_resource_notify(handle, URI_SWITCH, payload);
	if (error != SMARTTHINGS_RESOURCE_ERROR_NONE)
		_E("smartthings_resource_notify() failed, [%s]",
			__resource_error_to_str(error));

	smartthings_payload_destroy(payload);
}

static void __servo_v_changed(double value, void* user_data)
{
	smartthings_resource_h handle = user_data;
	smartthings_payload_h payload = NULL;
	int error = SMARTTHINGS_RESOURCE_ERROR_NONE;

	_D("servo_v changed to - %f", value);
	ret_if(!handle);
	ret_if(g_conn_status != SMARTTHINGS_RESOURCE_CONNECTION_STATUS_CONNECTED);

	smartthings_payload_create(&payload);
	if (!payload) {
		_E("failed to create payload is NULL");
		return;
	}

	smartthings_payload_set_int(payload, KEY_VOLUME, (int)value);

	error = smartthings_resource_notify(handle, URI_AUDIOVOLUME, payload);
	if (error != SMARTTHINGS_RESOURCE_ERROR_NONE)
		_E("smartthings_resource_notify() failed, [%s]",
			__resource_error_to_str(error));

	smartthings_payload_destroy(payload);
}

static void __servo_h_changed(double value, void* user_data)
{
	smartthings_resource_h handle = user_data;
	smartthings_payload_h payload = NULL;
	int error = SMARTTHINGS_RESOURCE_ERROR_NONE;

	_D("servo_h changed to - %f", value);
	ret_if(!handle);
	ret_if(g_conn_status != SMARTTHINGS_RESOURCE_CONNECTION_STATUS_CONNECTED);

	smartthings_payload_create(&payload);
	if (!payload) {
		_E("failed to create payload is NULL");
		return;
	}

	smartthings_payload_set_int(payload, KEY_SWITCHLEVEL, (int)value);

	error = smartthings_resource_notify(handle, URI_SWITCHLEVEL, payload);
	if (error != SMARTTHINGS_RESOURCE_ERROR_NONE)
		_E("smartthings_resource_notify() failed, [%s]",
			__resource_error_to_str(error));

	smartthings_payload_destroy(payload);
}

static int __device_interfaces_set_callbak(smartthings_resource_h handle)
{
	retv_if(!handle, -1);

	// Assume that, device interfaces are already initialized in controller.c
	switch_state_changed_cb_set(RESOURCE_CALLBACK_KEY,
		__switch_changed, handle);
	servo_v_state_changed_cb_set(RESOURCE_CALLBACK_KEY,
		__servo_v_changed, handle);
	servo_h_state_changed_cb_set(RESOURCE_CALLBACK_KEY,
		__servo_h_changed, handle);
	motion_state_changed_cb_set(RESOURCE_CALLBACK_KEY,
		__motion_changed, handle);

	return 0;
}


int st_thing_resource_init(void)
{
	smartthings_resource_h st_res_h = NULL;
	int error = 0;

	if (g_st_res_h) {
		_I("Already initialized!");
		return 0;
	}

	error = smartthings_resource_initialize(&st_res_h,
				_resource_connection_status_cb, NULL);
	if (error) {
		_E("smartthings_resource_initialize() is failed, [%s]",
			__resource_error_to_str(error));
		return -1;
	}

	g_st_res_h = st_res_h;
	g_conn_status = SMARTTHINGS_RESOURCE_CONNECTION_STATUS_DISCONNECTED;

	__device_interfaces_set_callbak(g_st_res_h);

	return 0;
}

int st_thing_resource_fini(void)
{
	if (!g_st_res_h)
		return 0;

	smartthings_resource_unset_request_cb(g_st_res_h);
	smartthings_resource_deinitialize(g_st_res_h);
	g_st_res_h = NULL;
	g_conn_status = SMARTTHINGS_RESOURCE_CONNECTION_STATUS_DISCONNECTED;

	return 0;
}
