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
#include "switch.h"

#define IDLE_PRIORITY (G_PRIORITY_HIGH_IDLE + 30)

struct switch_data_s {
	switch_state_e state;
	GHashTable *callback_hash;
};

struct switch_callback_s {
	switch_state_changed_cb callback;
	void *cb_data;
};

struct switch_pass_data_s {
	char *pass_key;
	switch_state_e state;
};

static struct switch_data_s *g_switch;
static pthread_mutex_t g_switch_mutex;

static int __free_switch_handle(struct switch_data_s *sw)
{
	if (sw->callback_hash) {
		g_hash_table_destroy(sw->callback_hash);
		g_hash_table_unref(sw->callback_hash);
	}

	free(sw);
	return 0;
}

int switch_initialize(void)
{
	if (g_switch) {
		_D("The switch is already initialized!");
		return 0;
	}

	g_switch = malloc(sizeof(struct switch_data_s));
	retv_if(!g_switch, -1);

	g_switch->callback_hash =
		g_hash_table_new_full(g_str_hash, g_str_equal, g_free, g_free);

	pthread_mutex_init(&g_switch_mutex, NULL);
	g_switch->state = SWITCH_STATE_OFF;

	/* TODO : initialize real switch here */

	return 0;
}

int switch_finalize(void)
{
	if (g_switch) {
		pthread_mutex_destroy(&g_switch_mutex);
		__free_switch_handle(g_switch);
		g_switch = NULL;
	}

	return 0;
}

static void __cb_item_foreach(gpointer key, gpointer value, gpointer user_data)
{
	char *item_name = key;
	struct switch_callback_s *cb_item = value;
	struct switch_pass_data_s *pass_item = user_data;

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
	struct switch_pass_data_s *pass_item = data;

	g_hash_table_foreach(g_switch->callback_hash, __cb_item_foreach, pass_item);
	g_free(pass_item->pass_key);
	g_free(pass_item);

	return G_SOURCE_REMOVE;
}

int switch_state_set(switch_state_e state, const char *pass_key)
{
	int old_state = 0;
	retv_if(!g_switch, -1);

	pthread_mutex_lock(&g_switch_mutex);
	old_state = g_switch->state;
	pthread_mutex_unlock(&g_switch_mutex);

	if (old_state != state) {
		pthread_mutex_lock(&g_switch_mutex);
		g_switch->state = state;
		pthread_mutex_unlock(&g_switch_mutex);

		if (g_hash_table_size(g_switch->callback_hash) > 0) {
			struct switch_pass_data_s *pass_item = NULL;

			pass_item = g_new(struct switch_pass_data_s, 1);
			pass_item->pass_key = g_strdup(pass_key);
			pass_item->state = state;
			g_idle_add_full(IDLE_PRIORITY,
				__call_cb_idle, pass_item, NULL);
		}
	}
	return 0;
}

int switch_state_get(switch_state_e *state)
{
	retv_if(!g_switch, -1);
	retv_if(!state, -1);

	pthread_mutex_lock(&g_switch_mutex);
	*state = g_switch->state;
	pthread_mutex_unlock(&g_switch_mutex);

	// _D("get state : %d", *state);

	return 0;
}

int switch_state_changed_cb_set(
	const char *callback_key, switch_state_changed_cb callback, void *cb_data)
{
	retv_if(!g_switch, -1);
	retv_if(!g_switch->callback_hash, -1);
	retv_if(!callback_key, -1);

	if (callback) {
		struct switch_callback_s *cb_item = NULL;
		cb_item = g_try_new(struct switch_callback_s, 1);
		retv_if(!cb_item, -1);

		cb_item->callback = callback;
		cb_item->cb_data = cb_data;

		g_hash_table_insert(g_switch->callback_hash,
			g_strdup(callback_key), cb_item);
	} else {
		g_hash_table_remove(g_switch->callback_hash, callback_key);
	}

	return 0;
}
