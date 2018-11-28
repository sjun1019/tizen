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

#ifndef __POSITION_FINDER_RESOURCE_LED_H__
#define __POSITION_FINDER_RESOURCE_LED_H__

#include <peripheral_io.h>

#define INPUT			PERIPHERAL_GPIO_DIRECTION_IN              /**< Input Mode */
#define OUTPUT_PULLUP	PERIPHERAL_GPIO_DIRECTION_OUT_INITIALLY_HIGH /**< Output mode with high value */
#define OUTPUT			PERIPHERAL_GPIO_DIRECTION_OUT_INITIALLY_LOW   /**< Output mode with low value */

#define HIGH 1
#define LOW 0

extern int digitalWrite(int pin_num, int write_value);
extern int digitalRead(int pin_num);
extern int pinMode(int pin_num, int mode);

extern void gpio_close(void);

#endif /* __POSITION_FINDER_RESOURCE_LED_H__ */
