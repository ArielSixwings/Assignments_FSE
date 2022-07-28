#include "../includes/semaphore.h"

semaphore::semaphore(int theStates[6]){
	for (int i = 0; i < 6; ++i){
		states[i] = theStates[i];
	}
}


void semaphore::print(){
	for (int i = 0; i < 6; ++i){
		std::cout << states[i];
	}
	std::cout << std::endl;
}