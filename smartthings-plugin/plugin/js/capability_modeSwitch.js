/*
 * Copyright (c) 2015 - 2017 Samsung Electronics Co., Ltd All Rights Reserved
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

var capabilityModeSwitch = {
	'href' : {
		switch: "/capability/switch/main/0"
	},
	'controlMode' : "on",

	'update' : function() {
		ocfDevice.getRemoteRepresentation(this.href.switch, this.onRepresentCallback);
	},

	'onRepresentCallback' : function(result, deviceHandle, uri, rcsJsonString) {
		scplugin.log.debug(className, arguments.callee.name, result);
		scplugin.log.debug(className, arguments.callee.name, uri);

		if (result == "OCF_OK" || result == "OCF_RESOURCE_CHANGED" || result == "OCF_RES_ALREADY_SUBSCRIBED") {
			capabilityModeSwitch.controlMode = rcsJsonString["power"];
		}

		if (capabilityModeSwitch.controlMode == "off") {
			document.getElementById("auto_mode").setAttribute('data-state', 'on');
			document.getElementById("camera_controller").setAttribute('data-state', 'auto_mode_on');
			document.getElementById("auto_mode_check").checked = true;
		} else {
			document.getElementById("auto_mode").setAttribute('data-state', 'off');
			document.getElementById("camera_controller").setAttribute('data-state', 'auto_mode_off');
			document.getElementById("auto_mode_check").checked = false;
		}
	},

	'set' : function(state) {
		scplugin.log.debug(className, arguments.callee.name, "power : " + state);
		var setRcsJson = {};
		setRcsJson["power"] = state;
		ocfDevice.setRemoteRepresentation(this.href.switch, setRcsJson, this.onRepresentCallback);
	},

	'isControllable': function() {
		if (this.controlMode == 'on') {
			return true;
		} else {
			return false;
		}
	},

	'modeToggle' : function() {
		if (this.controlMode == "on") {
			this.set("off");
		} else {
			this.set("on");
		}
	}
}
