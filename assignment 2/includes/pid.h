#ifndef PID_H
#define PID_H

#include <iostream>
// #include <wiringPi.h>

static float MAXCONTROL = 100.0;
static float MINCONTROL = -100.0;

class pid{

private:
	float totalError = 0.0;
	float previusError = 0.0;
	float referenceTemperature = 0.0;
	float deltaTemperature = 0.0;

	float proportionalController = 0.0; //kp
	float integralController = 0.0; 	//ki
	float derivativeController = 0.0;	//kd

	float period = 1.0;

public:
	pid(float refTemp);
	pid(float refTemp, float kp, float ki, float kd, float T);

	float controlTemperature(float inputTemperature);
	float boundedValue(float candidate);
};

#endif //PID_H