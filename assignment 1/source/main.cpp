#include "semaphore.h"
#include "../includes/trafficIntersection.h"

int main (void){
	std::cout << "Trafic lights" << std::endl;

	wiringPiSetup();
	
	trafficIntersection theIntersection;
	theIntersection.controlIntersection();
}

//ssh arielserafim@164.41.98.17