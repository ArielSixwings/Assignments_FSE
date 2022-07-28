#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <iostream>
#include "embeddedOutputs.h"

class semaphore{
	
public:
	int states[6];
	embeddedOutputs lights;
	
	semaphore();
	bool changeStates(int state);
	void setDefaultGroup(int group);
	void print();

private:	
	bool setLightsPins(int pins[6]);

};

#endif //SEMAPHORE_H