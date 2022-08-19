#include "../includes/pid.h"


pid::pid(float refTemp){
	
	this->referenceTemperature = refTemp;

	// this->proportionalController = kp;
	// this->integralController = ki;
	// this->derivativeController = kd;

	this->period = 1.0;
}

pid::pid(float refTemp, float kp, float ki, float kd, float T){
	
	this->referenceTemperature = refTemp;

	this->proportionalController = kp;
	this->integralController = ki;
	this->derivativeController = kd;

	this->period = T;
}

float pid::boundedValue(float candidate){
	if(candidate >= MAXCONTROL){
		return MAXCONTROL;
	}

	if (candidate <= MINCONTROL){
		return MINCONTROL;
	}

	return candidate;
}

float pid::controlTemperature(float inputTemperature){
	
	float errorCandidate;
	float deltaError;
	float newTemperature;

	this->deltaTemperature = this->referenceTemperature - inputTemperature;
	errorCandidate = this->totalError + deltaTemperature;
	
	this->totalError = this->boundedValue(errorCandidate);
	deltaError = this->deltaTemperature - this->previusError;

	newTemperature = this->proportionalController*this->deltaTemperature    + 
					 this->integralController*this->totalError*this->period + 
					 (this->derivativeController*deltaError)/this->period;

	newTemperature = this->boundedValue(newTemperature);

	this->previusError = this->deltaTemperature;

	return newTemperature;
}