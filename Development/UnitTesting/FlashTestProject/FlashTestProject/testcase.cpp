#include "stdafx.h"
#include "testcase.h"

testcase::testcase() {
	isInAutoLightMode = false;
	isInEmergencyMode = false;
}

int testcase::lightDetection(int photoResistorValue) {
	if (photoResistorValue <= PHOTO_RESISTOR_WORKING_VALUE) {
		isInAutoLightMode = true;
		return HIGH;
	}
	else {
		if (isInAutoLightMode) {
			isInAutoLightMode = false;
		}
		return LOW;
	}
}

int testcase::shortHeadLights(int headLightsBtnOneState, int headLightsBtnTwoState) {
	if (!isInAutoLightMode) {
		if (headLightsBtnOneState == HIGH) {
			return LOW;
		}
		else if (headLightsBtnOneState == LOW && headLightsBtnTwoState == LOW) {
			return HIGH;
		}
		else {
			return HIGH;
		}
	}
	else {
		return HIGH;
	}
}

int testcase::longHeadLights(int headLightsBtnOneState, int headLightsBtnTwoState) {
	if (!isInAutoLightMode) {
		if (headLightsBtnOneState == HIGH) {
			return LOW;
		}
		else if (headLightsBtnOneState == LOW && headLightsBtnTwoState == LOW) {
			return LOW;
		}
		else {
			return HIGH;
		}
	}
	else {
		if (headLightsBtnTwoState == HIGH) {
			return HIGH;
		}
		else {
			return LOW;
		}
	}
}

int testcase::rightTurnLights(int rightTurnBtn) {
	if (!isInEmergencyMode) {
		if (rightTurnBtn == HIGH)
			return HIGH;
		else
			return LOW;
	}
	else {
		return LOW;
	}
}

int testcase::leftTurnLights(int leftTurnBtn) {
	if (!isInEmergencyMode) {
		if (leftTurnBtn == HIGH)
			return HIGH;
		else
			return LOW;
	}
	else {
		return LOW;
	}
}

int testcase::emergencyLights(int emergencyLightsBtn) {
	if (emergencyLightsBtn == HIGH) {
		if (!isInEmergencyMode) {
			isInEmergencyMode = true;
			return LOW;
		}
		return HIGH;
	}
	else {
		if (isInEmergencyMode) {
			isInEmergencyMode = false;
		}
		return LOW;
	}
}

int testcase::stopLights(int stopLightsBtn) {
	if (stopLightsBtn == HIGH)
		return HIGH;
	else
		return LOW;
}

