#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include "pinMap.h"
#include <iostream>

class semaphore : pinMap{
	
public:
	int** states;
	
	semaphore();
	void changeStates(int state);
	void setOutputs();
};

#endif //SEMAPHORE_H