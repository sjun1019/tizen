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
#include "log.h"
#include "motion.h"

#define IDLE_PRIORITY (G_PRIORITY_HIGH_IDLE + 30)

struct motion_data_s {
	int state;
	GHashTable *callback_hash;
};

struct motion_callback_s {
	motion_state_changed_cb callback;
	void *cb_data;
};

struct motion_pass_data_s {
	char *pass_key;
	int state;
};

static struct motion_data_s *g_motion;
static pthread_mutex_t g_motion_mutex;

static int __free_motion_handle(struct motion_data_s *handle)
{
	if (handle->callback_hash) {
		g_hash_table_destroy(handle->callback_hash);
		g_hash_table_unref(handle->callback_hash);
	}

	free(handle);
	return 0;
}

int motion_initialize(void)
{
	if (g_motion) {
		_D("The motion is already initialized!");
		return 0;
	}

	g_motion = malloc(sizeof(struct motion_data_s));
	retv_if(!g_motion, -1);

	g_motion->callback_hash =
		g_hash_table_new_full(g_str_hash, g_str_equal, g_free, g_free);

	pthread_mutex_init(&g_motion_mutex, NULL);
	g_motion->state = 0;

	/* TODO : initialize real motion detector here */

	return 0;
}

int motion_finalize(void)
{
	if (g_motion) {
		pthread_mutex_destroy(&g_motion_mutex);
		__free_motion_handle(g_motion);
		g_motion = NULL;
	}

	return 0;
}

static void __cb_item_foreach(gpointer key, gpointer value, gpointer user_data)
{
	char *item_name = key;
	struct motion_callback_s *cb_item = value;
	struct motion_pass_data_s *pass_item = user_data;

	ret_if(!item_name);
	ret_if(!cb_item);
	ret_if(!pass_item);


	if (pass_item->pass_key &&
		(0 == g_strcmp0(item_name, pass_item->pass_key))) {
			// _D("pass item - %s", item_name);
			return;
		}

	_D("callback called for [%s]", item_name);
	cb_item->callback(pass_item->state, cb_item->cb_data);
}

static gboolean __call_cb_idle(gpointer data)
{
	struct motion_pass_data_s *pass_item = data;

	g_hash_table_foreach(g_motion->callback_hash, __cb_item_foreach, pass_item);
	g_free(pass_item->pass_key);
	g_free(pass_item);

	return G_SOURCE_REMOVE;
}

int motion_state_set(int state, const char *pass_key)
{
	int old_state = 0;
	retv_if(!g_motion, -1);

	// _D("set state : %d", state);

	pthread_mutex_lock(&g_motion_mutex);
	old_state = g_motion->state;
	pthread_mutex_unlock(&g_motion_mutex);

	if (old_state != state) {
		/* TODO : handle real motion detector here */
		pthread_mutex_lock(&g_motion_mutex);
		g_motion->state = state;
		pthread_mutex_unlock(&g_motion_mutex);

		if (g_hash_table_size(g_motion->callback_hash) > 0) {
			struct motion_pass_data_s *pass_item = NULL;

			pass_item = g_new(struct motion_pass_data_s, 1);
			pass_item->pass_key = g_strdup(pass_key);
			pass_item->state = state;
			g_idle_add_full(IDLE_PRIORITY,
				__call_cb_idle, pass_item, NULL);
		}
	}
	return 0;
}

int motion_state_get(int *state)
{
	retv_if(!g_motion, -1);
	retv_if(!state, -1);

	pthread_mutex_lock(&g_motion_mutex);
	*state = g_motion->state;
	pthread_mutex_unlock(&g_motion_mutex);

	// _D("get state : %d", *state);

	return 0;
}

int motion_state_changed_cb_set(
	const char *callback_key, motion_state_changed_cb callback, void *cb_data)
{
	retv_if(!g_motion, -1);
	retv_if(!g_motion->callback_hash, -1);
	retv_if(!callback_key, -1);

	if (callback) {
		struct motion_callback_s *cb_item = NULL;
		cb_item = g_try_new(struct motion_callback_s, 1);
		retv_if(!cb_item, -1);

		cb_item->callback = callback;
		cb_item->cb_data = cb_data;

		g_hash_table_insert(g_motion->callback_hash,
			g_strdup(callback_key), cb_item);
	} else {
		g_hash_table_remove(g_motion->callback_hash, callback_key);
	}

	return 0;
}
