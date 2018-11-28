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

#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#define MV_RESULT_COUNT_MAX 30
#define MV_RESULT_LENGTH_MAX (MV_RESULT_COUNT_MAX * 4) //4(x, y, w, h) * COUNT
#define IMAGE_INFO_MAX ((8 * MV_RESULT_LENGTH_MAX) + 4)

#define IMAGE_WIDTH 320
#define IMAGE_HEIGHT 240
#define CAMERA_IMAGE_QUALITY 100 //1~100
#define CAMERA_PREVIEW_INTERVAL_MIN 20

//카메라와 모터에 따라 최적화 필요한 값 --------------------------------
#define SERVO_MOTOR_VERTICAL_MIN 0
#define SERVO_MOTOR_VERTICAL_MAX 100
#define SERVO_MOTOR_VERTICAL_CENTER ((SERVO_MOTOR_VERTICAL_MIN + SERVO_MOTOR_VERTICAL_MAX) / 2)
#define SERVO_MOTOR_HORIZONTAL_MIN 0
#define SERVO_MOTOR_HORIZONTAL_MAX 100
#define SERVO_MOTOR_HORIZONTAL_CENTER ((SERVO_MOTOR_HORIZONTAL_MIN + SERVO_MOTOR_HORIZONTAL_MAX) / 2)

// 70CM 앞 물체가 화면의 서보모터 이동단위(1/20) 만큼 이동에 필요한 값 (실측)
#define SERVO_MOTOR_VERTICAL_STEP 1
#define SERVO_MOTOR_HORIZONTAL_STEP 2 //1.25

#endif
