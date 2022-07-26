#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <iostream>

class semaphore{
	
public:
	int lights[6];
	
	semaphore(int thelights[6]);	
	void Print();

};

#endif //SEMAPHORE_H