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

#ifndef __SAMSUNG_EXPERIENCE_SERVICE_SMARTTHINGS_RESOURCE_H__
#define __SAMSUNG_EXPERIENCE_SERVICE_SMARTTHINGS_RESOURCE_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <tizen.h>
#include <smartthings_payload.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file smartthings_resource.h
 */

/**
 * @addtogroup CAPI_SMARTTHINGS_THING_RESOURCE_MODULE
 * @{
 */

/**
 * @brief Enumeration for the SmartThings resource error.
 * @since_ses 1
 */
typedef enum {
	SMARTTHINGS_RESOURCE_ERROR_NONE = TIZEN_ERROR_NONE,                                /**< Successful */
	SMARTTHINGS_RESOURCE_ERROR_INVALID_PARAMETER = TIZEN_ERROR_INVALID_PARAMETER,      /**< Invalid parameter */
	SMARTTHINGS_RESOURCE_ERROR_OUT_OF_MEMORY = TIZEN_ERROR_OUT_OF_MEMORY,              /**< Out of memory */
	SMARTTHINGS_RESOURCE_ERROR_PERMISSION_DENIED = TIZEN_ERROR_PERMISSION_DENIED,      /**< Permission denied */
	SMARTTHINGS_RESOURCE_ERROR_NO_DATA = TIZEN_ERROR_NO_DATA,                          /**< No data */
	SMARTTHINGS_RESOURCE_ERROR_NOT_SUPPORTED = TIZEN_ERROR_NOT_SUPPORTED,			   /**< Not supported */
	SMARTTHINGS_RESOURCE_ERROR_OPERATION_FAILED = TIZEN_ERROR_UNKNOWN - 1,             /**< Operation failed */
	SMARTTHINGS_RESOURCE_ERROR_SERVICE_UNAVAILABLE = TIZEN_ERROR_UNKNOWN -2            /**< Service unavailable */
} smartthings_resource_error_e;

/**
 * @brief Enumeration for the request type of resource and collection resource.
 * @since_ses 1
 */
typedef enum {
	SMARTTHINGS_RESOURCE_REQUEST_GET = 0,              /**< Get request type */
	SMARTTHINGS_RESOURCE_REQUEST_SET = 1,              /**< Set request type */
	SMARTTHINGS_RESOURCE_REQUEST_COLLECTION_GET = 2,   /**< Get request type for collection */
	SMARTTHINGS_RESOURCE_REQUEST_COLLECTION_SET = 3    /**< Set request type for collection */
} smartthings_resource_req_type_e;

/**
 * @brief Enumeration for RPC connection status.
 * @since_ses 1
 */
typedef enum {
	SMARTTHINGS_RESOURCE_CONNECTION_STATUS_CONNECTED = 0,          /**< Connection is connected */
	SMARTTHINGS_RESOURCE_CONNECTION_STATUS_DISCONNECTED,           /**< Connection is disconnected */
	SMARTTHINGS_RESOURCE_CONNECTION_STATUS_REJECTED,               /**< Connection is rejected */
} smartthings_resource_connection_status_e;

/**
 * @brief The SmartThings resource handle.
 * @since_ses 1
 */
typedef struct smartthings_resource_s *smartthings_resource_h;

/**
 * @brief Callback for status of connection to SmartThings Thing agent.
  * @details The following error codes can be received: \n
	#SMARTTHINGS_RESOURCE_ERROR_NONE:                               Success \n
	#SMARTTHINGS_RESOURCE_ERROR_PERMISSION_DENIED:      Permission denied \n
	#SMARTTHINGS_RESOURCE_ERROR_SERVICE_UNAVAILABLE:   Service unavailable \n
 * @since_ses 1
 *
 * @remarks The @a handle should not be released.
 * @remarks The @a handle is the same object for which the callback was set/added.
 * @remarks The @a handle will be released when smartthings_deinitialize() is called.
 * @remarks When callback is called, user can see result as #smartthings_resource_error_e enumeration value.
 * @remarks When callback is called, user can see connection status as #smartthings_connection_status_e enumeration value.
 *
 * @param[in] result The result of connection operation
 * @param[in] handle The SmartThings handle
 * @param[in] status The status of connection
 * @param[in] user_data The user data passed from the callback registration function
 *
 * @see smartthings_resource_initialize()
 */
typedef void (*smartthings_resource_connection_status_cb)(smartthings_resource_error_e result, smartthings_resource_h handle, smartthings_resource_connection_status_e status, void *user_data);


/**
 * @brief Callback for handling request(GET/SET) messages.
 * @since_ses 1
 *
 * @remarks The @a payload is NULL when @a req_type is #SMARTTHINGS_RESOURCE_REQUEST_GET.
 * @remarks The @a payload can be used only in the callback. To use outside, make a copy.
 * @remarks The @a st_h should not be released.
 * @remarks The @a st_h is the same object for which the callback was set/added.
 * @remarks The @a st_h will be released when smartthings_resource_deinitialize() is called.
 * @remarks The @a payload should not be released.
 * @remarks The @a uri can be used only in the callback. To use outside, make a copy.
 *
 * @param[in] st_h The SmartThings resource handle
 * @param[in] req_id The request ID of request message
 * @param[in] uri The resource URI
 * @param[in] req_type The request type for request message
 * @param[in] payload The payload for SET request message
 * @param[in] user_data The user data passed from the callback registration function
 *
 * @see smartthings_resource_set_request_cb()
 * @see smartthings_resource_unset_request_cb()
 */
typedef void (*smartthings_resource_request_cb)(smartthings_resource_h st_h, int req_id, const char *uri,
												smartthings_resource_req_type_e req_type,
												smartthings_payload_h payload, void *user_data);

/**
 * @brief Callback for status of resource registration to cloud.
 * @since_ses 1
 *
 * @remarks This callback will be called when status of resource registration is changed.
 * @remarks The @a st_h should not be released.
 * @remarks The @a st_h is the same object for which the callback was set/added.
 * @remarks The @a st_h will be released when smartthings_resource_deinitialize() is called.
 * @remarks The @a is_registered will be true when resources are registered to cloud.
 *
 * @param[in] st_h The SmartThings resource handle
 * @param[in] is_registered The status of resource registration to cloud
 * @param[in] user_data The user data passed from the callback registration function
 *
 * @see smartthings_resource_set_cloud_registration_status_cb()
 * @see smartthings_resource_unset_cloud_registration_status_cb()
 */
typedef void (*smartthings_resource_cloud_registration_status_cb)(smartthings_resource_h st_h, bool is_registered, void *user_data);


/**
 * @brief Initializes a resource handle and connects to agent.
 * @since_ses 1
 * @privilege %http://com.samsung.tizen.smartthings-thing/appdefined/smartthings-thing.resource \n
 *            %http://tizen.org/privilege/appmanager.launch \n
 *            %http://tizen.org/privilege/datasharing
 *
 * @remarks The @a st_h must be released using smartthings_resource_deinitialize().
 * @remarks Ths function returns #SMARTTHINGS_RESOURCE_ERROR_PERMISSION_DENIED\n
 *          if the application has no app-defined privilege for 'http://com.samsung.tizen.smartthings-thing/appdefined/smartthings-thing.resource'.
 *
 * @param[out] st_h The SmartThings resource handle to be newly created on success
 * @param[in] connection_status_cb The connection status callback to register
 * @param[in] user_data The user data to be passed to the callback function
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_RESOURCE_ERROR_NONE Successful
 * @retval #SMARTTHINGS_RESOURCE_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SMARTTHINGS_RESOURCE_ERROR_OUT_OF_MEMORY Out of memory
 * @retval #SMARTTHINGS_RESOURCE_ERROR_PERMISSION_DENIED Permission denied
 * @retval #SMARTTHINGS_RESOURCE_ERROR_OPERATION_FAILED Operation failed
 * @retval #SMARTTHINGS_RESOURCE_ERROR_NOT_SUPPORTED Not supported
 * @retval #SMARTTHINGS_RESOURCE_ERROR_SERVICE_UNAVAILABLE Service unavailable
 *
 * @see smartthings_resource_deinitialize()
 */
int smartthings_resource_initialize(smartthings_resource_h *st_h,
								   smartthings_resource_connection_status_cb connection_status_cb,
								   void *user_data);

/**
 * @brief Deinitializes a resource handle and disconnects from the agent.
 * @since_ses 1
 *
 * @param[in] st_h The SmartThings resource handle
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_RESOURCE_ERROR_NONE Successful
 * @retval #SMARTTHINGS_RESOURCE_ERROR_INVALID_PARAMETER Invalid parameter
 *
 * @see smartthings_resource_initialize()
 */
int smartthings_resource_deinitialize(smartthings_resource_h st_h);

/**
 * @brief Sets resource request callback.
 * @since_ses 1
 * @privilege %http://com.samsung.tizen.smartthings-thing/appdefined/smartthings-thing.resource \n
 *            %http://tizen.org/privilege/appmanager.launch \n
 *            %http://tizen.org/privilege/datasharing
 *
 * @param[in] st_h The SmartThings resource handle
 * @param[in] req_cb The request callback to register
 * @param[in] user_data The user data to be passed to the callback function
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_RESOURCE_ERROR_NONE Successful
 * @retval #SMARTTHINGS_RESOURCE_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SMARTTHINGS_RESOURCE_ERROR_PERMISSION_DENIED Permission denied
 * @retval #SMARTTHINGS_RESOURCE_ERROR_OPERATION_FAILED Operation failed
 * @retval #SMARTTHINGS_RESOURCE_ERROR_SERVICE_UNAVAILABLE Service unavailable
 *
 * @see smartthings_resource_unset_request_cb()
 */
int smartthings_resource_set_request_cb(smartthings_resource_h st_h,
								smartthings_resource_request_cb req_cb,
								void *user_data);

/**
 * @brief Unsets resource request callback.
 * @since_ses 1
 * @privilege %http://com.samsung.tizen.smartthings-thing/appdefined/smartthings-thing.resource \n
 *            %http://tizen.org/privilege/appmanager.launch \n
 *            %http://tizen.org/privilege/datasharing
 *
 * @param[in] st_h The SmartThings resource handle
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_RESOURCE_ERROR_NONE Successful
 * @retval #SMARTTHINGS_RESOURCE_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SMARTTHINGS_RESOURCE_ERROR_PERMISSION_DENIED Permission denied
 * @retval #SMARTTHINGS_RESOURCE_ERROR_OPERATION_FAILED Operation failed
 * @retval #SMARTTHINGS_RESOURCE_ERROR_SERVICE_UNAVAILABLE Service unavailable
 *
 * @see smartthings_resource_set_request_cb()
 */
int smartthings_resource_unset_request_cb(smartthings_resource_h st_h);

/**
 * @brief Sends response for resource request message.
 * @since_ses 1
 * @privilege %http://com.samsung.tizen.smartthings-thing/appdefined/smartthings-thing.resource \n
 *            %http://tizen.org/privilege/appmanager.launch \n
 *            %http://tizen.org/privilege/datasharing \n
 *            %http://tizen.org/privilege/internet
 *
 * @param[in] st_h The SmartThings resource handle
 * @param[in] req_id The request ID of request message
 * @param[in] uri The resource URI
 * @param[in] payload The payload of response message
 * @param[in] result The result of response
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_RESOURCE_ERROR_NONE Successful
 * @retval #SMARTTHINGS_RESOURCE_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SMARTTHINGS_RESOURCE_ERROR_PERMISSION_DENIED Permission denied
 * @retval #SMARTTHINGS_RESOURCE_ERROR_OPERATION_FAILED Operation failed
 * @retval #SMARTTHINGS_RESOURCE_ERROR_SERVICE_UNAVAILABLE Service unavailable
 */
int smartthings_resource_send_response(smartthings_resource_h st_h, int req_id, const char *uri, smartthings_payload_h payload, bool result);

/**
 * @brief Notifies resource change.
 * @since_ses 1
 * @privilege %http://com.samsung.tizen.smartthings-thing/appdefined/smartthings-thing.resource \n
 *            %http://tizen.org/privilege/appmanager.launch \n
 *            %http://tizen.org/privilege/datasharing \n
 *            %http://tizen.org/privilege/internet
 *
 * @param[in] st_h The SmartThings resource handle
 * @param[in] uri The resource URI
 * @param[in] payload The payload of response message
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_RESOURCE_ERROR_NONE Successful
 * @retval #SMARTTHINGS_RESOURCE_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SMARTTHINGS_RESOURCE_ERROR_PERMISSION_DENIED Permission denied
 * @retval #SMARTTHINGS_RESOURCE_ERROR_OPERATION_FAILED Operation failed
 * @retval #SMARTTHINGS_RESOURCE_ERROR_SERVICE_UNAVAILABLE Service unavailable
 */
int smartthings_resource_notify(smartthings_resource_h st_h, const char *uri, smartthings_payload_h payload);

/**
 * @brief Gets resource URIs.
 * @since_ses 1
 * @privilege %http://com.samsung.tizen.smartthings-thing/appdefined/smartthings-thing.resource \n
 *            %http://tizen.org/privilege/appmanager.launch \n
 *            %http://tizen.org/privilege/datasharing
 *
 * @remarks The @a uris should be released using free().
 *
 * @param[in] st_h The SmartThings resource handle
 * @param[out] count The resource count
 * @param[out] uris The resource URI list
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_RESOURCE_ERROR_NONE Successful
 * @retval #SMARTTHINGS_RESOURCE_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SMARTTHINGS_RESOURCE_ERROR_PERMISSION_DENIED Permission denied
 * @retval #SMARTTHINGS_RESOURCE_ERROR_OPERATION_FAILED Operation failed
 * @retval #SMARTTHINGS_RESOURCE_ERROR_SERVICE_UNAVAILABLE Service unavailable
 */
int smartthings_resource_get_uris(smartthings_resource_h st_h, int *count, char ***uris);

/**
 * @brief Sets cloud registration callback.
 * @since_ses 1
 * @privilege %http://com.samsung.tizen.smartthings-thing/appdefined/smartthings-thing.resource \n
 *            %http://tizen.org/privilege/appmanager.launch \n
 *            %http://tizen.org/privilege/datasharing
 *
 * @param[in] st_h The SmartThings resource handle
 * @param[in] reg_cb The callback to register
 * @param[in] user_data The user data to be passed to the callback function
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_RESOURCE_ERROR_NONE Successful
 * @retval #SMARTTHINGS_RESOURCE_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SMARTTHINGS_RESOURCE_ERROR_PERMISSION_DENIED Permission denied
 * @retval #SMARTTHINGS_RESOURCE_ERROR_OPERATION_FAILED Operation failed
 * @retval #SMARTTHINGS_RESOURCE_ERROR_SERVICE_UNAVAILABLE Service unavailable
 *
 * @see smartthings_resource_unset_cloud_registration_status_cb()
 */
int smartthings_resource_set_cloud_registration_status_cb(smartthings_resource_h st_h,
								smartthings_resource_cloud_registration_status_cb reg_cb,
								void *user_data);

/**
 * @brief Unsets cloud registration callback.
 * @since_ses 1
 * @privilege %http://com.samsung.tizen.smartthings-thing/appdefined/smartthings-thing.resource \n
 *            %http://tizen.org/privilege/appmanager.launch \n
 *            %http://tizen.org/privilege/datasharing
 *
 * @param[in] st_h The SmartThings resource handle
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_RESOURCE_ERROR_NONE Successful
 * @retval #SMARTTHINGS_RESOURCE_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SMARTTHINGS_RESOURCE_ERROR_PERMISSION_DENIED Permission denied
 * @retval #SMARTTHINGS_RESOURCE_ERROR_OPERATION_FAILED Operation failed
 * @retval #SMARTTHINGS_RESOURCE_ERROR_SERVICE_UNAVAILABLE Service unavailable
 *
 * @see smartthings_resource_set_cloud_registration_status_cb()
 */
int smartthings_resource_unset_cloud_registration_status_cb(smartthings_resource_h st_h);


/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __SAMSUNG_EXPERIENCE_SERVICE_SMARTTHINGS_RESOURCE_H__ */
