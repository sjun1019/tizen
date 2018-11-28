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

var ocfDevice;
var capabilities = [capabilityModeSwitch, capabilityMotionSensor, capabilityServoMotor];
var className = "iot2018";

window.onload = function () {
	console.log("version : 0.0.1");
	registerTouchEvents();
	init();
};

function init() {
	console.log("-----------init-----------");
	scplugin.manager.getOCFDevices(getOCFDeviceCB);
}

function getOCFDeviceCB(devices) {
	console.log("getOCFDeviceCB : " + devices.length);

	for (var i in devices) {
		console.log("deviceHandle: " + devices[i].deviceHandle);
		console.log("deviceName: " + devices[i].deviceName);
		console.log("deviceType: " + devices[i].deviceType);
		console.log("metadata: " + devices[i].metadata);
	}

	setMainDevice(devices[0]);
	ocfDevice.subscribe(onRepresentCallback);

	for (var i = 0; i < capabilities.length; i++) {
		capabilities[i].update();
	}
}

function onRepresentCallback(result, deviceHandle, uri, rcsJsonString) {
	for (var i = 0; i < capabilities.length; i++) {
		var hrefObj = capabilities[i].href;

		for (var item in hrefObj) {
			if (hrefObj[item] == uri)
				capabilities[i].onRepresentCallback(result, deviceHandle, uri, rcsJsonString);
		}
	}
}

function registerTouchEvents() {
	var elements = document.getElementsByClassName("icon-move");
	// up-left-right-down

	// Move Up
	elements[0].addEventListener("touchstart", function() {
		if (!capabilityModeSwitch.isControllable()){
			return;
		}
		document.getElementById("camera_controller").className = "shadow-up";
	}, false);

	// Move Left
	elements[1].addEventListener("touchstart", function() {
		if (!capabilityModeSwitch.isControllable()){
			return;
		}
		document.getElementById("camera_controller").className = "shadow-left";
	}, false);

	// Move Right
	elements[2].addEventListener("touchstart", function() {
		if (!capabilityModeSwitch.isControllable()){
			return;
		}
		document.getElementById("camera_controller").className = "shadow-right";
	}, false);

	// Move Down
	elements[3].addEventListener("touchstart", function() {
		if (!capabilityModeSwitch.isControllable()){
			return;
		}
		document.getElementById("camera_controller").className = "shadow-down";
	}, false);

	for (var i = 0; i < elements.length; i++){
		elements[i].addEventListener("touchend", function() {
			document.getElementById("camera_controller").className = "";
		}, false);
	}
}

function setMainDevice(device) {
	scplugin.log.debug(className, arguments.callee.name, "set ocf device : " + device.deviceName);
	ocfDevice = device;
}

function backAction() {
	scplugin.manager.close();
}

function onModeBtnClicked() {
	capabilityModeSwitch.modeToggle();
}

function onMoveUpBtnClicked() {
	if (!capabilityModeSwitch.isControllable()){
		return;
	}
	capabilityServoMotor.moveUp();
}

function onMoveDownBtnClicked() {
	if (!capabilityModeSwitch.isControllable()){
		return;
	}
	capabilityServoMotor.moveDown();
}

function onMoveLeftBtnClicked() {
	if (!capabilityModeSwitch.isControllable()){
		return;
	}
	capabilityServoMotor.moveLeft();
}

function onMoveRightBtnClicked() {
	if (!capabilityModeSwitch.isControllable()){
		return;
	}
	capabilityServoMotor.moveRight();
}
