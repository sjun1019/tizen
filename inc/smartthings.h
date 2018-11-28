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

#ifndef __SAMSUNG_EXPERIENCE_SERVICE_SMARTTHINGS_H__
#define __SAMSUNG_EXPERIENCE_SERVICE_SMARTTHINGS_H__

#include <stdlib.h>
#include <stdbool.h>
#include <tizen.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup CAPI_SMARTTHINGS_THING_MASTER_MODULE
 * @{
 */

/**
 * @brief Definition for the max length of SSID for access point.
 * @since_ses 1
 */
#define SMARTTHINGS_SSID_LEN_MAX 32

/**
 * @brief Definition for the max length of cloud information.
 * @since_ses 1
 */
#define SMARTTHINGS_CLOUD_INFO_LEN_MAX 128

/**
 * @brief Enumeration for the SmartThings error.
 * @since_ses 1
 */
typedef enum {
	SMARTTHINGS_ERROR_NONE = TIZEN_ERROR_NONE,                                /**< Successful */
	SMARTTHINGS_ERROR_INVALID_PARAMETER = TIZEN_ERROR_INVALID_PARAMETER,      /**< Invalid parameter */
	SMARTTHINGS_ERROR_OUT_OF_MEMORY = TIZEN_ERROR_OUT_OF_MEMORY,              /**< Out of memory */
	SMARTTHINGS_ERROR_PERMISSION_DENIED = TIZEN_ERROR_PERMISSION_DENIED,      /**< Permission denied */
	SMARTTHINGS_ERROR_NO_DATA = TIZEN_ERROR_NO_DATA,                          /**< No data */
	SMARTTHINGS_ERROR_NOT_SUPPORTED = TIZEN_ERROR_NOT_SUPPORTED,              /**< Not supported */
	SMARTTHINGS_ERROR_OPERATION_FAILED = TIZEN_ERROR_UNKNOWN - 1,             /**< Operation failed */
	SMARTTHINGS_ERROR_SERVICE_UNAVAILABLE = TIZEN_ERROR_UNKNOWN -2            /**< Service unavailable */
} smartthings_error_e;

/**
 * @brief Enumeration for SmartThings status.
 * @since_ses 1
 */
typedef enum {
	SMARTTHINGS_STATUS_NOT_READY = -1,                   /**< Service agent is not ready */
	SMARTTHINGS_STATUS_INIT = 0,                         /**< Initial state of SmartThings Thing */
	SMARTTHINGS_STATUS_ES_STARTED,                       /**< Easy-setup is started */
	SMARTTHINGS_STATUS_ES_DONE,                          /**< Easy-setup is done */
	SMARTTHINGS_STATUS_ES_FAILED_ON_OWNERSHIP_TRANSFER,  /**< Easy-setup failed due to Ownership-Transfer failure */
	SMARTTHINGS_STATUS_CONNECTING_TO_AP,                 /**< Connecting to target Wi-Fi access point */
	SMARTTHINGS_STATUS_CONNECTED_TO_AP,                  /**< Connected to target Wi-Fi access point */
	SMARTTHINGS_STATUS_CONNECTING_TO_AP_FAILED,          /**< Failed to connect to target Wi-Fi access point */
	SMARTTHINGS_STATUS_REGISTERING_TO_CLOUD,             /**< Trying to sign up, sign in and publish resources to cloud */
	SMARTTHINGS_STATUS_REGISTERED_TO_CLOUD,              /**< Publish resources to cloud is complete. Now the thing is ready to be controlled via cloud */
	SMARTTHINGS_STATUS_REGISTERING_FAILED_ON_SIGN_IN,    /**< Failed to sign in to cloud */
	SMARTTHINGS_STATUS_REGISTERING_FAILED_ON_PUB_RES     /**< Failed to publish resources to cloud */
} smartthings_status_e;

/**
 * @brief Enumeration for RPC connection status.
 * @since_ses 1
 */
typedef enum {
	SMARTTHINGS_CONNECTION_STATUS_CONNECTED = 0,            /**< Connection is connected */
	SMARTTHINGS_CONNECTION_STATUS_DISCONNECTED,             /**< Connection is disconnected */
	SMARTTHINGS_CONNECTION_STATUS_REJECTED,                 /**< Connection is rejected */
} smartthings_connection_status_e;

/**
 * @brief The Wi-Fi mode.
 * @since_ses 1
 */
typedef enum {
	SMARTTHINGS_WIFI_MODE_11A = (1 << 0),   /**< Wi-Fi 11A */
	SMARTTHINGS_WIFI_MODE_11B = (1 << 1),   /**< Wi-Fi 11B */
	SMARTTHINGS_WIFI_MODE_11G = (1 << 2),   /**< Wi-Fi 11G */
	SMARTTHINGS_WIFI_MODE_11N = (1 << 3),   /**< Wi-Fi 11N */
	SMARTTHINGS_WIFI_MODE_11AC = (1 << 4)   /**< Wi-Fi 11AC */
} smartthings_wifi_mode_e;

/**
 * @brief The Wi-Fi frequency band.
 * @since_ses 1
 */
typedef enum {
	SMARTTHINGS_WIFI_FREQ_24G = (1 << 0),       /**< Wi-Fi 2.4GHz */
	SMARTTHINGS_WIFI_FREQ_5G = (1 << 1),        /**< Wi-Fi 5GHz */
} smartthings_wifi_freq_e;

/**
 * @brief The Wi-Fi authentication type of access point.
 * @since_ses 1
 */
typedef enum {
	SMARTTHINGS_WIFI_AUTHTYPE_NONE = 0, /**< No authentication */
	SMARTTHINGS_WIFI_AUTHTYPE_WEP,      /**< WEP */
	SMARTTHINGS_WIFI_AUTHTYPE_WPA_PSK,  /**< WPA-PSK */
	SMARTTHINGS_WIFI_AUTHTYPE_WPA2_PSK  /**< WPA2-PSK */
} smartthings_wifi_authtype_e;

/**
 * @brief The Wi-Fi encryption type of access point.
 * @since_ses 1
 */
typedef enum {
	SMARTTHINGS_WIFI_ENCTYPE_NONE = 0,      /**< No encryption */
	SMARTTHINGS_WIFI_ENCTYPE_WEP_64,        /**< WEP 64 */
	SMARTTHINGS_WIFI_ENCTYPE_WEP_128,       /**< WEP 128 */
	SMARTTHINGS_WIFI_ENCTYPE_TKIP,          /**< TKIP */
	SMARTTHINGS_WIFI_ENCTYPE_AES,           /**< AES */
	SMARTTHINGS_WIFI_ENCTYPE_TKIP_AES       /**< TKIP/AES */
} smartthings_wifi_enctype_e;

/**
 * @brief The SmartThings handle.
 * @since_ses 1
 */
typedef struct smartthings_s *smartthings_h;

/**
 * @brief The access point information handle.
 * @since_ses 1
 */
typedef struct smartthings_ap_info_s *smartthings_ap_info_h;

/**
 * @brief The device provisioning information handle.
 * @since_ses 1
 */
typedef struct smartthings_device_prov_info_s *smartthings_device_prov_info_h;

/**
 * @brief The cloud information handle for cloud sign-up.
 * @since_ses 1
 */
typedef struct smartthings_cloud_info_s *smartthings_cloud_info_h;

/**
 * @brief The access point list handle.
 * @since_ses 1
 */
typedef struct smartthings_ap_list_s *smartthings_ap_list_h;

/**
 * @brief Callback for status of connection to SmartThings Thing agent.
 * @details The following error codes can be received: \n
	#SMARTTHINGS_ERROR_NONE:                               Success \n
	#SMARTTHINGS_ERROR_PERMISSION_DENIED:      Permission denied \n
	#SMARTTHINGS_ERROR_SERVICE_UNAVAILABLE:   Service unavailable \n
 * @since_ses 1
 *
 * @remarks The @a handle should not be released.
 * @remarks The @a handle is the same object for which the callback was set/added.
 * @remarks The @a handle will be released when smartthings_deinitialize() is called.
 * @remarks When callback is called, user can see result as #smartthings_error_e enumeration value.
 * @remarks When callback is called, user can see connection status as #smartthings_connection_status_e enumeration value.
 *
 * @param[in] result The result of connection operation
 * @param[in] handle The SmartThings handle
 * @param[in] status The status of connection
 * @param[in] user_data The user data passed from the callback registration function
 *
 * @see smartthings_initialize()
 */
typedef void (*smartthings_connection_status_cb)(smartthings_error_e result, smartthings_h handle, smartthings_connection_status_e status, void *user_data);

/**
 * @brief Callback for SmartThings Thing status.
 * @since_ses 1
 *
 * @remarks The @a handle should not be released.
 * @remarks The @a handle is the same object for which the callback was set/added.
 * @remarks The @a handle will be released when smartthings_deinitialize() is called.
 * @remarks When callback is called, user can see SmartThings status as #smartthings_status_e enumeration value.
 *
 * @param[in] handle The SmartThings handle
 * @param[in] status The status of SmartThings
 * @param[in] user_data The user data passed from the callback registration function
 *
 * @see smartthings_set_status_changed_cb()
 * @see smartthings_unset_status_changed_cb()
 */
typedef void (*smartthings_status_changed_cb)(smartthings_h handle, smartthings_status_e status, void *user_data);

/**
 * @brief Callback for getting user's input regarding mutual verification.
 * @since_ses 1
 *
 * @remarks The @a handle should not be released.
 * @remarks The @a handle is the same object for which the callback was set/added.
 * @remarks The @a handle will be released when smartthings_deinitialize() is called.
 * @remarks When callback is called, user can send a confirmation for mutual verification as true or false.
 *
 * @param[in] handle The SmartThings handle
 * @param[in] user_data The user data passed from the callback registration function
 *
 * @see smartthings_set_user_confirm_cb()
 * @see smartthings_unset_user_confirm_cb()
 */
typedef void (*smartthings_user_confirm_cb)(smartthings_h handle, void *user_data);

/**
 * @brief Callback for getting user's opinion regarding device reset.
 * @since_ses 1
 *
 * @remarks The @a handle should not be released.
 * @remarks The @a handle is the same object for which the callback was set/added.
 * @remarks The @a handle will be released when smartthings_deinitialize() is called.
 * @remarks When callback is called, user can sends a confirmation for reset as true or false.
 *
 * @param[in] handle The SmartThings handle
 * @param[in] user_data The user data passed from the callback registration function
 *
 * @see smartthings_set_reset_confirm_cb()
 * @see smartthings_unset_reset_confirm_cb()
 */
typedef void (*smartthings_reset_confirm_cb)(smartthings_h handle, void *user_data);

/**
 * @brief Callback for result of reset operation.
 * @since_ses 1
 *
 * @remarks The @a handle should not be released.
 * @remarks The @a handle is the same object for which the callback was set/added.
 * @remarks The @a handle will be released when smartthings_deinitialize() is called.
 * @remarks When callback is called, user can check reset operation succeeds or fails.
 *
 * @param[in] handle The SmartThings handle
 * @param[in] result The result of reset
 * @param[in] user_data The user data passed from the callback registration function
 *
 * @see smartthings_set_reset_result_cb()
 * @see smartthings_unset_reset_result_cb()
 */
typedef void (*smartthings_reset_result_cb)(smartthings_h handle, bool result, void *user_data);

/**
 * @brief Callback for carrying the randomly generated PIN information.
 * @since_ses 1
 *
 * @remarks The @a handle should not be released.
 * @remarks The @a handle is the same object for which the callback was set/added.
 * @remarks The @a handle will be released when smartthings_deinitialize() is called.
 * @remarks The @a pin can be used only in the callback. To use outside, make a copy.
 * @remarks When callback is called, user can see PIN value and length.
 *
 * @param[in] handle The SmartThings handle
 * @param[in] pin The PIN data in string format
 * @param[in] size The PIN length of @a pin
 * @param[in] user_data The user data passed from the callback registration function
 *
 * @see smartthings_set_pin_cb()
 * @see smartthings_unset_pin_cb()
 */
typedef void (*smartthings_pin_generated_cb)(smartthings_h handle, const char* pin, size_t size, void *user_data);

/**
 * @brief Callback for informing the application to close the PIN display.
 * @since_ses 1
 *
 * @remarks The @a handle should not be released.
 * @remarks The @a handle is the same object for which the callback was set/added.
 * @remarks The @a handle will be released when smartthings_deinitialize() is called.
 * @remarks When callback is called, user can know PIN based ownership transfer is finished.
 *
 * @param[in] handle The SmartThings handle
 * @param[in] user_data The user data passed from the callback registration function
 *
 * @see smartthings_set_pin_cb()
 * @see smartthings_unset_pin_cb()
 */
typedef void (*smartthings_pin_display_close_cb)(smartthings_h handle, void *user_data);

/**
 * @brief Callback for informing Wi-Fi AP information to connect.
 * @since_ses 1
 *
 * @remarks The @a handle should not be released.
 * @remarks The @a handle is the same object for which the callback was set/added.
 * @remarks The @a handle will be released when smartthings_deinitialize() is called.
 * @remarks The @a ap_info_h should not be released.
 * @remarks The @a ap_info_h will be released when smartthings_unset_wifi_ap_provisioning_cb() is called.
 * @remarks When callback is called, user can get Wi-Fi provisioning information.
 *
 * @param[in] handle The SmartThings handle
 * @param[in] ap_info_h The AP information handle
 * @param[in] user_data The user data passed from the callback registration function
 *
 * @see smartthings_set_wifi_ap_provisioning_cb()
 * @see smartthings_unset_wifi_ap_provisioning_cb()
 */
typedef void (*smartthings_wifi_ap_provisioning_cb)(smartthings_h handle, smartthings_ap_info_h ap_info_h, void *user_data);

/**
 * @brief Callback for informing device provisioning information.
 * @since_ses 1
 *
 * @remarks The @a handle should not be released.
 * @remarks The @a handle is the same object for which the callback was set/added.
 * @remarks The @a handle will be released when smartthings_deinitialize() is called.
 * @remarks The @a dev_prov_h should not be released.
 * @remarks The @a dev_prov_h will be released when smartthings_unset_device_provisioning_cb() is called.
 * @remarks When callback is called, user can get device provisioning information.
 *
 * @param[in] handle The SmartThings handle
 * @param[in] dev_prov_h The device provisioning information handle
 * @param[in] user_data The user data passed from the callback registration function
 *
 * @see smartthings_set_device_provisioning_cb()
 * @see smartthings_unset_device_provisioning_cb()
 */
typedef void (*smartthings_device_provisioning_cb)(smartthings_h handle, smartthings_device_prov_info_h dev_prov_h, void *user_data);

/**
 * @brief Callback for informing the scan AP list request.
 * @since_ses 1
 *
 * @remarks The @a handle should not be released.
 * @remarks The @a handle is the same object for which the callback was set/added.
 * @remarks The @a handle will be released when smartthings_deinitialize() is called.
 * @remarks When callback is called, user scans access points, sets AP list and sends it to agent.
 *
 * @param[in] handle The SmartThings handle
 * @param[in] req_id The request ID
 * @param[in] user_data The user data passed from the callback registration function
 *
 * @see smartthings_set_scan_ap_cb()
 * @see smartthings_unset_scan_ap_cb()
 */
typedef void (*smartthings_scan_ap_cb)(smartthings_h handle, int req_id, void *user_data);

/**
 * @brief Callback for informing the stop soft AP request.
 * @since_ses 1
 *
 * @remarks The @a handle should not be released.
 * @remarks The @a handle is the same object for which the callback was set/added.
 * @remarks The @a handle will be released when smartthings_deinitialize() is called.
 * @remarks When callback is called, user stops soft AP.
 *
 * @param[in] handle The SmartThings handle
 * @param[in] user_data The user data passed from the callback registration function
 *
 * @see smartthings_set_stop_soft_ap_cb()
 * @see smartthings_unset_stop_soft_ap_cb()
 */
typedef void (*smartthings_stop_soft_ap_cb)(smartthings_h handle, void *user_data);

/**
 * @brief Creates a handle and connects to agent.
 * @since_ses 1
 * @privilege %http://com.samsung.tizen.smartthings-thing/appdefined/smartthings-thing.master \n
 *            %http://tizen.org/privilege/appmanager.launch \n
 *            %http://tizen.org/privilege/datasharing
 *
 * @remarks The @a handle must be released using smartthings_deinitialize().
 * @remarks Ths function returns #SMARTTHINGS_ERROR_PERMISSION_DENIED\n
 *          if the application has no app-defined privilege for 'http://com.samsung.tizen.smartthings-thing/appdefined/smartthings-thing.master'.
 *
 * @param[out] handle The SmartThings handle to be newly created on success
 * @param[in] connection_status_cb The RPC connection status callback to register
 * @param[in] user_data The user data to be passed to the callback function
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_ERROR_NONE Successful
 * @retval #SMARTTHINGS_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SMARTTHINGS_ERROR_OUT_OF_MEMORY Out of memory
 * @retval #SMARTTHINGS_ERROR_PERMISSION_DENIED Permission denied
 * @retval #SMARTTHINGS_ERROR_OPERATION_FAILED Operation failed
 * @retval #SMARTTHINGS_ERROR_NOT_SUPPORTED Not supported
 * @retval #SMARTTHINGS_ERROR_SERVICE_UNAVAILABLE Service unavailable
 *
 * @see smartthings_deinitialize()
 */
int smartthings_initialize(smartthings_h *handle,
						smartthings_connection_status_cb connection_status_cb,
						void *user_data);

/**
 * @brief Deinitializes a handle and disconnects from the agent.
 * @since_ses 1
 *
 * @param[in] handle The SmartThings handle
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_ERROR_NONE Successful
 * @retval #SMARTTHINGS_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SMARTTHINGS_ERROR_OPERATION_FAILED Operation failed
 *
 * @see smartthings_initialize()
 */
int smartthings_deinitialize(smartthings_h handle);

/**
 * @brief Starts SmartThings Thing operation.
 * @since_ses 1
 * @privilege %http://com.samsung.tizen.smartthings-thing/appdefined/smartthings-thing.master \n
 *            %http://tizen.org/privilege/appmanager.launch \n
 *            %http://tizen.org/privilege/datasharing
 *
 * @param[in] handle The SmartThings handle
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_ERROR_NONE Successful
 * @retval #SMARTTHINGS_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SMARTTHINGS_ERROR_PERMISSION_DENIED Permission denied
 * @retval #SMARTTHINGS_ERROR_OPERATION_FAILED Operation failed
 * @retval #SMARTTHINGS_ERROR_SERVICE_UNAVAILABLE Service unavailable
 *
 * @see smartthings_stop()
 */
int smartthings_start(smartthings_h handle);

/**
 * @brief Stops SmartThings Thing operation.
 * @since_ses 1
 * @privilege %http://com.samsung.tizen.smartthings-thing/appdefined/smartthings-thing.master \n
 *            %http://tizen.org/privilege/appmanager.launch \n
 *            %http://tizen.org/privilege/datasharing
 *
 * @param[in] handle The SmartThings handle
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_ERROR_NONE Successful
 * @retval #SMARTTHINGS_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SMARTTHINGS_ERROR_PERMISSION_DENIED Permission denied
 * @retval #SMARTTHINGS_ERROR_OPERATION_FAILED Operation failed
 * @retval #SMARTTHINGS_ERROR_SERVICE_UNAVAILABLE Service unavailable
 *
 * @see smartthings_start()
 */
int smartthings_stop(smartthings_h handle);

/**
 * @brief Sets thing status changed callback.
 * @since_ses 1
 * @privilege %http://com.samsung.tizen.smartthings-thing/appdefined/smartthings-thing.master \n
 *            %http://tizen.org/privilege/appmanager.launch \n
 *            %http://tizen.org/privilege/datasharing
 *
 * @remarks Only one callback function can be set with this function.
 * @remarks If multiple callbacks are set, the last one is registered only.
 * @remarks Callback is called when SmartThings status is changed.
 * @remarks When callback is called, user can get SmartThings status as #smartthings_status_e enumeration value.
 *
 * @param[in] handle The SmartThings handle
 * @param[in] status_cb The status changed callback to register
 * @param[in] user_data The user data to be passed to the callback function
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_ERROR_NONE Successful
 * @retval #SMARTTHINGS_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SMARTTHINGS_ERROR_PERMISSION_DENIED Permission denied
 * @retval #SMARTTHINGS_ERROR_OPERATION_FAILED Operation failed
 * @retval #SMARTTHINGS_ERROR_SERVICE_UNAVAILABLE Service unavailable
 *
 * @see smartthings_unset_status_changed_cb()
 */
int smartthings_set_status_changed_cb(smartthings_h handle,
								smartthings_status_changed_cb status_cb,
								void *user_data);

/**
 * @brief Unsets thing status changed callback.
 * @since_ses 1
 * @privilege %http://com.samsung.tizen.smartthings-thing/appdefined/smartthings-thing.master \n
 *            %http://tizen.org/privilege/appmanager.launch \n
 *            %http://tizen.org/privilege/datasharing
 *
 * @param[in] handle The SmartThings handle
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_ERROR_NONE Successful
 * @retval #SMARTTHINGS_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SMARTTHINGS_ERROR_PERMISSION_DENIED Permission denied
 * @retval #SMARTTHINGS_ERROR_OPERATION_FAILED Operation failed
 * @retval #SMARTTHINGS_ERROR_SERVICE_UNAVAILABLE Service unavailable
 *
 * @see smartthings_set_status_changed_cb()
 */
int smartthings_unset_status_changed_cb(smartthings_h handle);

/**
 * @brief Sets test certificate files.
 * @since_ses 1
 * @privilege %http://com.samsung.tizen.smartthings-thing/appdefined/smartthings-thing.master \n
 *            %http://tizen.org/privilege/appmanager.launch \n
 *            %http://tizen.org/privilege/datasharing
 *
 * @remarks These files should be placed in 'res' directory of application.
 * @remarks This function is needed only for using test certificate.
 * @remarks This function can be used before smartthings_start()
 *
 * @param[in] handle The SmartThings handle
 * @param[in] certificate The certificate file
 * @param[in] private_key The private key file
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_ERROR_NONE Successful
 * @retval #SMARTTHINGS_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SMARTTHINGS_ERROR_PERMISSION_DENIED Permission denied
 * @retval #SMARTTHINGS_ERROR_OPERATION_FAILED Operation failed
 * @retval #SMARTTHINGS_ERROR_SERVICE_UNAVAILABLE Service unavailable
 */
int smartthings_set_certificate_file(smartthings_h handle, const char *certificate, const char *private_key);

/**
 * @brief Sets device property for Easy-setup.
 * @since_ses 1
 *
 * @remarks This function can be used before smartthings_start()
 *
 * @param[in] handle The SmartThings handle
 * @param[in] dev_name The device name
 * @param[in] wifi_mode The supported Wi-Fi mode (bit masked value for #smartthings_wifi_mode_e)
 * @param[in] wifi_freq The supported Wi-Fi frequency (bit masked value for #smartthings_wifi_freq_e)
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_ERROR_NONE Successful
 * @retval #SMARTTHINGS_ERROR_INVALID_PARAMETER Invalid parameter
 */
int smartthings_set_device_property(smartthings_h handle, const char* dev_name, int wifi_mode, int wifi_freq);

/**
 * @brief Gets a device ID.
 * @since_ses 1
 * @privilege %http://com.samsung.tizen.smartthings-thing/appdefined/smartthings-thing.master \n
 *            %http://tizen.org/privilege/appmanager.launch \n
 *            %http://tizen.org/privilege/datasharing
 *
 * @remarks The @a device_id should be released using free().
 *
 * @param[in] handle The SmartThings handle
 * @param[out] device_id The device ID
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_ERROR_NONE Successful
 * @retval #SMARTTHINGS_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SMARTTHINGS_ERROR_PERMISSION_DENIED Permission denied
 * @retval #SMARTTHINGS_ERROR_OPERATION_FAILED Operation failed
 * @retval #SMARTTHINGS_ERROR_SERVICE_UNAVAILABLE Service unavailable
 */
int smartthings_get_device_id(smartthings_h handle, char **device_id);

/**
 * @brief Gets a Easy-setup status.
 * @since_ses 1
 * @privilege %http://com.samsung.tizen.smartthings-thing/appdefined/smartthings-thing.master \n
 *            %http://tizen.org/privilege/appmanager.launch \n
 *            %http://tizen.org/privilege/datasharing
 *
 * @param[in] handle The SmartThings handle
 * @param[out] is_completed The status of Easy-setup whether it is completed or not
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_ERROR_NONE Successful
 * @retval #SMARTTHINGS_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SMARTTHINGS_ERROR_PERMISSION_DENIED Permission denied
 * @retval #SMARTTHINGS_ERROR_OPERATION_FAILED Operation failed
 * @retval #SMARTTHINGS_ERROR_SERVICE_UNAVAILABLE Service unavailable
 */
int smartthings_get_easysetup_status(smartthings_h handle, bool *is_completed);

/**
 * @brief Starts Easy-setup mode.
 *
 * @details This function requests for turning on soft AP to SmartThings Thing agent.
 * @since_ses 1
 * @privilege %http://com.samsung.tizen.smartthings-thing/appdefined/smartthings-thing.master \n
 *            %http://tizen.org/privilege/appmanager.launch \n
 *            %http://tizen.org/privilege/datasharing \n
 *            %http://tizen.org/privilege/softap
 *
 * @param[in] handle The SmartThings handle
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_ERROR_NONE Successful
 * @retval #SMARTTHINGS_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SMARTTHINGS_ERROR_PERMISSION_DENIED Permission denied
 * @retval #SMARTTHINGS_ERROR_OPERATION_FAILED Operation failed
 * @retval #SMARTTHINGS_ERROR_SERVICE_UNAVAILABLE Service unavailable
 *
 * @see smartthings_stop_easysetup()
 */
int smartthings_start_easysetup(smartthings_h handle);

/**
 * @brief Stops Easy-setup mode.
 *
 * @details This function requests for turning off soft AP to SmartThings Thing agent.
 * @since_ses 1
 * @privilege %http://com.samsung.tizen.smartthings-thing/appdefined/smartthings-thing.master \n
 *            %http://tizen.org/privilege/appmanager.launch \n
 *            %http://tizen.org/privilege/datasharing \n
 *            %http://tizen.org/privilege/softap
 *
 * @param[in] handle The SmartThings handle
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_ERROR_NONE Successful
 * @retval #SMARTTHINGS_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SMARTTHINGS_ERROR_PERMISSION_DENIED Permission denied
 * @retval #SMARTTHINGS_ERROR_OPERATION_FAILED Operation failed
 * @retval #SMARTTHINGS_ERROR_SERVICE_UNAVAILABLE Service unavailable
 *
 * @see smartthings_start_easysetup()
 */
int smartthings_stop_easysetup(smartthings_h handle);

/**
 * @brief Sets callback for getting user confirmation for mutual verification based just work ownership transfer.
 * @since_ses 1
 * @privilege %http://com.samsung.tizen.smartthings-thing/appdefined/smartthings-thing.master \n
 *            %http://tizen.org/privilege/appmanager.launch \n
 *            %http://tizen.org/privilege/datasharing
 *
 * @remarks Only one callback function can be set with this function.
 * @remarks If multiple callbacks are set, the last one is registered only.
 * @remarks Callback is called when it needs user's confirm for mutual verification based just work ownership transfer.
 * @remarks When callback is called, user can send a confirmation for mutual verification based just work ownership transfer as true or false.
 *
 * @param[in] handle The SmartThings handle
 * @param[in] confirm_cb The user confirm callback to register
 * @param[in] user_data The user data to be passed to the callback function
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_ERROR_NONE Successful
 * @retval #SMARTTHINGS_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SMARTTHINGS_ERROR_PERMISSION_DENIED Permission denied
 * @retval #SMARTTHINGS_ERROR_OPERATION_FAILED Operation failed
 * @retval #SMARTTHINGS_ERROR_SERVICE_UNAVAILABLE Service unavailable
 *
 * @see smartthings_unset_user_confirm_cb()
 */
int smartthings_set_user_confirm_cb(smartthings_h handle,
								smartthings_user_confirm_cb confirm_cb,
								void *user_data);

/**
 * @brief Unsets user confirmation callback.
 * @since_ses 1
 * @privilege %http://com.samsung.tizen.smartthings-thing/appdefined/smartthings-thing.master \n
 *            %http://tizen.org/privilege/appmanager.launch \n
 *            %http://tizen.org/privilege/datasharing
 *
 * @param[in] handle The SmartThings handle
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_ERROR_NONE Successful
 * @retval #SMARTTHINGS_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SMARTTHINGS_ERROR_PERMISSION_DENIED Permission denied
 * @retval #SMARTTHINGS_ERROR_OPERATION_FAILED Operation failed
 * @retval #SMARTTHINGS_ERROR_SERVICE_UNAVAILABLE Service unavailable
 *
 * @see smartthings_set_user_confirm_cb()
 */
int smartthings_unset_user_confirm_cb(smartthings_h handle);

/**
 * @brief Sets reset confirmation callback.
 * @since_ses 1
 * @privilege %http://com.samsung.tizen.smartthings-thing/appdefined/smartthings-thing.master \n
 *            %http://tizen.org/privilege/appmanager.launch \n
 *            %http://tizen.org/privilege/datasharing
 *
 * @remarks Only one callback function can be set with this function.
 * @remarks If multiple callbacks are set, the last one is registered only.
 * @remarks Callback is called when it needs user's confirm for reset.
 * @remarks When callback is called, user can send a confirmation for reset as true or false.
 *
 * @param[in] handle The SmartThings handle
 * @param[in] confirm_cb The reset confirm callback to register
 * @param[in] user_data The user data to be passed to the callback function
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_ERROR_NONE Successful
 * @retval #SMARTTHINGS_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SMARTTHINGS_ERROR_PERMISSION_DENIED Permission denied
 * @retval #SMARTTHINGS_ERROR_OPERATION_FAILED Operation failed
 * @retval #SMARTTHINGS_ERROR_SERVICE_UNAVAILABLE Service unavailable
 *
 * @see smartthings_unset_reset_confirm_cb()
 */
int smartthings_set_reset_confirm_cb(smartthings_h handle,
								smartthings_reset_confirm_cb confirm_cb,
								void *user_data);

/**
 * @brief Unsets reset confirmation callback.
 * @since_ses 1
 * @privilege %http://com.samsung.tizen.smartthings-thing/appdefined/smartthings-thing.master \n
 *            %http://tizen.org/privilege/appmanager.launch \n
 *            %http://tizen.org/privilege/datasharing
 *
 * @param[in] handle The SmartThings handle
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_ERROR_NONE Successful
 * @retval #SMARTTHINGS_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SMARTTHINGS_ERROR_PERMISSION_DENIED Permission denied
 * @retval #SMARTTHINGS_ERROR_OPERATION_FAILED Operation failed
 * @retval #SMARTTHINGS_ERROR_SERVICE_UNAVAILABLE Service unavailable
 *
 * @see smartthings_set_reset_confirm_cb()
 */
int smartthings_unset_reset_confirm_cb(smartthings_h handle);

/**
 * @brief Sets reset result callback.
 * @since_ses 1
 * @privilege %http://com.samsung.tizen.smartthings-thing/appdefined/smartthings-thing.master \n
 *            %http://tizen.org/privilege/appmanager.launch \n
 *            %http://tizen.org/privilege/datasharing
 *
 * @remarks Only one callback function can be set with this function.
 * @remarks If multiple callbacks are set, the last one is registered only.
 * @remarks Callback is called when reset operation returns its result.
 * @remarks When callback is called, user can check reset operation succeeds or fails.
 *
 * @param[in] handle The SmartThings handle
 * @param[in] reset_result_cb The reset result callback to register
 * @param[in] user_data The user data to be passed to the callback function
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_ERROR_NONE Successful
 * @retval #SMARTTHINGS_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SMARTTHINGS_ERROR_PERMISSION_DENIED Permission denied
 * @retval #SMARTTHINGS_ERROR_OPERATION_FAILED Operation failed
 * @retval #SMARTTHINGS_ERROR_SERVICE_UNAVAILABLE Service unavailable
 *
 * @see smartthings_unset_reset_result_cb()
 */
int smartthings_set_reset_result_cb(smartthings_h handle,
								smartthings_reset_result_cb reset_result_cb,
								void *user_data);

/**
 * @brief Unsets reset result callback.
 * @since_ses 1
 * @privilege %http://com.samsung.tizen.smartthings-thing/appdefined/smartthings-thing.master \n
 *            %http://tizen.org/privilege/appmanager.launch \n
 *            %http://tizen.org/privilege/datasharing
 *
 * @param[in] handle The SmartThings handle
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_ERROR_NONE Successful
 * @retval #SMARTTHINGS_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SMARTTHINGS_ERROR_PERMISSION_DENIED Permission denied
 * @retval #SMARTTHINGS_ERROR_OPERATION_FAILED Operation failed
 * @retval #SMARTTHINGS_ERROR_SERVICE_UNAVAILABLE Service unavailable
 *
 * @see smartthings_set_reset_result_cb()
 */
int smartthings_unset_reset_result_cb(smartthings_h handle);


/**
 * @brief Sets callback for getting randomly generated PIN for the PIN-based ownership transfer request.
 * @since_ses 1
 * @privilege %http://com.samsung.tizen.smartthings-thing/appdefined/smartthings-thing.master \n
 *            %http://tizen.org/privilege/appmanager.launch \n
 *            %http://tizen.org/privilege/datasharing
 *
 * @remarks Only one callback function can be set with this function.
 * @remarks If multiple callbacks are set, the last one is registered only.
 * @remarks @a generated_cb callback is called when PIN is generated.
 * @remarks @a close_cb callback is called when PIN based ownership transfer is finished.
 * @remarks When @a generated_cb callback is called, user can see PIN value and length.
 * @remarks When @a close_cb callback is called, user can know PIN based ownership transfer is finished.
 *
 * @param[in] handle The SmartThings handle
 * @param[in] generated_cb The PIN generation callback to register
 * @param[in] close_cb The PIN display close callback to register
 * @param[in] user_data The user data to be passed to the callback function
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_ERROR_NONE Successful
 * @retval #SMARTTHINGS_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SMARTTHINGS_ERROR_PERMISSION_DENIED Permission denied
 * @retval #SMARTTHINGS_ERROR_OPERATION_FAILED Operation failed
 * @retval #SMARTTHINGS_ERROR_SERVICE_UNAVAILABLE Service unavailable
 *
 * @see smartthings_unset_pin_cb()
 */
int smartthings_set_pin_cb(smartthings_h handle,
								smartthings_pin_generated_cb generated_cb,
								smartthings_pin_display_close_cb close_cb,
								void *user_data);

/**
 * @brief Unsets PIN callback.
 * @since_ses 1
 * @privilege %http://com.samsung.tizen.smartthings-thing/appdefined/smartthings-thing.master \n
 *            %http://tizen.org/privilege/appmanager.launch \n
 *            %http://tizen.org/privilege/datasharing
 *
 * @param[in] handle The SmartThings handle
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_ERROR_NONE Successful
 * @retval #SMARTTHINGS_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SMARTTHINGS_ERROR_PERMISSION_DENIED Permission denied
 * @retval #SMARTTHINGS_ERROR_OPERATION_FAILED Operation failed
 * @retval #SMARTTHINGS_ERROR_SERVICE_UNAVAILABLE Service unavailable
 *
 * @see smartthings_set_pin_cb()
 */
int smartthings_unset_pin_cb(smartthings_h handle);

/**
 * @brief Sets callback for getting Wi-Fi AP information during Easy-setup.
 * @since_ses 1
 * @privilege %http://com.samsung.tizen.smartthings-thing/appdefined/smartthings-thing.master \n
 *            %http://tizen.org/privilege/appmanager.launch \n
 *            %http://tizen.org/privilege/datasharing
 *
 * @remarks Only one callback function can be set with this function.
 * @remarks If multiple callbacks are set, the last one is registered only.
 * @remarks Callback is called when Wi-Fi provisioning event occurs.
 * @remarks When callback is called, user can get Wi-Fi provisioning information.
 *
 * @param[in] handle The SmartThings handle
 * @param[in] wifi_ap_cb The Wi-Fi AP callback to register
 * @param[in] user_data The user data to be passed to the callback function
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_ERROR_NONE Successful
 * @retval #SMARTTHINGS_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SMARTTHINGS_ERROR_PERMISSION_DENIED Permission denied
 * @retval #SMARTTHINGS_ERROR_OPERATION_FAILED Operation failed
 * @retval #SMARTTHINGS_ERROR_SERVICE_UNAVAILABLE Service unavailable
 *
 * @see smartthings_unset_wifi_ap_provisioning_cb()
 */
int smartthings_set_wifi_ap_provisioning_cb(smartthings_h handle,
								smartthings_wifi_ap_provisioning_cb wifi_ap_cb,
								void *user_data);

/**
 * @brief Unsets callback for getting Wi-Fi AP information during Easy-setup.
 * @since_ses 1
 * @privilege %http://com.samsung.tizen.smartthings-thing/appdefined/smartthings-thing.master \n
 *            %http://tizen.org/privilege/appmanager.launch \n
 *            %http://tizen.org/privilege/datasharing
 *
 * @param[in] handle The SmartThings handle
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_ERROR_NONE Successful
 * @retval #SMARTTHINGS_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SMARTTHINGS_ERROR_PERMISSION_DENIED Permission denied
 * @retval #SMARTTHINGS_ERROR_OPERATION_FAILED Operation failed
 * @retval #SMARTTHINGS_ERROR_SERVICE_UNAVAILABLE Service unavailable
 *
 * @see smartthings_set_wifi_ap_provisioning_cb()
 */
int smartthings_unset_wifi_ap_provisioning_cb(smartthings_h handle);

/**
 * @brief Sets callback for getting device provisioning information.
 * @since_ses 1
 * @privilege %http://com.samsung.tizen.smartthings-thing/appdefined/smartthings-thing.master \n
 *            %http://tizen.org/privilege/appmanager.launch \n
 *            %http://tizen.org/privilege/datasharing
 *
 * @remarks Only one callback function can be set with this function.
 * @remarks If multiple callbacks are set, the last one is registered only.
 * @remarks Callback is called when device provisioning event occurs.
 * @remarks When callback is called, user can get device provisioning information.
 *
 * @param[in] handle The SmartThings handle
 * @param[in] dev_prov_cb The device provisioning callback to register
 * @param[in] user_data The user data to be passed to the callback function
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_ERROR_NONE Successful
 * @retval #SMARTTHINGS_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SMARTTHINGS_ERROR_PERMISSION_DENIED Permission denied
 * @retval #SMARTTHINGS_ERROR_OPERATION_FAILED Operation failed
 * @retval #SMARTTHINGS_ERROR_SERVICE_UNAVAILABLE Service unavailable
 *
 * @see smartthings_unset_device_provisioning_cb()
 */
int smartthings_set_device_provisioning_cb(smartthings_h handle,
								smartthings_device_provisioning_cb dev_prov_cb,
								void *user_data);

/**
 * @brief Unsets callback for getting device provisioning information.
 * @since_ses 1
 * @privilege %http://com.samsung.tizen.smartthings-thing/appdefined/smartthings-thing.master \n
 *            %http://tizen.org/privilege/appmanager.launch \n
 *            %http://tizen.org/privilege/datasharing
 *
 * @param[in] handle The SmartThings handle
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_ERROR_NONE Successful
 * @retval #SMARTTHINGS_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SMARTTHINGS_ERROR_PERMISSION_DENIED Permission denied
 * @retval #SMARTTHINGS_ERROR_OPERATION_FAILED Operation failed
 * @retval #SMARTTHINGS_ERROR_SERVICE_UNAVAILABLE Service unavailable
 *
 * @see smartthings_set_device_provisioning_cb()
 */
int smartthings_unset_device_provisioning_cb(smartthings_h handle);

/**
 * @brief Sets callback for informing the scan AP list request.
 * @since_ses 1
 * @privilege %http://com.samsung.tizen.smartthings-thing/appdefined/smartthings-thing.master \n
 *            %http://tizen.org/privilege/appmanager.launch \n
 *            %http://tizen.org/privilege/datasharing
 *
 * @remarks Only one callback function can be set with this function.
 * @remarks If multiple callbacks are set, the last one is registered only.
 * @remarks Callback is called when GET request for access point list.
 * @remarks When callback is called, user scans access points, sets AP list and sends it to agent.
 *
 * @param[in] handle The SmartThings handle
 * @param[in] scan_ap_cb The callback to register
 * @param[in] user_data The user data to be passed to the callback function
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_ERROR_NONE Successful
 * @retval #SMARTTHINGS_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SMARTTHINGS_ERROR_PERMISSION_DENIED Permission denied
 * @retval #SMARTTHINGS_ERROR_OPERATION_FAILED Operation failed
 * @retval #SMARTTHINGS_ERROR_SERVICE_UNAVAILABLE Service unavailable
 *
 * @see smartthings_unset_scan_ap_cb()
 * @see smartthings_send_ap_list()
 */
int smartthings_set_scan_ap_cb(smartthings_h handle,
								smartthings_scan_ap_cb scan_ap_cb,
								void *user_data);

/**
 * @brief Unsets callback for informing the scan AP list request.
 * @since_ses 1
 * @privilege %http://com.samsung.tizen.smartthings-thing/appdefined/smartthings-thing.master \n
 *            %http://tizen.org/privilege/appmanager.launch \n
 *            %http://tizen.org/privilege/datasharing
 *
 * @param[in] handle The SmartThings handle
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_ERROR_NONE Successful
 * @retval #SMARTTHINGS_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SMARTTHINGS_ERROR_PERMISSION_DENIED Permission denied
 * @retval #SMARTTHINGS_ERROR_OPERATION_FAILED Operation failed
 * @retval #SMARTTHINGS_ERROR_SERVICE_UNAVAILABLE Service unavailable
 *
 * @see smartthings_set_scan_ap_cb()
 */
int smartthings_unset_scan_ap_cb(smartthings_h handle);

/**
 * @brief Sets callback for informing the stop soft AP request.
 * @since_ses 1
 * @privilege %http://com.samsung.tizen.smartthings-thing/appdefined/smartthings-thing.master \n
 *            %http://tizen.org/privilege/appmanager.launch \n
 *            %http://tizen.org/privilege/datasharing
 *
 * @remarks Only one callback function can be set with this function.
 * @remarks If multiple callbacks are set, the last one is registered only.
 * @remarks Callback is called when POST request for stopping soft AP.
 * @remarks When callback is called, user stops soft AP.
 *
 * @param[in] handle The SmartThings handle
 * @param[in] stop_soft_ap_cb The callback to register
 * @param[in] user_data The user data to be passed to the callback function
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_ERROR_NONE Successful
 * @retval #SMARTTHINGS_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SMARTTHINGS_ERROR_PERMISSION_DENIED Permission denied
 * @retval #SMARTTHINGS_ERROR_OPERATION_FAILED Operation failed
 * @retval #SMARTTHINGS_ERROR_SERVICE_UNAVAILABLE Service unavailable
 *
 * @see smartthings_unset_stop_soft_ap_cb()
 */
int smartthings_set_stop_soft_ap_cb(smartthings_h handle,
								smartthings_stop_soft_ap_cb stop_soft_ap_cb,
								void *user_data);

/**
 * @brief Unsets callback for informing the stop soft AP request.
 * @since_ses 1
 * @privilege %http://com.samsung.tizen.smartthings-thing/appdefined/smartthings-thing.master \n
 *            %http://tizen.org/privilege/appmanager.launch \n
 *            %http://tizen.org/privilege/datasharing
 *
 * @param[in] handle The SmartThings handle
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_ERROR_NONE Successful
 * @retval #SMARTTHINGS_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SMARTTHINGS_ERROR_PERMISSION_DENIED Permission denied
 * @retval #SMARTTHINGS_ERROR_OPERATION_FAILED Operation failed
 * @retval #SMARTTHINGS_ERROR_SERVICE_UNAVAILABLE Service unavailable
 *
 * @see smartthings_set_stop_soft_ap_cb()
 */
int smartthings_unset_stop_soft_ap_cb(smartthings_h handle);

/**
 * @brief Sends a user confirmation for MUTUAL VERIFICATION BASED JUST WORK Ownership transfer.
 * @since_ses 1
 * @privilege %http://com.samsung.tizen.smartthings-thing/appdefined/smartthings-thing.master \n
 *            %http://tizen.org/privilege/appmanager.launch \n
 *            %http://tizen.org/privilege/datasharing \n
 *            %http://tizen.org/privilege/internet
 *
 * @param[in] handle The SmartThings handle
 * @param[in] confirm The user confirmation for OTM(ownership transfer method)
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_ERROR_NONE Successful
 * @retval #SMARTTHINGS_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SMARTTHINGS_ERROR_PERMISSION_DENIED Permission denied
 * @retval #SMARTTHINGS_ERROR_OPERATION_FAILED Operation failed
 * @retval #SMARTTHINGS_ERROR_SERVICE_UNAVAILABLE Service unavailable
 *
 * @see smartthings_set_user_confirm_cb()
 * @see smartthings_unset_user_confirm_cb()
 */
int smartthings_send_user_confirm(smartthings_h handle, bool confirm);


/**
 * @brief Sends a reset confirmation.
 * @since_ses 1
 * @privilege %http://com.samsung.tizen.smartthings-thing/appdefined/smartthings-thing.master \n
 *            %http://tizen.org/privilege/appmanager.launch \n
 *            %http://tizen.org/privilege/datasharing \n
 *            %http://tizen.org/privilege/internet
 *
 * @param[in] handle The SmartThings handle
 * @param[in] confirm The reset confirmation
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_ERROR_NONE Successful
 * @retval #SMARTTHINGS_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SMARTTHINGS_ERROR_PERMISSION_DENIED Permission denied
 * @retval #SMARTTHINGS_ERROR_OPERATION_FAILED Operation failed
 * @retval #SMARTTHINGS_ERROR_SERVICE_UNAVAILABLE Service unavailable
 *
 * @see smartthings_set_reset_confirm_cb()
 * @see smartthings_unset_reset_confirm_cb()
 */
int smartthings_send_reset_confirm(smartthings_h handle, bool confirm);

/**
 * @brief Sends a reset command for resetting the device's Cloud signup and Easy-setup.
 * @since_ses 1
 * @privilege %http://com.samsung.tizen.smartthings-thing/appdefined/smartthings-thing.master \n
 *            %http://tizen.org/privilege/appmanager.launch \n
 *            %http://tizen.org/privilege/datasharing \n
 *            %http://tizen.org/privilege/internet
 *
 * @param[in] handle The SmartThings handle
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_ERROR_NONE Successful
 * @retval #SMARTTHINGS_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SMARTTHINGS_ERROR_PERMISSION_DENIED Permission denied
 * @retval #SMARTTHINGS_ERROR_OPERATION_FAILED Operation failed
 * @retval #SMARTTHINGS_ERROR_SERVICE_UNAVAILABLE Service unavailable
 *
 * @see smartthings_set_reset_result_cb()
 * @see smartthings_unset_reset_result_cb()
 */
int smartthings_reset(smartthings_h handle);

/**
 * @brief Gets SSID of access point.
 * @since_ses 1
 *
 * @remarks The @a ssid should be released using free().
 *
 * @param[in] ap_info_h The SmartThings AP information handle
 * @param[out] ssid The SSID name
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_ERROR_NONE Successful
 * @retval #SMARTTHINGS_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SMARTTHINGS_ERROR_OPERATION_FAILED Operation failed
 *
 * @see smartthings_set_wifi_ap_provisioning_cb()
 * @see smartthings_unset_wifi_ap_provisioning_cb()
 */
int smartthings_apinfo_get_ssid(smartthings_ap_info_h ap_info_h, char **ssid);

/**
 * @brief Gets password of access point.
 * @since_ses 1
 *
 * @remarks The @a pwd should be released using free().
 *
 * @param[in] ap_info_h The SmartThings AP information handle
 * @param[out] pwd The password
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_ERROR_NONE Successful
 * @retval #SMARTTHINGS_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SMARTTHINGS_ERROR_OPERATION_FAILED Operation failed
 *
 * @see smartthings_set_wifi_ap_provisioning_cb()
 * @see smartthings_unset_wifi_ap_provisioning_cb()
 */
int smartthings_apinfo_get_password(smartthings_ap_info_h ap_info_h, char **pwd);

/**
 * @brief Gets authentification type of access point.
 * @since_ses 1
 *
 * @param[in] ap_info_h The SmartThings AP information handle
 * @param[out] authtype The authentification type
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_ERROR_NONE Successful
 * @retval #SMARTTHINGS_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SMARTTHINGS_ERROR_OPERATION_FAILED Operation failed
 *
 * @see smartthings_set_wifi_ap_provisioning_cb()
 * @see smartthings_unset_wifi_ap_provisioning_cb()
 */
int smartthings_apinfo_get_authtype(smartthings_ap_info_h ap_info_h, smartthings_wifi_authtype_e *authtype);

/**
 * @brief Gets encryption type of access point.
 * @since_ses 1
 *
 * @param[in] ap_info_h The SmartThings AP information handle
 * @param[out] enctype The encryption type
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_ERROR_NONE Successful
 * @retval #SMARTTHINGS_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SMARTTHINGS_ERROR_OPERATION_FAILED Operation failed
 *
 * @see smartthings_set_wifi_ap_provisioning_cb()
 * @see smartthings_unset_wifi_ap_provisioning_cb()
 */
int smartthings_apinfo_get_enctype(smartthings_ap_info_h ap_info_h, smartthings_wifi_enctype_e *enctype);

/**
 * @brief Gets channel information of access point.
 * @since_ses 1
 *
 * @param[in] ap_info_h The SmartThings AP information handle
 * @param[out] channel The frequency channel
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_ERROR_NONE Successful
 * @retval #SMARTTHINGS_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SMARTTHINGS_ERROR_OPERATION_FAILED Operation failed
 *
 * @see smartthings_set_wifi_ap_provisioning_cb()
 * @see smartthings_unset_wifi_ap_provisioning_cb()
 */
int smartthings_apinfo_get_channel(smartthings_ap_info_h ap_info_h, int *channel);

/**
 * @brief Gets language of device provisioing information.
 * @since_ses 1
 *
 * @remarks The @a language should be released using free().
 *
 * @param[in] dev_prov_h The SmartThings device provisioning information handle
 * @param[out] language The IETF language tag using ISO 639X
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_ERROR_NONE Successful
 * @retval #SMARTTHINGS_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SMARTTHINGS_ERROR_OPERATION_FAILED Operation failed
 *
 * @see smartthings_set_device_provisioning_cb()
 * @see smartthings_unset_device_provisioning_cb()
 */
int smartthings_devinfo_get_language(smartthings_device_prov_info_h dev_prov_h, char **language);

/**
 * @brief Gets country of device provisioing information.
 * @since_ses 1
 *
 * @remarks The @a country should be released using free().
 *
 * @param[in] dev_prov_h The SmartThings device provisioning information handle
 * @param[out] country The ISO Country Code (ISO 3166-1 Alpha-2)
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_ERROR_NONE Successful
 * @retval #SMARTTHINGS_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SMARTTHINGS_ERROR_OPERATION_FAILED Operation failed
 *
 * @see smartthings_set_device_provisioning_cb()
 * @see smartthings_unset_device_provisioning_cb()
 */
int smartthings_devinfo_get_country(smartthings_device_prov_info_h dev_prov_h, char **country);

/**
 * @brief Gets datetime of device provisioing information.
 * @since_ses 1
 *
 * @remarks The @a datetime should be released using free().
 *
 * @param[in] dev_prov_h The SmartThings device provisioning information handle
 * @param[out] datetime The date and time
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_ERROR_NONE Successful
 * @retval #SMARTTHINGS_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SMARTTHINGS_ERROR_OPERATION_FAILED Operation failed
 *
 * @see smartthings_set_device_provisioning_cb()
 * @see smartthings_unset_device_provisioning_cb()
 */
int smartthings_devinfo_get_datetime(smartthings_device_prov_info_h dev_prov_h, char **datetime);

/**
 * @brief Creates a SmartThings AP list handle.
 * @since_ses 1
 *
 * @remarks The @a ap_list_h must be released using smartthings_aplist_destroy().
 *
 * @param[out] ap_list_h The SmartThings AP list handle to be newly created on success
 * @param[in] count The count of AP
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_ERROR_NONE Successful
 * @retval #SMARTTHINGS_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SMARTTHINGS_ERROR_OUT_OF_MEMORY Out of memory
 *
 * @see smartthings_aplist_destroy()
 */
int smartthings_aplist_create(smartthings_ap_list_h *ap_list_h, unsigned int count);

/**
 * @brief Destroys a SmartThings AP list handle.
 * @since_ses 1
 *
 * @param[in] ap_list_h The SmartThings AP list handle
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_ERROR_NONE Successful
 * @retval #SMARTTHINGS_ERROR_INVALID_PARAMETER Invalid parameter
 *
 * @see smartthings_aplist_create()
 */
int smartthings_aplist_destroy(smartthings_ap_list_h ap_list_h);

/**
 * @brief Sets SSID at the specific index of AP list handle.
 * @since_ses 1
 *
 * @param[in] ap_list_h The SmartThings AP list handle
 * @param[in] idx The index
 * @param[in] ssid The SSID of AP
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_ERROR_NONE Successful
 * @retval #SMARTTHINGS_ERROR_INVALID_PARAMETER Invalid parameter
 *
 * @see smartthings_aplist_create()
 * @see smartthings_aplist_destroy()
 */
int smartthings_aplist_set_ssid(smartthings_ap_list_h ap_list_h, int idx, const char *ssid);

/**
 * @brief Sets BSSID at the specific index of AP list handle.
 * @since_ses 1
 *
 * @param[in] ap_list_h The SmartThings AP list handle
 * @param[in] idx The index
 * @param[in] bssid The BSSID of AP
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_ERROR_NONE Successful
 * @retval #SMARTTHINGS_ERROR_INVALID_PARAMETER Invalid parameter
 *
 * @see smartthings_aplist_create()
 * @see smartthings_aplist_destroy()
 */
int smartthings_aplist_set_bssid(smartthings_ap_list_h ap_list_h, int idx, const char *bssid);

/**
 * @brief Sets authentification type at the specific index of AP list handle.
 * @since_ses 1
 *
 * @param[in] ap_list_h The SmartThings AP list handle
 * @param[in] idx The index
 * @param[in] authtype The authentification type of AP
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_ERROR_NONE Successful
 * @retval #SMARTTHINGS_ERROR_INVALID_PARAMETER Invalid parameter
 *
 * @see smartthings_aplist_create()
 * @see smartthings_aplist_destroy()
 */
int smartthings_aplist_set_authtype(smartthings_ap_list_h ap_list_h, int idx, smartthings_wifi_authtype_e authtype);

/**
 * @brief Sets encryption type at the specific index of AP list handle.
 * @since_ses 1
 *
 * @param[in] ap_list_h The SmartThings AP list handle
 * @param[in] idx The index
 * @param[in] enctype The encryption type of AP
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_ERROR_NONE Successful
 * @retval #SMARTTHINGS_ERROR_INVALID_PARAMETER Invalid parameter
 *
 * @see smartthings_aplist_create()
 * @see smartthings_aplist_destroy()
 */
int smartthings_aplist_set_enctype(smartthings_ap_list_h ap_list_h, int idx, smartthings_wifi_enctype_e enctype);

/**
 * @brief Sets frequency channel at the specific index of AP list handle.
 * @since_ses 1
 *
 * @param[in] ap_list_h The SmartThings AP list handle
 * @param[in] idx The index
 * @param[in] channel The frequency channel of AP
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_ERROR_NONE Successful
 * @retval #SMARTTHINGS_ERROR_INVALID_PARAMETER Invalid parameter
 *
 * @see smartthings_aplist_create()
 * @see smartthings_aplist_destroy()
 */
int smartthings_aplist_set_channel(smartthings_ap_list_h ap_list_h, int idx, int channel);

/**
 * @brief Sets signal level at the specific index of AP list handle.
 * @since_ses 1
 *
 * @param[in] ap_list_h The SmartThings AP list handle
 * @param[in] idx The index
 * @param[in] signal_level The signal level of AP
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_ERROR_NONE Successful
 * @retval #SMARTTHINGS_ERROR_INVALID_PARAMETER Invalid parameter
 *
 * @see smartthings_aplist_create()
 * @see smartthings_aplist_destroy()
 */
int smartthings_aplist_set_signal_level(smartthings_ap_list_h ap_list_h, int idx, int signal_level);

/**
 * @brief Sets max speed rate at the specific index of AP list handle.
 * @since_ses 1
 *
 * @param[in] ap_list_h The SmartThings AP list handle
 * @param[in] idx The index
 * @param[in] max_rate The max speed rate of AP
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_ERROR_NONE Successful
 * @retval #SMARTTHINGS_ERROR_INVALID_PARAMETER Invalid parameter
 *
 * @see smartthings_aplist_create()
 * @see smartthings_aplist_destroy()
 */
int smartthings_aplist_set_max_rate(smartthings_ap_list_h ap_list_h, int idx, int max_rate);

/**
 * @brief Sends the scanned AP list.
 * @since_ses 1
 * @privilege %http://com.samsung.tizen.smartthings-thing/appdefined/smartthings-thing.master \n
 *            %http://tizen.org/privilege/appmanager.launch \n
 *            %http://tizen.org/privilege/datasharing \n
 *            %http://tizen.org/privilege/internet
 *
 * @param[in] handle The SmartThings handle
 * @param[in] ap_list_h The SmartThings AP list handle
 * @param[in] req_id The request ID
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_ERROR_NONE Successful
 * @retval #SMARTTHINGS_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SMARTTHINGS_ERROR_OUT_OF_MEMORY Out of memory
 * @retval #SMARTTHINGS_ERROR_PERMISSION_DENIED Permission denied
 * @retval #SMARTTHINGS_ERROR_OPERATION_FAILED Operation failed
 * @retval #SMARTTHINGS_ERROR_SERVICE_UNAVAILABLE Service unavailable
 *
 * @see smartthings_aplist_create()
 * @see smartthings_aplist_destroy()
 * @see smartthings_set_scan_ap_cb()
 */
int smartthings_send_ap_list(smartthings_h handle, smartthings_ap_list_h ap_list_h, int req_id);

/**
 * @brief Creates a SmartThings cloud information handle.
 * @since_ses 1
 *
 * @remarks The @a cloud_info_h must be released using smartthings_cloudinfo_destroy().
 *
 * @param[out] cloud_info_h The SmartThings cloud information handle to be newly created on success
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_ERROR_NONE Successful
 * @retval #SMARTTHINGS_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SMARTTHINGS_ERROR_OUT_OF_MEMORY Out of memory
 *
 * @see smartthings_cloudinfo_destroy()
 */
int smartthings_cloudinfo_create(smartthings_cloud_info_h *cloud_info_h);

/**
 * @brief Destroys a SmartThings cloud information handle.
 * @since_ses 1
 *
 * @param[in] cloud_info_h The SmartThings cloud information handle
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_ERROR_NONE Successful
 * @retval #SMARTTHINGS_ERROR_INVALID_PARAMETER Invalid parameter
 *
 * @see smartthings_cloudinfo_create()
 */
int smartthings_cloudinfo_destroy(smartthings_cloud_info_h cloud_info_h);

/**
 * @brief Sets region of cloud information.
 * @since_ses 1
 *
 * @remarks The @a region can be set to one of "global" or "china".
 * @remarks If it doesn't use this function, the @a region will be set to "global" internally.
 *
 * @param[in] cloud_info_h The SmartThings cloud information handle
 * @param[in] region The region name
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_ERROR_NONE Successful
 * @retval #SMARTTHINGS_ERROR_INVALID_PARAMETER Invalid parameter
 */
int smartthings_cloudinfo_set_region(smartthings_cloud_info_h cloud_info_h, const char *region);

/**
 * @brief Sets authentification provider of cloud information.
 * @since_ses 1
 *
 * @param[in] cloud_info_h The SmartThings cloud information handle
 * @param[in] auth_provider The authentification provider
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_ERROR_NONE Successful
 * @retval #SMARTTHINGS_ERROR_INVALID_PARAMETER Invalid parameter
 */
int smartthings_cloudinfo_set_auth_provider(smartthings_cloud_info_h cloud_info_h, const char *auth_provider);

/**
 * @brief Sets access token of cloud information.
 * @since_ses 1
 *
 * @param[in] cloud_info_h The SmartThings cloud information handle
 * @param[in] access_token The access token
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_ERROR_NONE Successful
 * @retval #SMARTTHINGS_ERROR_INVALID_PARAMETER Invalid parameter
 */
int smartthings_cloudinfo_set_access_token(smartthings_cloud_info_h cloud_info_h, const char *access_token);

/**
 * @brief Sets refresh token of cloud information.
 * @since_ses 1
 *
 * @param[in] cloud_info_h The SmartThings cloud information handle
 * @param[in] refresh_token The refresh token
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_ERROR_NONE Successful
 * @retval #SMARTTHINGS_ERROR_INVALID_PARAMETER Invalid parameter
 */
int smartthings_cloudinfo_set_refresh_token(smartthings_cloud_info_h cloud_info_h, const char *refresh_token);

/**
 * @brief Sets user ID of cloud information.
 * @since_ses 1
 *
 * @param[in] cloud_info_h The SmartThings cloud information handle
 * @param[in] user_id The user ID
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_ERROR_NONE Successful
 * @retval #SMARTTHINGS_ERROR_INVALID_PARAMETER Invalid parameter
 */
int smartthings_cloudinfo_set_user_id(smartthings_cloud_info_h cloud_info_h, const char *user_id);

/**
 * @brief Sets client ID of cloud information.
 * @since_ses 1
 *
 * @param[in] cloud_info_h The SmartThings cloud information handle
 * @param[in] client_id The client ID
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_ERROR_NONE Successful
 * @retval #SMARTTHINGS_ERROR_INVALID_PARAMETER Invalid parameter
 */
int smartthings_cloudinfo_set_client_id(smartthings_cloud_info_h cloud_info_h, const char *client_id);

/**
 * @brief Requests to sign up to cloud.
 * @since_ses 1
 * @privilege %http://com.samsung.tizen.smartthings-thing/appdefined/smartthings-thing.master \n
 *            %http://tizen.org/privilege/appmanager.launch \n
 *            %http://tizen.org/privilege/datasharing \n
 *            %http://tizen.org/privilege/internet
 *
 * @param[in] handle The SmartThings handle
 * @param[in] cloud_info_h The handle for cloud signup
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_ERROR_NONE Successful
 * @retval #SMARTTHINGS_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SMARTTHINGS_ERROR_PERMISSION_DENIED Permission denied
 * @retval #SMARTTHINGS_ERROR_OPERATION_FAILED Operation failed
 * @retval #SMARTTHINGS_ERROR_SERVICE_UNAVAILABLE Service unavailable
 */
int smartthings_sign_up_cloud(smartthings_h handle, smartthings_cloud_info_h cloud_info_h);

/**
 * @brief Sets preconfigured PIN.
 * @since_ses 1
 * @privilege %http://com.samsung.tizen.smartthings-thing/appdefined/smartthings-thing.master \n
 *            %http://tizen.org/privilege/appmanager.launch \n
 *            %http://tizen.org/privilege/datasharing
 *
 * @param[in] handle The SmartThings handle
 * @param[in] pin The PIN code to preconfigure
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_ERROR_NONE Successful
 * @retval #SMARTTHINGS_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SMARTTHINGS_ERROR_PERMISSION_DENIED Permission denied
 * @retval #SMARTTHINGS_ERROR_OPERATION_FAILED Operation failed
 * @retval #SMARTTHINGS_ERROR_SERVICE_UNAVAILABLE Service unavailable
 */
int smartthings_set_preconfigured_pin(smartthings_h handle, const char* pin);

/**
 * @brief Sets MOT(multiple ownership transfer) status.
 * @since_ses 1
 * @privilege %http://com.samsung.tizen.smartthings-thing/appdefined/smartthings-thing.master \n
 *            %http://tizen.org/privilege/appmanager.launch \n
 *            %http://tizen.org/privilege/datasharing
 *
 * @param[in] handle The SmartThings handle
 * @param[in] enable The MOT(multiple ownership transfer) status
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_ERROR_NONE Successful
 * @retval #SMARTTHINGS_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SMARTTHINGS_ERROR_PERMISSION_DENIED Permission denied
 * @retval #SMARTTHINGS_ERROR_OPERATION_FAILED Operation failed
 * @retval #SMARTTHINGS_ERROR_SERVICE_UNAVAILABLE Service unavailable
 */
int smartthings_set_mot_status(smartthings_h handle, bool enable);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __SAMSUNG_EXPERIENCE_SERVICE_SMARTTHINGS_H__ */
