#include "../includes/trafficIntersection.h"

using namespace std::literals::chrono_literals;

trafficIntersection::trafficIntersection(int theminGreenTime,
										int themaxGreenTime,
										int theminRedTime,
										int themaxRedTime,
										int theyellowTime)
	{
	this->minGreenTime = theminGreenTime;
	this->maxGreenTime = themaxGreenTime;
	this->minRedTime = theminRedTime;
	this->maxRedTime = themaxRedTime;
	this->yellowTime = theyellowTime;

	minTime = this->minGreenTime;
	useTime = this->maxGreenTime;

	this->buttonOne = this->theMap[8];
	this->buttonTwo = this->theMap[8];
}

void trafficIntersection::print(){
	std::cout << "states" << std::endl;
	std::cout << this->minGreenTime << "  " << this->maxGreenTime << std::endl;
	std::cout << this->yellowTime << std::endl;
	std::cout << this->minRedTime << "  " << this->maxRedTime << std::endl;
}

void changeTime(){
	useTime = minTime;
}

void trafficIntersection::listenButton(int pin){
	wiringPiISR(pin,INT_EDGE_RISING,changeTime);
}


void trafficIntersection::manageTime(){
	

	auto start = std::chrono::high_resolution_clock::now();
	auto end = std::chrono::high_resolution_clock::now();
	
	std::chrono::duration<float> duration = end - start;

	for (int i = 0; duration < std::chrono::duration<float>(useTime); ++i){
		std::this_thread::sleep_for(0.1s);
		
		end = std::chrono::high_resolution_clock::now();
		duration = end - start;
	}

	useTime = this->maxGreenTime;
	std::cout << "out of for, returning to proced to new state" << std::endl;
}

void trafficIntersection::controlIntersection(){
	this->theSemaphore.setDefaultGroup(1);
	//changeStates
	this->listenButton(this->buttonOne);
	this->listenButton(this->buttonTwo);

	for (int i = 0; i < 100; ++i){
		this->theSemaphore.changeStates(0);//green 		red
		this->manageTime();
		
		this->theSemaphore.changeStates(1);//yellow 	red
		std::this_thread::sleep_for(1s);
		// sleep(this->yellowTime);
		
		this->theSemaphore.changeStates(2);//red 		red
		std::this_thread::sleep_for(1s);
		// sleep(1);
		
		this->theSemaphore.changeStates(3);//red 		green
		std::this_thread::sleep_for(1s);
		// sleep(this->minGreenTime);

		this->theSemaphore.changeStates(4);//red 		yellow
		std::this_thread::sleep_for(1s);	
		// sleep(this->yellowTime);

		this->theSemaphore.changeStates(2);//red 		red
		std::this_thread::sleep_for(1s);
	}

}