#pragma once
class testcase
{
public:
	const int HIGH = 1;
	const int LOW = 0;
	const int PHOTO_RESISTOR_WORKING_VALUE = 100;

private:
	bool isInAutoLightMode;
	bool isInEmergencyMode;

public:
	testcase();
	int lightDetection(int photoResistorValue);
	int shortHeadLights(int headLightsBtnOneState, int headLightsBtnTwoState);
	int longHeadLights(int headLightsBtnOneState, int headLightsBtnTwoState);
	int rightTurnLights(int rightTurnBtn);
	int leftTurnLights(int leftTurnBtn);
	int emergencyLights(int emergencyLightsBtn);
	int stopLights(int stopLightsBtn);
};

