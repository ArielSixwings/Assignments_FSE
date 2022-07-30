#include "../includes/trafficIntersection.h"

using namespace std::literals::chrono_literals;

trafficIntersection::trafficIntersection(){

	this->buttonOne = this->theMap[8];
	this->buttonTwo = this->theMap[7];

	this->carSensorOne = this->theMap[14];
	this->carSensorTwo = this->theMap[15];

	this->velocityOneA = this->theMap[23];
	this->velocityOneB = this->theMap[18];
	this->velocityTwoA = this->theMap[25];
	this->velocityTwoB = this->theMap[24];
	
	pinMode(this->theMap[8], INPUT);
	pinMode(this->theMap[7], INPUT);
	
	pinMode(this->theMap[14], INPUT);
	pinMode(this->theMap[15], INPUT);

	pinMode(this->theMap[18], INPUT);
	pinMode(this->theMap[23], INPUT);
	pinMode(this->theMap[24], INPUT);
	pinMode(this->theMap[25], INPUT);
}

void changeTime(){
	useTime = minTime;
}

void getTimeStart(){
	timeStart = std::chrono::high_resolution_clock::now();
}

void getTimeEnd(){
	timeEnd = std::chrono::high_resolution_clock::now();
	
	std::chrono::duration<float> duration = timeEnd - timeStart;
	
	velocity = 3.6*1/float(duration.count());
	
	std::cout << "velocity: "<< velocity << std::endl;

}

void trafficIntersection::listenButton(int pin){
	wiringPiISR(pin,INT_EDGE_RISING,changeTime);
}

void trafficIntersection::getVelocity(int sensorA, int sensorB){
	wiringPiISR(sensorA, INT_EDGE_RISING,getTimeStart);
	wiringPiISR(sensorB, INT_EDGE_RISING,getTimeEnd);
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

	std::cout << "Returning to proced to new state: time: " << useTime << std::endl;
	useTime = 2*minTime;
}

void trafficIntersection::controlIntersection(){
	this->listenButton(this->buttonOne);
	this->listenButton(this->buttonTwo);

	this->listenButton(this->carSensorOne);
	this->listenButton(this->carSensorTwo);

	this->theSemaphore.changeStates(5);//off 		off
	
	std::this_thread::sleep_for(5s);
	for (int i = 0; i < 100; ++i){
		std::cout << "Start new iteration" << std::endl;
		

		this->theSemaphore.changeStates(0);//green 		red
		this->getVelocity(this->velocityOneA,this->velocityOneB);
		this->manageTime();
		
		this->theSemaphore.changeStates(1);//yellow 	red
		std::this_thread::sleep_for(3s);
		
		this->theSemaphore.changeStates(2);//red 		red
		std::this_thread::sleep_for(1s);
		
		this->theSemaphore.changeStates(3);//red 		green
		std::this_thread::sleep_for(5s);

		this->theSemaphore.changeStates(4);//red 		yellow
		std::this_thread::sleep_for(3s);

		this->theSemaphore.changeStates(2);//red 		red
		std::this_thread::sleep_for(1s);
	}

}