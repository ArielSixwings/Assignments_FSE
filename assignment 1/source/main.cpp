#include "semaphore.h"
#include <thread>
#include "../includes/trafficIntersection.h"


void doOne(){
	trafficIntersection theIntersection(true);
	theIntersection.controlIntersection();

}

void doTwo(){
	trafficIntersection theIntersection(false);
	theIntersection.controlIntersection();

}


int main (void){
	std::cout << "Trafic lights" << std::endl;

	wiringPiSetup();
	
	std::thread intersectionOne(doOne);
	std::thread intersectionTwo(doTwo);

	intersectionOne.join();
	intersectionTwo.join();
}

//ssh arielserafim@164.41.98.17