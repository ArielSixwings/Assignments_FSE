#include "semaphore.h"
#include "../includes/trafficIntersection.h"
#include "../includes/embeddedOutputs.h"

int main (void){
	std::cout << "Trafic lights" << std::endl;

	wiringPiSetup();
	
	int conf1[6] = {0,0,1,0,0,1};
	int conf2[6] = {1,0,0,0,0,1};
	int conf3[6] = {0,1,0,0,0,1};
	int conf4[6] = {0,0,1,0,0,1};
	int conf5[6] = {0,0,1,1,0,0};
	int conf6[6] = {0,0,1,0,1,0};
	
	semaphore state1(conf1);
	semaphore state2(conf2);
	semaphore state3(conf3);
	semaphore state4(conf4);
	semaphore state5(conf5);
	semaphore state6(conf6);
	
	
	std::vector<semaphore> states;

	states.push_back(state1);
	states.push_back(state2);
	states.push_back(state3);
	states.push_back(state4);
	states.push_back(state5);
	states.push_back(state6);
	
	trafficIntersection theIntersection(states,5,10,5,10,3);
	// theIntersection.PrintInTime();
	theIntersection.controlIntersection();
}

//ssh arielserafim@164.41.98.17