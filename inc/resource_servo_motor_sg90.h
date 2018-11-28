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

#ifndef __RESOURCE_SERVO_MOTOR_SG90_H__
#define __RESOURCE_SERVO_MOTOR_SG90_H__

void resource_close_servo_motor(int channel);

/**
 * This module is sample codes to handling Servo motors in Tizen platform.
 * Hardware is configured with SG90,
 * @param[in] channel
 * @param[in] duty_cycle_ms
 * @return 0 on success, otherwise a negative error value
  */
int resource_set_servo_motor_sg90_value(int channel, double duty_cycle_ms);

/**
 * This module is sample codes to handling Servo motors in Tizen platform.
 * Hardware is configured with SG90,
 * @param[in] channel
 * @param[in] percent
 * @return 0 on success, otherwise a negative error value
  */
int resource_rotate_servo_motor_by_percent(int channel, double percent);

#endif /* __RESOURCE_SERVO_MOTOR_SG90_H__ */
