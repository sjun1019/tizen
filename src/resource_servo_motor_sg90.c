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

#include <peripheral_io.h>
#include <glib.h>
#include "log.h"

#define ENABLE_SERVO_TIMEOUT

/* This value is only for Servo Motor - SG90 */
#define SERVO_MOTOR_DEFAULT_PERIOD 20.0
#define SERVO_MOTOR_DUTY_CYCLE_COUNTER_CLOCKWISE 0.9
#define SERVO_MOTOR_DUTY_CYCLE_CLOCKWISE 2.4

#ifdef ENABLE_SERVO_TIMEOUT
#define SERVO_TIMEOUT_INTERVAL 50  //150
#endif /* ENABLE_SERVO_TIMEOUT */

/* This APIs are only made for Eagleye530s */
/* There are 2 pins for PWM */
static peripheral_pwm_h g_pwm0_h;
static peripheral_pwm_h g_pwm2_h;

#ifdef ENABLE_SERVO_TIMEOUT
static guint g_timer_id0;
static guint g_timer_id2;

static gboolean __timeout_cb(void *data)
{
	int channel = GPOINTER_TO_INT(data);

	_D("pwm channel[%d] disable", channel);
	if (channel == 0 && g_pwm0_h) {
		peripheral_pwm_set_enabled(g_pwm0_h, false);
		g_timer_id0 = 0;
	} else if (channel == 2 && g_pwm2_h) {
		peripheral_pwm_set_enabled(g_pwm2_h, false);
		g_timer_id2 = 0;
	}
	return FALSE;
}

static void __remove_timeout_cb(int channel)
{
	if (channel == 0) {
		if (g_timer_id0) {
			g_source_remove(g_timer_id0);
			g_timer_id0 = 0;
		}
	} else if (channel == 2) {
		if (g_timer_id2) {
			g_source_remove(g_timer_id0);
			g_timer_id2 = 0;
		}
	}
}

static void __add_timeout_cb(int channel)
{
	if (channel == 0) {
		g_timer_id0 = g_timeout_add(SERVO_TIMEOUT_INTERVAL,
						__timeout_cb, GINT_TO_POINTER(channel));
	} else if (channel == 2) {
		g_timer_id2 = g_timeout_add(SERVO_TIMEOUT_INTERVAL,
						__timeout_cb, GINT_TO_POINTER(channel));
	}
}
#endif /* ENABLE_SERVO_TIMEOUT */

void resource_close_servo_motor(int channel)
{
#ifdef ENABLE_SERVO_TIMEOUT
	__remove_timeout_cb(channel);
#endif /* ENABLE_SERVO_TIMEOUT */

	if (channel == 0 && g_pwm0_h) {
		peripheral_pwm_close(g_pwm0_h);
		g_pwm0_h = NULL;
	} else if (channel == 2 && g_pwm2_h) {
		peripheral_pwm_close(g_pwm2_h);
		g_pwm2_h = NULL;
	}
}

int resource_set_servo_motor_sg90_value(int channel, double duty_cycle_ms)
{
	int ret = 0;
	peripheral_pwm_h *pwm_h = NULL;

	if (duty_cycle_ms >= SERVO_MOTOR_DEFAULT_PERIOD) {
		_E("Too large duty cycle");
		return -1;
	}

#ifdef ENABLE_SERVO_TIMEOUT
	__remove_timeout_cb(channel);
#endif /* ENABLE_SERVO_TIMEOUT */

	if (channel == 0) {
		pwm_h = &g_pwm0_h;
	} else if (channel == 2) {
		pwm_h = &g_pwm2_h;
	} else {
		_E("unsupported channel - %d", channel);
		return -1;
	}

	if (!*pwm_h) {
		ret = peripheral_pwm_open(0, channel, pwm_h);
		if (ret != PERIPHERAL_ERROR_NONE) {
			_E("failed to open servo motor with channel(%d) : %s", channel, get_error_message(ret));
			return -1;
		}
	}

	ret = peripheral_pwm_set_period(*pwm_h, SERVO_MOTOR_DEFAULT_PERIOD * 1000 * 1000);
	if (ret != PERIPHERAL_ERROR_NONE) {
		_E("failed to set period : %s", get_error_message(ret));
		return -1;
	}

	ret = peripheral_pwm_set_duty_cycle(*pwm_h, duty_cycle_ms * 1000 * 1000);
	if (ret != PERIPHERAL_ERROR_NONE) {
		_E("failed to set duty cycle : %s", get_error_message(ret));
		return -1;
	}

	ret = peripheral_pwm_set_enabled(*pwm_h, true);
	if (ret != PERIPHERAL_ERROR_NONE) {
		_E("failed to enable : %s", get_error_message(ret));
		return -1;
	}

#ifdef ENABLE_SERVO_TIMEOUT
	__add_timeout_cb(channel);
#endif /* ENABLE_SERVO_TIMEOUT */

	return 0;
}

int resource_rotate_servo_motor_by_percent(int channel, double percent)
{
	int ret = 0;
	double duty_cycle = 0.0f;

	duty_cycle = ((SERVO_MOTOR_DUTY_CYCLE_CLOCKWISE - SERVO_MOTOR_DUTY_CYCLE_COUNTER_CLOCKWISE)
			* (percent / 100.0))
			+ SERVO_MOTOR_DUTY_CYCLE_COUNTER_CLOCKWISE;

	ret = resource_set_servo_motor_sg90_value(channel, duty_cycle);

	return ret;
}
