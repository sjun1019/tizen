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

#ifndef __SAMSUNG_EXPERIENCE_SERVICE_SMARTTHINGS_PAYLOAD_H__
#define __SAMSUNG_EXPERIENCE_SERVICE_SMARTTHINGS_PAYLOAD_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file smartthings_payload.h
 */

/**
 * @addtogroup CAPI_SMARTTHINGS_THING_PAYLOAD_MODULE
 * @{
 */

/**
 * @brief The SmartThings payload handle.
 * @since_ses 1
 */
typedef struct smartthings_payload_s *smartthings_payload_h;

/**
 * @brief Creates a SmartThings payload handle.
 * @since_ses 1
 *
 * @remarks The @a payload must be released using smartthings_payload_destroy().
 * @remarks If the @a payload is set to parent payload as an object or object array
 *          using smartthings_payload_set_object() or smartthings_payload_set_object_array(),
 *          the @a payload must not be released.

 * @param[out] payload The SmartThings payload handle to be newly created on success
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_RESOURCE_ERROR_NONE Successful
 * @retval #SMARTTHINGS_RESOURCE_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SMARTTHINGS_RESOURCE_ERROR_OUT_OF_MEMORY Out of memory
 *
 * @see smartthings_payload_destroy()
 */
int smartthings_payload_create(smartthings_payload_h *payload);

/**
 * @brief Destroys a SmartThings payload handle and releases all its resources.
 * @since_ses 1
 *
 * @remarks If the @a payload has child payload, its child payload will be released as well.
 *
 * @param[in] payload The SmartThings payload handle
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_RESOURCE_ERROR_NONE Successful
 * @retval #SMARTTHINGS_RESOURCE_ERROR_INVALID_PARAMETER Invalid parameter
 *
 * @see smartthings_payload_create()
 */
int smartthings_payload_destroy(smartthings_payload_h payload);

/**
 * @brief Sets an integer value for the attribute name.
 * @since_ses 1
 *
 * @remarks The @a attr_name is key value, one of several properties of the resource type.
 * @remarks The function replaces any existing value for the given @a attr_name.
 *
 * @param[in] payload The SmartThings payload handle
 * @param[in] attr_name The attribute name
 * @param[in] value The value to set
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_RESOURCE_ERROR_NONE Successful
 * @retval #SMARTTHINGS_RESOURCE_ERROR_INVALID_PARAMETER Invalid parameter
 */
int smartthings_payload_set_int(smartthings_payload_h payload, const char *attr_name, int value);

/**
 * @brief Sets a boolean value for the attribute name.
 * @since_ses 1
 *
 * @remarks The @a attr_name is key value, one of several properties of the resource type.
 * @remarks The function replaces any existing value for the given @a attr_name.
 *
 * @param[in] payload The SmartThings payload handle
 * @param[in] attr_name The attribute name
 * @param[in] value The value to set
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_RESOURCE_ERROR_NONE Successful
 * @retval #SMARTTHINGS_RESOURCE_ERROR_INVALID_PARAMETER Invalid parameter
 */
int smartthings_payload_set_bool(smartthings_payload_h payload, const char *attr_name, bool value);

/**
 * @brief Sets a double value for the attribute name.
 * @since_ses 1
 *
 * @remarks The @a attr_name is key value, one of several properties of the resource type.
 * @remarks The function replaces any existing value for the given @a attr_name.
 *
 * @param[in] payload The SmartThings payload handle
 * @param[in] attr_name The attribute name
 * @param[in] value The value to set
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_RESOURCE_ERROR_NONE Successful
 * @retval #SMARTTHINGS_RESOURCE_ERROR_INVALID_PARAMETER Invalid parameter
 */
int smartthings_payload_set_double(smartthings_payload_h payload, const char *attr_name, double value);

/**
 * @brief Sets a string value for the attribute name.
 * @since_ses 1
 *
 * @remarks The @a attr_name is key value, one of several properties of the resource type.
 * @remarks The function replaces any existing value for the given @a attr_name.
 *
 * @param[in] payload The SmartThings payload handle
 * @param[in] attr_name The attribute name
 * @param[in] value The value to set
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_RESOURCE_ERROR_NONE Successful
 * @retval #SMARTTHINGS_RESOURCE_ERROR_INVALID_PARAMETER Invalid parameter
 */
int smartthings_payload_set_string(smartthings_payload_h payload, const char *attr_name, const char *value);

/**
 * @brief Sets a byte string value and length for the attribute name.
 * @since_ses 1
 *
 * @remarks The @a attr_name is key value, one of several properties of the resource type.
 * @remarks The function replaces any existing value for the given @a attr_name.
 *
 * @param[in] payload The SmartThings payload handle
 * @param[in] attr_name The attribute name
 * @param[in] value The value to set
 * @param[in] length The size of value
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_RESOURCE_ERROR_NONE Successful
 * @retval #SMARTTHINGS_RESOURCE_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SMARTTHINGS_RESOURCE_ERROR_OPERATION_FAILED Operation failed
 */
int smartthings_payload_set_byte_string(smartthings_payload_h payload, const char *attr_name, const char *value, unsigned int length);

/**
 * @brief Sets an object value for the attribute name.
 * @since_ses 1
 *
 * @remarks The @a attr_name is key value, one of several properties of the resource type.
 * @remarks The @a value is SmartThings payload handle.
 * @remarks The function replaces any existing value for the given @a attr_name.
 *
 * @param[in] payload The SmartThings payload handle
 * @param[in] attr_name The attribute name
 * @param[in] value The value to set
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_RESOURCE_ERROR_NONE Successful
 * @retval #SMARTTHINGS_RESOURCE_ERROR_INVALID_PARAMETER Invalid parameter
 */
int smartthings_payload_set_object(smartthings_payload_h payload, const char *attr_name, smartthings_payload_h value);

/**
 * @brief Sets an integer array for the attribute name.
 * @since_ses 1
 *
 * @remarks The @a attr_name is key value, one of several properties of the resource type.
 * @remarks The function replaces any existing array for the given @a attr_name.
 *
 * @param[in] payload The SmartThings payload handle
 * @param[in] attr_name The attribute name
 * @param[in] array The array associated with the given attribute name
 * @param[in] length The length of @a array
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_RESOURCE_ERROR_NONE Successful
 * @retval #SMARTTHINGS_RESOURCE_ERROR_INVALID_PARAMETER Invalid parameter
 */
int smartthings_payload_set_int_array(smartthings_payload_h payload, const char *attr_name, const int *array, unsigned int length);

/**
 * @brief Sets a boolean array for the attribute name.
 * @since_ses 1
 *
 * @remarks The @a attr_name is key value, one of several properties of the resource type.
 * @remarks The function replaces any existing array for the given @a attr_name.
 *
 * @param[in] payload The SmartThings payload handle
 * @param[in] attr_name The attribute name
 * @param[in] array The array associated with the given attribute name
 * @param[in] length The length of @a array
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_RESOURCE_ERROR_NONE Successful
 * @retval #SMARTTHINGS_RESOURCE_ERROR_INVALID_PARAMETER Invalid parameter
 */
int smartthings_payload_set_bool_array(smartthings_payload_h payload, const char *attr_name, const bool *array, unsigned int length);

/**
 * @brief Sets a double array for the attribute name.
 * @since_ses 1
 *
 * @remarks The @a attr_name is key value, one of several properties of the resource type.
 * @remarks The function replaces any existing array for the given @a attr_name.
 *
 * @param[in] payload The SmartThings payload handle
 * @param[in] attr_name The attribute name
 * @param[in] array The array associated with the given attribute name
 * @param[in] length The length of @a array
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_RESOURCE_ERROR_NONE Successful
 * @retval #SMARTTHINGS_RESOURCE_ERROR_INVALID_PARAMETER Invalid parameter
 */
int smartthings_payload_set_double_array(smartthings_payload_h payload, const char *attr_name, const double *array, unsigned int length);

/**
 * @brief Sets a string array for the attribute name.
 * @since_ses 1
 *
 * @remarks The @a attr_name is key value, one of several properties of the resource type.
 * @remarks The function replaces any existing array for the given @a attr_name.
 *
 * @param[in] payload The SmartThings payload handle
 * @param[in] attr_name The attribute name
 * @param[in] array The array associated with the given attribute name
 * @param[in] length The length of @a array
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_RESOURCE_ERROR_NONE Successful
 * @retval #SMARTTHINGS_RESOURCE_ERROR_INVALID_PARAMETER Invalid parameter
 */
int smartthings_payload_set_string_array(smartthings_payload_h payload, const char *attr_name, const char **array, unsigned int length);

/**
 * @brief Sets an object array for the attribute name.
 * @since_ses 1
 *
 * @remarks The @a attr_name is key value, one of several properties of the resource type.
 * @remarks The function replaces any existing array for the given @a attr_name.
 *
 * @param[in] payload The SmartThings payload handle
 * @param[in] attr_name The attribute name
 * @param[in] array The array associated with the given attribute name
 * @param[in] length The length of @a array
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_RESOURCE_ERROR_NONE Successful
 * @retval #SMARTTHINGS_RESOURCE_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SMARTTHINGS_RESOURCE_ERROR_OUT_OF_MEMORY Out of memory
 */
int smartthings_payload_set_object_array(smartthings_payload_h payload, const char *attr_name, smartthings_payload_h *array, unsigned int length);

/**
 * @brief Adds a payload for child resource of collection resource.
 * @since_ses 1
 *
 * @remarks The @a resource_uri is key value, one of several child resources of the collection resource.
 * @remarks The @a value is SmartThings payload handle.
 * @remarks The function replaces any existing payload for the given @a resource_uri.
 *
 * @param[in] payload The SmartThings payload handle
 * @param[in] resource_uri The resource URI of child resource
 * @param[in] value The payload associated with the given resource URI
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_RESOURCE_ERROR_NONE Successful
 * @retval #SMARTTHINGS_RESOURCE_ERROR_INVALID_PARAMETER Invalid parameter
 */
int smartthings_payload_add_collection_object(smartthings_payload_h payload, const char *resource_uri, smartthings_payload_h value);

/**
 * @brief Gets an integer value for the attribute name.
 * @since_ses 1
 *
 * @remarks The @a attr_name is key value, one of several properties of the resource type.
 *
 * @param[in] payload The SmartThings payload handle
 * @param[in] attr_name The attribute name
 * @param[out] value The value associated with the given attribute name
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_RESOURCE_ERROR_NONE Successful
 * @retval #SMARTTHINGS_RESOURCE_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SMARTTHINGS_RESOURCE_ERROR_NO_DATA No data
 */
int smartthings_payload_get_int(smartthings_payload_h payload, const char *attr_name, int *value);

/**
 * @brief Gets a boolean value for the attribute name.
 * @since_ses 1
 *
 * @remarks The @a attr_name is key value, one of several properties of the resource type.
 *
 * @param[in] payload The SmartThings payload handle
 * @param[in] attr_name The attribute name
 * @param[out] value The value associated with the given attribute name
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_RESOURCE_ERROR_NONE Successful
 * @retval #SMARTTHINGS_RESOURCE_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SMARTTHINGS_RESOURCE_ERROR_NO_DATA No data
 */
int smartthings_payload_get_bool(smartthings_payload_h payload, const char *attr_name, bool *value);

/**
 * @brief Gets a double value for the attribute name.
 * @since_ses 1
 *
 * @remarks The @a attr_name is key value, one of several properties of the resource type.
 *
 * @param[in] payload The SmartThings payload handle
 * @param[in] attr_name The attribute name
 * @param[out] value The value associated with the given attribute name
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_RESOURCE_ERROR_NONE Successful
 * @retval #SMARTTHINGS_RESOURCE_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SMARTTHINGS_RESOURCE_ERROR_NO_DATA No data
 */
int smartthings_payload_get_double(smartthings_payload_h payload, const char *attr_name, double *value);

/**
 * @brief Gets a string value for the attribute name.
 * @since_ses 1
 *
 * @remarks The @a attr_name is key value, one of several properties of the resource type.
 * @remarks The @a value should be released using free().
 *
 * @param[in] payload The SmartThings payload handle
 * @param[in] attr_name The attribute name
 * @param[out] value The value associated with the given attribute name
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_RESOURCE_ERROR_NONE Successful
 * @retval #SMARTTHINGS_RESOURCE_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SMARTTHINGS_RESOURCE_ERROR_NO_DATA No data
 */
int smartthings_payload_get_string(smartthings_payload_h payload, const char *attr_name, char **value);

/**
 * @brief Gets a byte string value and length for the attribute name.
 * @since_ses 1
 *
 * @remarks The @a attr_name is key value, one of several properties of the resource type.
 * @remarks The @a value should be released using free().
 *
 * @param[in] payload The SmartThings payload handle
 * @param[in] attr_name The attribute name
 * @param[out] value The value associated with the given attribute name
 * @param[out] length The size of value
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_RESOURCE_ERROR_NONE Successful
 * @retval #SMARTTHINGS_RESOURCE_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SMARTTHINGS_RESOURCE_ERROR_NO_DATA No data
 */
int smartthings_payload_get_byte_string(smartthings_payload_h payload, const char *attr_name, char **value, unsigned int *length);

/**
 * @brief Gets an object value for the attribute name.
 * @since_ses 1
 *
 * @remarks The @a attr_name is key value, one of several properties of the resource type.
 * @remarks The @a value is SmartThings payload handle.
 * @remarks The @a value must be released using smartthings_payload_release_object().
 *
 * @param[in] payload The SmartThings payload handle
 * @param[in] attr_name The attribute name
 * @param[out] value The value associated with the given attribute name
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_RESOURCE_ERROR_NONE Successful
 * @retval #SMARTTHINGS_RESOURCE_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SMARTTHINGS_RESOURCE_ERROR_OUT_OF_MEMORY Out of memory
 * @retval #SMARTTHINGS_RESOURCE_ERROR_NO_DATA No data
 */
int smartthings_payload_get_object(smartthings_payload_h payload, const char *attr_name, smartthings_payload_h *value);

/**
 * @brief Gets an integer array for the attribute name.
 * @since_ses 1
 *
 * @remarks The @a attr_name is key value, one of several properties of the resource type.
 * @remarks The @a array must be released using smartthings_payload_release_int_array().
 *
 * @param[in] payload The SmartThings payload handle
 * @param[in] attr_name The attribute name
 * @param[out] array The array associated with the given attribute name
 * @param[out] length The length of @a array
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_RESOURCE_ERROR_NONE Successful
 * @retval #SMARTTHINGS_RESOURCE_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SMARTTHINGS_RESOURCE_ERROR_OUT_OF_MEMORY Out of memory
 * @retval #SMARTTHINGS_RESOURCE_ERROR_NO_DATA No data
 *
 * @see smartthings_payload_release_int_array()
 */
int smartthings_payload_get_int_array(smartthings_payload_h payload, const char *attr_name, int **array, unsigned int *length);

/**
 * @brief Gets a boolean array for the attribute name.
 * @since_ses 1
 *
 * @remarks The @a attr_name is key value, one of several properties of the resource type.
 * @remarks The @a array must be released using smartthings_payload_release_bool_array().
 *
 * @param[in] payload The SmartThings payload handle
 * @param[in] attr_name The attribute name
 * @param[out] array The array associated with the given attribute name
 * @param[out] length The length of @a array
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_RESOURCE_ERROR_NONE Successful
 * @retval #SMARTTHINGS_RESOURCE_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SMARTTHINGS_RESOURCE_ERROR_OUT_OF_MEMORY Out of memory
 * @retval #SMARTTHINGS_RESOURCE_ERROR_NO_DATA No data
 *
 * @see smartthings_payload_release_bool_array()
 */
int smartthings_payload_get_bool_array(smartthings_payload_h payload, const char *attr_name, bool **array, unsigned int *length);

/**
 * @brief Gets a double array for the attribute name.
 * @since_ses 1
 *
 * @remarks The @a attr_name is key value, one of several properties of the resource type.
 * @remarks The @a array must be released using smartthings_payload_release_double_array().
 *
 * @param[in] payload The SmartThings payload handle
 * @param[in] attr_name The attribute name
 * @param[out] array The array associated with the given attribute name
 * @param[out] length The length of @a array
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_RESOURCE_ERROR_NONE Successful
 * @retval #SMARTTHINGS_RESOURCE_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SMARTTHINGS_RESOURCE_ERROR_OUT_OF_MEMORY Out of memory
 * @retval #SMARTTHINGS_RESOURCE_ERROR_NO_DATA No data
 *
 * @see smartthings_payload_release_double_array()
 */
int smartthings_payload_get_double_array(smartthings_payload_h payload, const char *attr_name, double **array, unsigned int *length);

/**
 * @brief Gets a string array for the attribute name.
 * @since_ses 1
 *
 * @remarks The @a attr_name is key value, one of several properties of the resource type.
 * @remarks The @a array must be released using smartthings_payload_release_string_array().
 *
 * @param[in] payload The SmartThings payload handle
 * @param[in] attr_name The attribute name
 * @param[out] array The array associated with the given attribute name
 * @param[out] length The length of @a array
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_RESOURCE_ERROR_NONE Successful
 * @retval #SMARTTHINGS_RESOURCE_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SMARTTHINGS_RESOURCE_ERROR_OUT_OF_MEMORY Out of memory
 * @retval #SMARTTHINGS_RESOURCE_ERROR_NO_DATA No data
 *
 * @see smartthings_payload_release_string_array()
 */
int smartthings_payload_get_string_array(smartthings_payload_h payload, const char *attr_name, char ***array, unsigned int *length);

/**
 * @brief Gets an object array for the attribute name.
 * @since_ses 1
 *
 * @remarks The @a attr_name is key value, one of several properties of the resource type.
 * @remarks The @a array is a list of SmartThings payload handle.
 * @remarks The @a array must be released using smartthings_payload_release_object_array().
 *
 * @param[in] payload The SmartThings payload handle
 * @param[in] attr_name The attribute name
 * @param[out] array The array associated with the given attribute name
 * @param[out] length The length of @a array
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_RESOURCE_ERROR_NONE Successful
 * @retval #SMARTTHINGS_RESOURCE_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SMARTTHINGS_RESOURCE_ERROR_OUT_OF_MEMORY Out of memory
 * @retval #SMARTTHINGS_RESOURCE_ERROR_NO_DATA No data
 *
 * @see smartthings_payload_release_object_array()
 */
int smartthings_payload_get_object_array(smartthings_payload_h payload, const char *attr_name, smartthings_payload_h **array, unsigned int *length);

/**
 * @brief Gets a payload for child resource of collection resource.
 * @since_ses 1
 *
 * @remarks The @a resource_uri is key value, one of several child resources of the collection resource.
 * @remarks The @a value is SmartThings payload handle.
 * @remarks The @a value must be released using smartthings_payload_release_object().
 *
 * @param[in] payload The SmartThings payload handle
 * @param[in] resource_uri The resource URI of child resource
 * @param[out] value The payload associated with the given resource URI
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_RESOURCE_ERROR_NONE Successful
 * @retval #SMARTTHINGS_RESOURCE_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #SMARTTHINGS_RESOURCE_ERROR_OUT_OF_MEMORY Out of memory
 * @retval #SMARTTHINGS_RESOURCE_ERROR_NO_DATA No data
 */
int smartthings_payload_get_collection_object(smartthings_payload_h payload, const char *resource_uri, smartthings_payload_h *value);

/**
 * @brief Releases an integer array of the SmartThings payload.
 * @since_ses 1
 *
 * @param[in] array The array to release
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_RESOURCE_ERROR_NONE Successful
 * @retval #SMARTTHINGS_RESOURCE_ERROR_INVALID_PARAMETER Invalid parameter
 *
 * @see smartthings_payload_get_int_array()
 */
int smartthings_payload_release_int_array(int *array);

/**
 * @brief Releases a boolean array of the SmartThings payload.
 * @since_ses 1
 *
 * @param[in] array The array to release
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_RESOURCE_ERROR_NONE Successful
 * @retval #SMARTTHINGS_RESOURCE_ERROR_INVALID_PARAMETER Invalid parameter
 *
 * @see smartthings_payload_get_bool_array()
 */
int smartthings_payload_release_bool_array(bool *array);

/**
 * @brief Releases a double array of the SmartThings payload.
 * @since_ses 1
 *
 * @param[in] array The array to release
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_RESOURCE_ERROR_NONE Successful
 * @retval #SMARTTHINGS_RESOURCE_ERROR_INVALID_PARAMETER Invalid parameter
 *
 * @see smartthings_payload_get_double_array()
 */
int smartthings_payload_release_double_array(double *array);

/**
 * @brief Releases a string array of the SmartThings payload.
 * @since_ses 1
 *
 * @param[in] array The array to release
 * @param[in] length The length of @a array
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_RESOURCE_ERROR_NONE Successful
 * @retval #SMARTTHINGS_RESOURCE_ERROR_INVALID_PARAMETER Invalid parameter
 *
 * @see smartthings_payload_get_string_array()
 */
int smartthings_payload_release_string_array(char **array, unsigned int length);

/**
 * @brief Releases an object array of the SmartThings payload.
 * @since_ses 1
 *
 * @param[in] array The array to release
 * @param[in] length The length of @a array
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_RESOURCE_ERROR_NONE Successful
 * @retval #SMARTTHINGS_RESOURCE_ERROR_INVALID_PARAMETER Invalid parameter
 *
 * @see smartthings_payload_get_object_array()
 */
int smartthings_payload_release_object_array(smartthings_payload_h *array, unsigned int length);

/**
 * @brief Releases a SmartThings payload.
 * @since_ses 1
 *
 * @remarks The function is different with smartthings_payload_destroy().
 * @remarks The function releases only payload value that is obtained by smartthings_payload_get_object().
 *
 * @param[in] payload The payload to release
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #SMARTTHINGS_RESOURCE_ERROR_NONE Successful
 * @retval #SMARTTHINGS_RESOURCE_ERROR_INVALID_PARAMETER Invalid parameter
 *
 * @see smartthings_payload_get_object()
 */
int smartthings_payload_release_object(smartthings_payload_h payload);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __SAMSUNG_EXPERIENCE_SERVICE_SMARTTHINGS_PAYLOAD_H__ */
