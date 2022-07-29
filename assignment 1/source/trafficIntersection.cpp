#include "../includes/trafficIntersection.h"

trafficIntersection::trafficIntersection(std::vector<semaphore> thestates,
	int theminGreenTime,
	int themaxGreenTime,
	int theminRedTime,
	int themaxRedTime,
	int theyellowTime)
	{
		
	this->states = thestates;
		
	int conf0[6] = {0,0,0,0,0,0};
	semaphore state0(conf0);

	this->minGreenTime = theminGreenTime;
	this->maxGreenTime = themaxGreenTime;
	this->minRedTime = theminRedTime;
	this->maxRedTime = themaxRedTime;
	this->yellowTime = theyellowTime;

	minTime = this->minGreenTime;
	useTime = this->maxGreenTime;

	this->buttonOne = this->pinMap[8];
	this->buttonTwo = this->pinMap[8];
}

void trafficIntersection::print(){
	std::cout << "states" << std::endl;
	for (int i = 0; i < states.size(); ++i){
		this->states[i].Print();
	}

	std::cout << this->minGreenTime << "  " << this->maxGreenTime << std::endl;
	std::cout << this->yellowTime << std::endl;
	std::cout << this->minRedTime << "  " << this->maxRedTime << std::endl;
}

void trafficIntersection::listenButton(int pin){
	wiringPiIRS(pin,INT_EDGE_RISING,changeTime);
}

void changeTime(){
	useTime = minTime;
}

void trafficIntersection::manageTime(){
	using namespace std::literals::chrono_literals;

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
		sleep(this->yellowTime);
		
		this->theSemaphore.changeStates(2);//red 		red
		sleep(1);
		
		this->theSemaphore.changeStates(3);//red 		green
		sleep(this->minGreenTime);

		this->theSemaphore.changeStates(4);//red 		yellow	
		sleep(this->yellowTime);

		this->theSemaphore.changeStates(2);//red 		red
		sleep(1);
	}

}