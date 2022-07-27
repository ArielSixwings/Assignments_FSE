#include "semaphore.h"
#include "../includes/trafficIntersection.h"
#include "../includes/embeddedOutputs.h"

int main (void){
	std::cout << "Trafic lights" << std::endl;

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
	


	int *pins = new int[12];

	pins[0] = 1;
	pins[1] = 2;
	pins[2] = 3;
	pins[3] = 26;
	pins[4] = 21;
	pins[5] = 11;
	pins[6] = 20;
	pins[7] = 0;
	pins[8] = 16;
	pins[9] = 5;
	pins[10] = 12;
	pins[11] = 6;

	embeddedOutputs outputs;
	outputs.printOutputs();
	// outputs.setOutput(pins);

	// trafficIntersection theIntersection(states,10,20,5,10,3);
	// theIntersection.PrintInTime();
}

//ssh arielserafim@164.41.98.17