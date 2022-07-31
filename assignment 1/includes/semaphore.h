#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include "pinMap.h"
#include <iostream>

class semaphore : pinMap{
	
public:
	int** states;
	
	semaphore();
	void changeStates(bool useDeafault, int state);
	void setOutputs(bool useDeafault);
};

#endif //SEMAPHORE_H