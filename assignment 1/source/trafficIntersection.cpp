#include "../includes/trafficIntersection.h"

using namespace std::literals::chrono_literals;

void changeTime(){
	useTime = minTime;
}

void getTimeStart(){
	timeStart = std::chrono::high_resolution_clock::now();
}

void checkMainRedLight(){
	if ((roadStatus == MAIN_ROAD_RED) or (roadStatus == BOTH_ROAD_RED)){
		mainRoadInfraction++;
		totalInfraction++;
	}
}

void getTimeEnd(){
	timeEnd = std::chrono::high_resolution_clock::now();
	
	std::chrono::duration<float> duration = timeEnd - timeStart;
	
	velocity = 3.6*1/float(duration.count());
	
	std::cout << "velocity: "<< velocity << std::endl;
	if (velocity > 66){
		std::cout << "VELOCITY Infraction" << std::endl;
		velocityInfraction++;
		totalInfraction++;
	}
	checkMainRedLight();
}


void checkSecondaryRedLight(){
	if ((roadStatus == SECONDARY_ROAD_RED) or (roadStatus == BOTH_ROAD_RED)){
		secondaryRoadInfraction++;
		totalInfraction++;
	}
}

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

	pinMode(this->theMap[23], INPUT);
	pinMode(this->theMap[18], INPUT);

	pinMode(this->theMap[25], INPUT);
	pinMode(this->theMap[24], INPUT);
}

void trafficIntersection::getVelocity(int sensorA, int sensorB){
	wiringPiISR(sensorA, INT_EDGE_FALLING,getTimeStart);
	wiringPiISR(sensorB, INT_EDGE_FALLING,getTimeEnd);
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

	std::cout << "Returning to proced to new state: time: " << useTime << std::endl;
	useTime = 2*minTime;
}

void trafficIntersection::mainRoadRedLightInfraction(int sensorA, int sensorB){
	wiringPiISR(sensorA, INT_EDGE_FALLING,checkMainRedLight);
	wiringPiISR(sensorB, INT_EDGE_FALLING,checkMainRedLight);
}

void trafficIntersection::secondaryRoadRedLightInfraction(int sensorA, int sensorB){
	wiringPiISR(sensorA, INT_EDGE_FALLING,checkSecondaryRedLight);
	wiringPiISR(sensorB, INT_EDGE_FALLING,checkSecondaryRedLight);
}

void trafficIntersection::controlIntersection(){
	this->listenButton(this->buttonOne);
	this->listenButton(this->buttonTwo);

	this->listenButton(this->carSensorOne);
	this->listenButton(this->carSensorTwo);

	this->getVelocity(this->velocityOneA,this->velocityOneB);
	this->getVelocity(this->velocityTwoA,this->velocityTwoB);

	this->secondaryRoadRedLightInfraction(this->carSensorOne,this->carSensorTwo);

	// this->getVelocity(this->velocityTwoA,this->velocityTwoB);
	
	this->theSemaphore.changeStates(5);//off 		off
	
	std::this_thread::sleep_for(5s);
	for (int i = 0; i < 100; ++i){
		std::cout << "Start new iteration" << std::endl;
		std::cout << "Main Road Infraction:" << mainRoadInfraction <<std::endl;
		std::cout << "Secondary Road Infraction:" << secondaryRoadInfraction <<std::endl;
		std::cout << "Total Infraction:" << totalInfraction <<std::endl;

		

		this->theSemaphore.changeStates(0);//green 		red
		roadStatus = SECONDARY_ROAD_RED;
		this->manageTime();
		
		this->theSemaphore.changeStates(1);//yellow 	red
		std::this_thread::sleep_for(3s);
		
		this->theSemaphore.changeStates(2);//red 		red
		roadStatus = BOTH_ROAD_RED;
		std::this_thread::sleep_for(1s);
		
		this->theSemaphore.changeStates(3);//red 		green
		roadStatus = MAIN_ROAD_RED;
		std::this_thread::sleep_for(5s);

		this->theSemaphore.changeStates(4);//red 		yellow
		std::this_thread::sleep_for(3s);

		this->theSemaphore.changeStates(2);//red 		red
		roadStatus = BOTH_ROAD_RED;
		std::this_thread::sleep_for(1s);
	}

}