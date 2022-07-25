#include "trafficIntersection.h"


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
}

void trafficIntersection::Print(){
	std::cout << "states" << std::endl;
	for (int i = 0; i < states.size(); ++i){
		this->states[i].Print();
	}

	std::cout << this->minGreenTime << "  " << this->maxGreenTime << std::endl;
	std::cout << this->yellowTime << std::endl;
	std::cout << this->minRedTime << "  " << this->maxRedTime << std::endl;
}

void trafficIntersection::PrintInTime(){
	this->states[1].Print();
	sleep(this->minGreenTime);
	this->states[2].Print();
	sleep(this->yellowTime);
	this->states[3].Print();
	sleep(1);
	this->states[4].Print();
	sleep(this->minGreenTime);
	this->states[5].Print();
	sleep(this->yellowTime);
	this->states[0].Print();
}

	// void flashingAmber(){

	// }