#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <iostream>
#include "embeddedOutputs.h"

class semaphore{
	
public:
	int states[6];
	embeddedOutputs lights;
	
	semaphore(int theStates[6]);
	// bool setLightsPins();
	void print();

};

#endif //SEMAPHORE_H