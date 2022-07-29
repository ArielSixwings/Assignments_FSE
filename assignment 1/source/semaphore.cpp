#include "../includes/semaphore.h"

semaphore::semaphore(){

	int conf0[6] = {1,0,0,0,0,1}; //green 		red
	int conf1[6] = {0,1,0,0,0,1}; //yellow 		red
	int conf2[6] = {0,0,1,0,0,1}; //red 		red
	int conf3[6] = {0,0,1,1,0,0}; //red 		green
	int conf4[6] = {0,0,1,0,1,0}; //red 		yellow	
	int conf5[6] = {0,0,0,0,0,0}; //off 		off
	int conf6[6] = {0,1,0,0,1,0}; //yellow	yellow

	for (int i = 0; i < 6; ++i){
		this->states[0][i] = conf0[i];
		this->states[1][i] = conf1[i];
		this->states[2][i] = conf2[i];
		this->states[3][i] = conf3[i];
		this->states[4][i] = conf4[i];
		this->states[5][i] = conf5[i];
		this->states[6][i] = conf6[i];
	}
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
		int pins[6] = {1,26,21,20,16,12};
		this->setLightsPins(pins);
		return;
	}
	int pins[6] = {2,3,11,0,5,6};
	this->setLightsPins(pins);
}

void semaphore::print(){
	for (int i = 0; i < 6; ++i){
		std::cout << states[i];
	}
	std::cout << std::endl;
}

bool semaphore::changeStates(int state){
	if (state < 0 or state > 6){
		std::cout << "invalid state" << std::endl;
		return false;
	}

	this->lights.onOff(this->states[state]);
	return true;
}