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

#include <stdlib.h>
#include <pthread.h>
#include <glib.h>
#include <math.h>
#include "log.h"
#include "servo-type.h"
#include "resource_servo_motor_sg90.h"

#define IDLE_PRIORITY (G_PRIORITY_HIGH_IDLE + 30)
#define VALUE_DEFAULT (50.0f)
#define SERVO_V_CHANNEL 0

struct servo_v_data_s {
	double value;
	GHashTable *callback_hash;
};

struct servo_v_callback_s {
	servo_state_changed_cb callback;
	void *cb_data;
};

struct servo_v_pass_data_s {
	char *pass_key;
	double value;
};

static struct servo_v_data_s *g_servo_v;
static pthread_mutex_t g_servo_v_mutex;

static int __free_servo_v_handle(struct servo_v_data_s *servo_v)
{
	if (servo_v->callback_hash) {
		g_hash_table_destroy(servo_v->callback_hash);
		g_hash_table_unref(servo_v->callback_hash);
	}

	free(servo_v);
	return 0;
}

int servo_v_finalize(void)
{
	if (g_servo_v) {
		resource_close_servo_motor(SERVO_V_CHANNEL);
		pthread_mutex_destroy(&g_servo_v_mutex);
		__free_servo_v_handle(g_servo_v);
		g_servo_v = NULL;
	}

	return 0;
}

int servo_v_initialize(void)
{
	if (g_servo_v) {
		_D("The servo_v is already initialized!");
		return 0;
	}

	g_servo_v = malloc(sizeof(struct servo_v_data_s));
	retv_if(!g_servo_v, -1);

	g_servo_v->callback_hash =
		g_hash_table_new_full(g_str_hash, g_str_equal, g_free, g_free);

	pthread_mutex_init(&g_servo_v_mutex, NULL);
	g_servo_v->value = VALUE_DEFAULT;

	if (resource_rotate_servo_motor_by_percent(SERVO_V_CHANNEL, VALUE_DEFAULT)) {
		_E("faiiled to set servo h value to 0");
		servo_v_finalize();
		return -1;
	}

	return 0;
}

static void __cb_item_foreach(gpointer key, gpointer value, gpointer user_data)
{
	char *item_name = key;
	struct servo_v_callback_s *cb_item = value;
	struct servo_v_pass_data_s *pass_item = user_data;

	ret_if(!item_name);
	ret_if(!cb_item);
	ret_if(!pass_item);

	if (pass_item->pass_key &&
		(0 == g_strcmp0(item_name, pass_item->pass_key))) {
			// _D("pass item - %s", item_name);
			return;
		}

	_D("callback called for [%s]", item_name);
	cb_item->callback(pass_item->value, cb_item->cb_data);
}

static gboolean __call_cb_idle(gpointer data)
{
	struct servo_v_pass_data_s *pass_item = data;

	g_hash_table_foreach(g_servo_v->callback_hash, __cb_item_foreach, pass_item);
	g_free(pass_item->pass_key);
	g_free(pass_item);

	return G_SOURCE_REMOVE;
}

static inline int __double_is_same(double a, double b)
{
	const double eps = 0.0001;
	if (fabs(a-b) < eps)
		return 1;
	else
		return 0;
}

int servo_v_state_set(double value, const char *pass_key)
{
	double old_value = 0.0;
	retv_if(!g_servo_v, -1);

	pthread_mutex_lock(&g_servo_v_mutex);
	old_value = g_servo_v->value;
	pthread_mutex_unlock(&g_servo_v_mutex);

	if (1){//!__double_is_same(old_value, value)) {
		if (resource_rotate_servo_motor_by_percent(SERVO_V_CHANNEL, value)) {
			_E("fail led to set servo v value to [%lf]", value);
			return -1;
		}
		_D("set value : %lf", value);
		pthread_mutex_lock(&g_servo_v_mutex);
		g_servo_v->value = value;
		pthread_mutex_unlock(&g_servo_v_mutex);

		if (g_hash_table_size(g_servo_v->callback_hash) > 0) {
			struct servo_v_pass_data_s *pass_item = NULL;

			pass_item = g_new(struct servo_v_pass_data_s, 1);
			pass_item->pass_key = g_strdup(pass_key);
			pass_item->value = value;
			g_idle_add_full(IDLE_PRIORITY,
				__call_cb_idle, pass_item, NULL);
		}
	} else {
		_D("a value[%lf] is same as old one[%lf]" , value, old_value);
	}
	return 0;
}

int servo_v_state_get(double *value)
{
	retv_if(!g_servo_v, -1);
	retv_if(!value, -1);

	pthread_mutex_lock(&g_servo_v_mutex);
	*value = g_servo_v->value;
	pthread_mutex_unlock(&g_servo_v_mutex);

	_D("get value : %lf", *value);

	return 0;
}

int servo_v_state_changed_cb_set(
	const char *callback_key, servo_state_changed_cb callback, void *cb_data)
{
	retv_if(!g_servo_v, -1);
	retv_if(!g_servo_v->callback_hash, -1);
	retv_if(!callback_key, -1);

	if (callback) {
		struct servo_v_callback_s *cb_item = NULL;
		cb_item = g_try_new(struct servo_v_callback_s, 1);
		retv_if(!cb_item, -1);

		cb_item->callback = callback;
		cb_item->cb_data = cb_data;

		g_hash_table_insert(g_servo_v->callback_hash,
			g_strdup(callback_key), cb_item);
	} else {
		g_hash_table_remove(g_servo_v->callback_hash, callback_key);
	}

	return 0;
}
