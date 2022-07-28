#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <iostream>
#include "embeddedOutputs.h"

class semaphore{
	
public:
	int states[6];
	embeddedOutputs lights;
	
	semaphore();
	bool setLightsPins(int pins[6]);
	bool changeStates(int state);
	void print();

};

#endif //SEMAPHORE_H