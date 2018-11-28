/*
 * Copyright (c) 2018 Samsung Electronics Co., Ltd All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the License);
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

const SERVO_RANGE = {
	VERTICAL: {
		MIN: 15,
		MAX: 65
	},
	HORIZONTAL: {
		MIN: 5,
		MAX: 65
	}
};
const SERVO_STEP = {
	VERTICAL: (SERVO_RANGE.VERTICAL.MAX - SERVO_RANGE.VERTICAL.MIN) / 10,
	HORIZONTAL: (SERVO_RANGE.HORIZONTAL.MAX - SERVO_RANGE.HORIZONTAL.MIN) / 10,
};
const CONTROL_TYPE_VERTICAL = "vertical";
const CONTROL_TYPE_HORIZONTAL = "horizontal";

var capabilityServoMotor = {
	'href' : {
		v: "/capability/audioVolume/main/0",
		h: "/capability/switchLevel/main/0"
	},
	'valueV' : 50,
	'valueH' : 50,

	'update' : function() {
		for (var item in this.href) {
			ocfDevice.getRemoteRepresentation(this.href[item], this.onRepresentCallback);
		}
	},

	'onRepresentCallback' : function(result, deviceHandle, uri, rcsJsonString) {
		scplugin.log.debug(className, arguments.callee.name, result);
		scplugin.log.debug(className, arguments.callee.name, uri);

		if (result == "OCF_OK" || result == "OCF_RESOURCE_CHANGED" || result == "OCF_RES_ALREADY_SUBSCRIBED") {
			if (uri == capabilityServoMotor.href.v) {
				if(rcsJsonString["volume"] === undefined) return;
				capabilityServoMotor.valueV = rcsJsonString["volume"];
			} else if (uri == capabilityServoMotor.href.h) {
				if(rcsJsonString["dimmingSetting"] === undefined) return;
				capabilityServoMotor.valueH = rcsJsonString["dimmingSetting"];
			}
		}
	},

	'move' : function(type, value) {
		var setRcsJson = {};
		var href;
		scplugin.log.debug(className, arguments.callee.name, "Servo Motor type: " + type, "value: " + value);

		if (type == CONTROL_TYPE_VERTICAL) {
			setRcsJson["volume"] = value;
			href = this.href.v;
		} else if (type == CONTROL_TYPE_HORIZONTAL) {
			setRcsJson["dimmingSetting"] = value;
			href = this.href.h;
		} else {
			scplugin.log.debug(className, arguments.callee.name, "Servo Motor invalid type!");
		}

		ocfDevice.setRemoteRepresentation(href, setRcsJson, this.onRepresentCallback);
	},

	'moveDown' : function() {
		var nextVal = this.valueV + SERVO_STEP.VERTICAL;
		if (nextVal >= SERVO_RANGE.VERTICAL.MAX)
			nextVal = SERVO_RANGE.VERTICAL.MAX;

		this.move(CONTROL_TYPE_VERTICAL, nextVal);
	},

	'moveUp' : function() {
		var nextVal = this.valueV - SERVO_STEP.VERTICAL;
		if (nextVal <= SERVO_RANGE.VERTICAL.MIN)
			nextVal = SERVO_RANGE.VERTICAL.MIN;

		this.move(CONTROL_TYPE_VERTICAL, nextVal);
	},
	'moveLeft' : function() {
		var nextVal = this.valueH + SERVO_STEP.HORIZONTAL;
		if (nextVal >= SERVO_RANGE.HORIZONTAL.MAX)
			nextVal = SERVO_RANGE.HORIZONTAL.MAX;

		this.move(CONTROL_TYPE_HORIZONTAL, nextVal);
	},
	'moveRight' : function() {
		var nextVal = this.valueH - SERVO_STEP.HORIZONTAL;
		if (nextVal <= SERVO_RANGE.HORIZONTAL.MIN)
			nextVal = SERVO_RANGE.HORIZONTAL.MIN;

		this.move(CONTROL_TYPE_HORIZONTAL, nextVal);
	}
}
