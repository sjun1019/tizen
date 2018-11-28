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

#ifndef __SAMSUNG_EXPERIENCE_SERVICE_SMARTTHINGS_NOTIFICATION_H__
#define __SAMSUNG_EXPERIENCE_SERVICE_SMARTTHINGS_NOTIFICATION_H__

#include <smartthings_resource.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file smartthings_notification.h
 */

/**
 * @addtogroup CAPI_SMARTTHINGS_THING_NOTIFICATION_MODULE
 * @{
 */

/**
 * @brief Enumeration for the type of notification.
 * @since_ses 1
 */
typedef enum {
	SMARTTHINGS_NOTIFICATION_TYPE_ALERT = 1,    /**< Alert type */
	SMARTTHINGS_NOTIFICATION_TYPE_NOTICE,       /**< Notice type */
	SMARTTHINGS_NOTIFICATION_TYPE_EVENT,        /**< Event type */
	SMARTTHINGS_NOTIFICATION_TYPE_INFO,         /**< Info type */
	SMARTTHINGS_NOTIFICATION_TYPE_WARNING       /**< Warning type */
} smartthings_notification_type_e;


/**
 * @brief The SmartThings push message handle.
 * @since_ses 1
 */
typedef struct smartthings_push_msg_s* smartthings_push_msg_h;

/**
 * @brief Creates a SmartThings push message handle.
 * @since_ses 1
 *
 * @remarks The @a handle must be released using smartthings_push_msg_destroy().
 *
 * @param[out] handle The SmartThings push message handle to be newly created on success
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_RESOURCE_ERROR_NONE Successful
 * @retval #SMARTTHINGS_RESOURCE_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SMARTTHINGS_RESOURCE_ERROR_OUT_OF_MEMORY Out of memory
 * @retval #SMARTTHINGS_RESOURCE_ERROR_OPERATION_FAILED Operation failed
 *
 * @see smartthings_push_msg_destroy()
 */
int smartthings_push_msg_create(smartthings_push_msg_h *handle);

/**
 * @brief Destroys a SmartThings push message handle and releases all its resources.
 * @since_ses 1
 *
 * @param[in] handle The SmartThings push message handle
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_RESOURCE_ERROR_NONE Successful
 * @retval #SMARTTHINGS_RESOURCE_ERROR_INVALID_PARAMETER Invalid parameter
 *
 * @see smartthings_push_msg_create()
 */
int smartthings_push_msg_destroy(smartthings_push_msg_h handle);

/**
 * @brief Sets a URI for the push message.
 * @since_ses 1
 *
 * @param[in] handle The SmartThings push message handle
 * @param[in] uri The URI of push message to set
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_RESOURCE_ERROR_NONE Successful
 * @retval #SMARTTHINGS_RESOURCE_ERROR_INVALID_PARAMETER Invalid parameter
 *
 */
int smartthings_push_msg_set_uri(smartthings_push_msg_h handle, const char *uri);

/**
 * @brief Sets a type for the push message.
 * @since_ses 1
 *
 * @param[in] handle The SmartThings push message handle
 * @param[in] type The type of push message to set
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_RESOURCE_ERROR_NONE Successful
 * @retval #SMARTTHINGS_RESOURCE_ERROR_INVALID_PARAMETER Invalid parameter
 *
 */
int smartthings_push_msg_set_type(smartthings_push_msg_h handle, smartthings_notification_type_e type);

/**
 * @brief Sets a code for the push message.
 * @since_ses 1
 *
 * @param[in] handle The SmartThings push message handle
 * @param[in] code The code of push message to set
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_RESOURCE_ERROR_NONE Successful
 * @retval #SMARTTHINGS_RESOURCE_ERROR_INVALID_PARAMETER Invalid parameter
 *
 */
int smartthings_push_msg_set_code(smartthings_push_msg_h handle, const char *code);

/**
 * @brief Sets a payload for the push message.
 * @since_ses 1
 *
 * @param[in] handle The SmartThings push message handle
 * @param[in] payload The payload of push message to set
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_RESOURCE_ERROR_NONE Successful
 * @retval #SMARTTHINGS_RESOURCE_ERROR_INVALID_PARAMETER Invalid parameter
 *
 */
int smartthings_push_msg_set_payload(smartthings_push_msg_h handle, smartthings_payload_h payload);

/**
 * @brief Sends the push message.
 * @since_ses 1
 * @privilege %http://com.samsung.tizen.smartthings-thing/appdefined/smartthings-thing.resource \n
 *            %http://tizen.org/privilege/appmanager.launch \n
 *            %http://tizen.org/privilege/datasharing \n
 *            %http://tizen.org/privilege/internet
 *
 * @param[in] st_h The SmartThings resource handle
 * @param[in] push_msg_h The SmartThings push message handle
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_RESOURCE_ERROR_NONE Successful
 * @retval #SMARTTHINGS_RESOURCE_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SMARTTHINGS_RESOURCE_ERROR_PERMISSION_DENIED Permission denied
 * @retval #SMARTTHINGS_RESOURCE_ERROR_OPERATION_FAILED Operation failed
 */
int smartthings_send_push_msg(smartthings_resource_h st_h, smartthings_push_msg_h push_msg_h);


/**
 * @brief The SmartThings notification message handle.
 * @since_ses 1
 */
typedef struct smartthings_notification_msg_s* smartthings_notification_msg_h;


/**
 * @brief Creates a SmartThings notification message handle.
 * @since_ses 1
 *
 * @remarks The @a handle must be released using smartthings_notification_msg_destroy().
 *
 * @param[out] handle The SmartThings notification message handle to be newly created on success
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_RESOURCE_ERROR_NONE Successful
 * @retval #SMARTTHINGS_RESOURCE_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SMARTTHINGS_RESOURCE_ERROR_OUT_OF_MEMORY Out of memory
 * @retval #SMARTTHINGS_RESOURCE_ERROR_OPERATION_FAILED Operation failed
 *
 * @see smartthings_notification_msg_destroy()
 */
int smartthings_notification_msg_create(smartthings_notification_msg_h *handle);

/**
 * @brief Destroys a SmartThings notification message handle and releases all its resources.
 * @since_ses 1
 *
 * @param[in] handle The SmartThings notification message handle
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_RESOURCE_ERROR_NONE Successful
 * @retval #SMARTTHINGS_RESOURCE_ERROR_INVALID_PARAMETER Invalid parameter
 *
 * @see smartthings_notification_msg_create()
 */
int smartthings_notification_msg_destroy(smartthings_notification_msg_h handle);

/**
 * @brief Sets a URI for the notification message.
 * @since_ses 1
 *
 * @param[in] handle The SmartThings notification message handle
 * @param[in] uri The URI of notification message to set
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_RESOURCE_ERROR_NONE Successful
 * @retval #SMARTTHINGS_RESOURCE_ERROR_INVALID_PARAMETER Invalid parameter
 *
 */
int smartthings_notification_msg_set_uri(smartthings_notification_msg_h handle, const char *uri);

/**
 * @brief Sets a type for the notification message.
 * @since_ses 1
 *
 * @param[in] handle The SmartThings notification message handle
 * @param[in] type The type of notification message to set
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_RESOURCE_ERROR_NONE Successful
 * @retval #SMARTTHINGS_RESOURCE_ERROR_INVALID_PARAMETER Invalid parameter
 *
 */
int smartthings_notification_msg_set_type(smartthings_notification_msg_h handle, smartthings_notification_type_e type);

/**
 * @brief Sets a payload for the notification message.
 * @since_ses 1
 *
 * @param[in] handle The SmartThings notification message handle
 * @param[in] name The name of payload
 * @param[in] payload The payload of notification message to set
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_RESOURCE_ERROR_NONE Successful
 * @retval #SMARTTHINGS_RESOURCE_ERROR_INVALID_PARAMETER Invalid parameter
 *
 */
int smartthings_notification_msg_set_payload(smartthings_notification_msg_h handle, const char *name, smartthings_payload_h payload);

/**
 * @brief Sends the notification message.
 * @since_ses 1
 * @privilege %http://com.samsung.tizen.smartthings-thing/appdefined/smartthings-thing.resource \n
 *            %http://tizen.org/privilege/appmanager.launch \n
 *            %http://tizen.org/privilege/datasharing \n
 *            %http://tizen.org/privilege/internet
 *
 * @param[in] st_h The SmartThings resource handle
 * @param[in] notification_msg_h The SmartThings notification message handle
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_RESOURCE_ERROR_NONE Successful
 * @retval #SMARTTHINGS_RESOURCE_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SMARTTHINGS_RESOURCE_ERROR_PERMISSION_DENIED Permission denied
 * @retval #SMARTTHINGS_RESOURCE_ERROR_OPERATION_FAILED Operation failed
 */
int smartthings_send_notification_msg(smartthings_resource_h st_h, smartthings_notification_msg_h notification_msg_h);


/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __SAMSUNG_EXPERIENCE_SERVICE_SMARTTHINGS_NOTIFICATION_H__ */
