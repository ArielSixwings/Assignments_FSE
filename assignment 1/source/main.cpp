#include "semaphore.h"
#include "../includes/trafficIntersection.h"
#include "../includes/embeddedOutputs.h"

int main (void){
	std::cout << "Trafic lights" << std::endl;

	wiringPiSetup();
	
	trafficIntersection theIntersection(5,10,5,10,3);
	// theIntersection.PrintInTime();
	theIntersection.controlIntersection();
}

//ssh arielserafim@164.41.98.17