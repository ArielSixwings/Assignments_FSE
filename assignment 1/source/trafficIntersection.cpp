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

void trafficIntersection::printInTime(){
	
	eventHandler timeManager(5,10,8000);
	timeManager.openServer();


	this->states[1].print();
	
	std::thread Listener(work,timeManager);
	timeManager.handleTime();
	// sleep(this->maxGreenTime);
	
	this->states[2].print();
	sleep(this->yellowTime);
	this->states[3].print();
	sleep(1);
	this->states[4].print();
	sleep(this->minGreenTime);
	this->states[5].print();
	sleep(this->yellowTime);
	this->states[0].print();
	Listener.join();
}

#include "../includes/embeddedInputs.h"


void trafficIntersection::listenButton(int pin){
	wiringPiIRS(pin,INT_EDGE_RISING,changeTime);
}
void changeTime(){
	useTime = minTime;
}