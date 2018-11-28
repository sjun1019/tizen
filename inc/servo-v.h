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

#ifndef __SERVO_V_H__
#define __SERVO_V_H__

#include "servo-type.h"

int servo_v_initialize(void);
int servo_v_finalize(void);
int servo_v_state_set(double value, const char *pass_key);
int servo_v_state_get(double *value);
int servo_v_state_changed_cb_set(
	const char *callback_key, servo_state_changed_cb callback, void *cb_data);

#endif /* __SERVO_V_H__ */
