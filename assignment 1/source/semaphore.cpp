#include "../includes/semaphore.h"

semaphore::semaphore(){
	this->states[0] = {1,0,0,0,0,1}; //green 	red
	this->states[1] = {0,1,0,0,0,1}; //yellow 	red
	this->states[2] = {0,0,1,0,0,1}; //red 		red
	this->states[3] = {0,0,1,1,0,0}; //red 		green
	this->states[4] = {0,0,1,0,1,0}; //red 		yellow	
	this->states[5] = {0,0,0,0,0,0}; //off 		off
	this->states[0] = {0,0,0,0,0,0}; //yellow	yellow
}

bool semaphore::setLightsPins(int pins[6]){
	if (pins == NULL){
		std::cout << "invalid use of function setLightsPinns: null send as pins" << std::endl; 
		return false;
	}

	this->lights.setOutput(pins);
	this->lights.setGroup(pins);

	return true;
}

void semaphore::setDefaultGroup(int group){
	if (group){
		this->setLightsPins({1,26,21,20,16,12});
		return;
	}
	this->setLightsPins({2,3,11,0,5,6});
}

void semaphore::print(){
	for (int i = 0; i < 6; ++i){
		std::cout << states[i];
	}
	std::cout << std::endl;
}

bool semaphore::changeStates(int state){
	if (state < 0 or state > 5){
		std::cout << "invalid state" << std::endl:
		return false;
	}

	this->lights.onOff(this->states[state]);
	return true
}