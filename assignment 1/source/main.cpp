#include "semaphore.h"
#include <thread>
#include "../includes/trafficIntersection.h"


static bool rasp;

void doOne(){
	trafficIntersection theIntersection(true,rasp);
	theIntersection.controlIntersection();

}

void doTwo(){
	trafficIntersection theIntersection(false,rasp);
	theIntersection.controlIntersection();

}


int main (void){
	int ans;
	wiringPiSetup();
	
	std::cout << "Use 0 if you are at rasp43 and 1 if you are at rasp44" << std::endl;
	std::cin >> ans;

	if (ans == 0){
		rasp = true;
	}else{
		rasp = false;
	}
	
	
	std::thread intersectionOne(doOne);
	std::thread intersectionTwo(doTwo);

	intersectionOne.join();
	intersectionTwo.join();
}

//ssh arielserafim@164.41.98.17