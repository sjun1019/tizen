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

#include <smartthings.h>
#include "log.h"

/*  You have to FIX IT !!!  */
#define CERT_FILE "cert_file_name.pem" // cert file name in 'res' directory
#define PRIV_FILE "private_key_file_name.der" // private key file name in 'res' directory

static smartthings_h g_st_master_h;

static void _user_confirm_cb(smartthings_h handle, void *user_data)
{
	if (smartthings_send_user_confirm(handle, true) != 0)
		_E("smartthings_send_user_confirm() is failed");
}

static void _reset_confirm_cb(smartthings_h handle, void *user_data)
{
	if (smartthings_send_reset_confirm(handle, true) != 0)
		_E("smartthings_send_reset_confirm() is failed");
}

static void _reset_result_cb(smartthings_h handle, bool result, void *user_data)
{
	_I("reset result = [%d]", result);
}

static const char *thing_status_to_str(smartthings_status_e status)
{
	const char *status_str = NULL;

	switch (status) {
	case SMARTTHINGS_STATUS_NOT_READY:
		status_str = "SMARTTHINGS_STATUS_NOT_READY";
		break;
	case SMARTTHINGS_STATUS_INIT:
		status_str = "SMARTTHINGS_STATUS_INIT";
		break;
	case SMARTTHINGS_STATUS_ES_STARTED:
		status_str = "SMARTTHINGS_STATUS_ES_STARTED";
		break;
	case SMARTTHINGS_STATUS_ES_DONE:
		status_str =  "SMARTTHINGS_STATUS_ES_DONE";
		break;
	case SMARTTHINGS_STATUS_ES_FAILED_ON_OWNERSHIP_TRANSFER:
		status_str = "SMARTTHINGS_STATUS_ES_FAILED_ON_OWNERSHIP_TRANSFER";
		break;
	case SMARTTHINGS_STATUS_CONNECTING_TO_AP:
		status_str = "SMARTTHINGS_STATUS_CONNECTING_TO_AP";
		break;
	case SMARTTHINGS_STATUS_CONNECTED_TO_AP:
		status_str = "SMARTTHINGS_STATUS_CONNECTED_TO_AP";
		break;
	case SMARTTHINGS_STATUS_CONNECTING_TO_AP_FAILED:
		status_str = "SMARTTHINGS_STATUS_CONNECTING_TO_AP_FAILED";
		break;
	case SMARTTHINGS_STATUS_REGISTERING_TO_CLOUD:
		status_str = "SMARTTHINGS_STATUS_REGISTERING_TO_CLOUD";
		break;
	case SMARTTHINGS_STATUS_REGISTERED_TO_CLOUD:
		status_str = "SMARTTHINGS_STATUS_REGISTERED_TO_CLOUD";
		break;
	case SMARTTHINGS_STATUS_REGISTERING_FAILED_ON_SIGN_IN:
		status_str = "SMARTTHINGS_STATUS_REGISTERING_FAILED_ON_SIGN_IN";
		break;
	case SMARTTHINGS_STATUS_REGISTERING_FAILED_ON_PUB_RES:
		status_str = "SMARTTHINGS_STATUS_REGISTERING_FAILED_ON_PUB_RES";
		break;
	default:
		status_str = "Unknown Status";
		break;
	}
	return status_str;
}

static void
_thing_status_cb(
	smartthings_h handle, smartthings_status_e status, void *user_data)
{
	_D("status: [%d] [%s]", status, thing_status_to_str(status));
}

static const char *__master_error_to_str(smartthings_error_e error)
{
	const char *err_str = NULL;

	switch (error) {
	case SMARTTHINGS_ERROR_NONE:
		err_str = "SMARTTHINGS_ERROR_NONE";
		break;
	case SMARTTHINGS_ERROR_INVALID_PARAMETER:
		err_str = "SMARTTHINGS_ERROR_INVALID_PARAMETER";
		break;
	case SMARTTHINGS_ERROR_OUT_OF_MEMORY:
		err_str = "SMARTTHINGS_ERROR_OUT_OF_MEMORY";
		break;
	case SMARTTHINGS_ERROR_PERMISSION_DENIED:
		err_str = "SMARTTHINGS_ERROR_PERMISSION_DENIED";
		break;
	case SMARTTHINGS_ERROR_NO_DATA:
		err_str = "SMARTTHINGS_ERROR_NO_DATA";
		break;
	case SMARTTHINGS_ERROR_NOT_SUPPORTED:
		err_str = "SMARTTHINGS_ERROR_NOT_SUPPORTED";
		break;
	case SMARTTHINGS_ERROR_OPERATION_FAILED:
		err_str = "SMARTTHINGS_ERROR_OPERATION_FAILED";
		break;
	case SMARTTHINGS_ERROR_SERVICE_UNAVAILABLE:
		err_str = "SMARTTHINGS_ERROR_SERVICE_UNAVAILABLE";
		break;
	default:
		err_str = "Unknown error";
		break;
	}

	return err_str;
}

static void
_things_connection_status_cb(smartthings_error_e error,
	smartthings_h handle, smartthings_connection_status_e status,
	void *user_data)
{
	_D("result [%s], status = [%d]", __master_error_to_str(error), status);

	if (status == SMARTTHINGS_CONNECTION_STATUS_CONNECTED) {
		int err = 0;
		bool is_es_completed = false;
		const char* dev_name = "iot-vision-cam";
		int wifi_mode = SMARTTHINGS_WIFI_MODE_11B
			| SMARTTHINGS_WIFI_MODE_11G
			| SMARTTHINGS_WIFI_MODE_11N;

		int wifi_freq = SMARTTHINGS_WIFI_FREQ_24G | SMARTTHINGS_WIFI_FREQ_5G;

		err = smartthings_set_device_property(
					handle, dev_name, wifi_mode, wifi_freq);
		if (err) {
			_E("smartthings_initialize() is failed, [%s]",
				__master_error_to_str(err));
			return;
		}

		err = smartthings_set_certificate_file(handle, CERT_FILE, PRIV_FILE);
		if (err) {
			_E("smartthings_set_certificate_file() is failed, [%s]",
				__master_error_to_str(err));
			return;
		}

		err = smartthings_set_user_confirm_cb(handle, _user_confirm_cb, NULL);
		if (err) {
			_E("smartthings_set_user_confirm_cb() is failed, [%s]",
				__master_error_to_str(err));
			return;
		}

		err = smartthings_set_reset_confirm_cb(handle, _reset_confirm_cb, NULL);
		if (err) {
			_E("smartthings_set_reset_confirm_cb() is failed, [%s]",
				__master_error_to_str(err));
			return;
		}

		err = smartthings_set_reset_result_cb(handle, _reset_result_cb, NULL);
		if (err) {
			_E("smartthings_set_reset_confirm_cb() is failed, [%s]",
				__master_error_to_str(err));
			return;
		}

		err = smartthings_set_status_changed_cb(handle, _thing_status_cb, NULL);
		if (err) {
			_E("smartthings_set_status_changed_callback() is failed, [%s]",
				__master_error_to_str(err));
			return;
		}

		err = smartthings_start(handle);
		if (err) {
			_E("smartthings_start() is failed, [%s]",
				__master_error_to_str(err));
			return;
		}

		err = smartthings_get_easysetup_status(handle, &is_es_completed);
		if (err) {
			_E("smartthings_get_easysetup_status() is failed, [%s]",
				__master_error_to_str(err));
			return;
		}

		if (is_es_completed == true) {
			_I("Easysetup is already done");
			return;
		}

		err = smartthings_start_easysetup(handle);
		if (err) {
			_E("smartthings_start_easysetup() is failed, [%s]",
				__master_error_to_str(err));
			smartthings_stop(handle);
			return;
		}
	} else {
			_E("connection failed");
	}
	return;
}

int st_thing_master_init()
{
	int err = 0;
	smartthings_h st_handle = NULL;

	if (g_st_master_h) {
		_I("Already initialized!");
		return 0;
	}

	err = smartthings_initialize(&st_handle, _things_connection_status_cb, NULL);
	if (err) {
		_E("smartthings_initialize() is failed, [%s]",
			__master_error_to_str(err));
		return -1;
	}

	g_st_master_h = st_handle;

	return 0;
}

int st_thing_master_fini()
{
	if (!g_st_master_h) {
		_I("handle is already NULL");
		return 0;
	}

	smartthings_unset_user_confirm_cb(g_st_master_h);
	smartthings_unset_reset_confirm_cb(g_st_master_h);
	smartthings_unset_reset_result_cb(g_st_master_h);
	smartthings_unset_status_changed_cb(g_st_master_h);

	smartthings_stop_easysetup(g_st_master_h);
	smartthings_stop(g_st_master_h);

	if (smartthings_deinitialize(g_st_master_h) != 0)  {
		_E("smartthings_deinitialize() is failed");
		return -1;
	}
	g_st_master_h = NULL;

	return 0;
}
