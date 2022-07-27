#include "../includes/semaphore.h"

semaphore::semaphore(int thelights[6]){
	for (int i = 0; i < 6; ++i){
		lights[i] = thelights[i];
	}
}


void semaphore::Print(){
	for (int i = 0; i < 6; ++i){
		std::cout << lights[i];
	}
	std::cout << std::endl;
}