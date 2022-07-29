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