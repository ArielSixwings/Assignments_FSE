#include "semaphore.h"
#include "../includes/trafficIntersection.h"
#include "../includes/embeddedOutputs.h"

int main (void){
	std::cout << "Trafic lights" << std::endl;

	wiringPiSetup();
	pinMode(26, OUTPUT);
	digitalWrite(26, 1);
}

//ssh arielserafim@164.41.98.17