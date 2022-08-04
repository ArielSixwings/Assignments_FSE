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
		if (usedSSH){
			RASPA_mainRoadInfraction++;
			return;
		}
		RASPB_mainRoadInfraction++;
		// system("cvlc alarm.mp3");
	}
}

void getTimeEnd(){
	timeEnd = std::chrono::high_resolution_clock::now();
	
	std::chrono::duration<float> duration = timeEnd - timeStart;
	
	velocity = 3.6*1/float(duration.count());
	
	std::cout << "velocity: "<< velocity << std::endl;
	if (velocity > 66){
		if (usedSSH){
			RASPA_VelocityInfraction++;
			return;
		}
		RASPB_VelocityInfraction++;
		// system("cvlc alarm.mp3");
	}
	checkMainRedLight();
}


void checkSecondaryRedLight(){
	if ((roadStatus == SECONDARY_ROAD_RED) or (roadStatus == BOTH_ROAD_RED)){
		if (usedSSH){
			RASPA_secondaryRoadInfraction++;
			return;
		}
		RASPB_secondaryRoadInfraction++;
		// system("cvlc alarm.mp3");
	}
}

void recievCommands(client theClient){
	message = new(int);
	int recievedLength;


	if((recievedLength = recv(theClient.clientSocket, message, 16, 0)) < 0){
		std::cout << "Error at recv" << std::endl;
	}

}

trafficIntersection::trafficIntersection(bool defaultUse,bool rasp){

	usedSSH = rasp;

	if (defaultUse){
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

		this->useDefault = true;
		this->theSemaphore.setOutputs(true);
		return;
		
	}
	this->buttonOne = this->theMap[10];
	this->buttonTwo = this->theMap[9];

	this->carSensorOne = this->theMap[4];
	this->carSensorTwo = this->theMap[17];

	this->velocityOneA = this->theMap[22];
	this->velocityOneB = this->theMap[27];
	this->velocityTwoA = this->theMap[19];
	this->velocityTwoB = this->theMap[13];
		
	pinMode(this->theMap[10], INPUT);
	pinMode(this->theMap[9], INPUT);
		
	pinMode(this->theMap[4], INPUT);
	pinMode(this->theMap[17], INPUT);

	pinMode(this->theMap[22], INPUT);
	pinMode(this->theMap[27], INPUT);
	pinMode(this->theMap[19], INPUT);
	pinMode(this->theMap[13], INPUT);
	this->useDefault = false;
	this->theSemaphore.setOutputs(false);
}

void trafficIntersection::nightMode(){
	for (int i = 0; i < 100; ++i){
		this->theSemaphore.changeStates(this->useDefault,5);//off 		off
		std::this_thread::sleep_for(0.5s);
		this->theSemaphore.changeStates(this->useDefault,6);//yellow	yellow
	}
}

void trafficIntersection::emergencyMode(){
	this->theSemaphore.changeStates(this->useDefault,0);//green 		red
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

void trafficIntersection::reportToServer(client theClient){
	message = new(int[2]);
	
	if (this->useDefault){
		if (usedSSH){
			message[0] = 1;
			message[1] = RASPA_mainRoadInfraction;
			send(theClient.clientSocket,message,5,0);
			std::this_thread::sleep_for(0.3s);

			message[0] = 3;
			message[1] = RASPA_secondaryRoadInfraction;
			send(theClient.clientSocket,message,5,0);
			std::this_thread::sleep_for(0.3s);

			message[0] = 5;
			message[1] = RASPA_VelocityInfraction;
			send(theClient.clientSocket,message,5,0);
			std::this_thread::sleep_for(0.4s);
			return;
		}

		message[0] = 10;
		message[1] = RASPB_mainRoadInfraction;
		send(theClient.clientSocket,message,5,0);
		std::this_thread::sleep_for(0.3s);

		message[0] = 30;
		message[1] = RASPB_secondaryRoadInfraction;
		send(theClient.clientSocket,message,5,0);
		std::this_thread::sleep_for(0.3s);

		message[0] = 50;
		message[1] = RASPB_VelocityInfraction;
		send(theClient.clientSocket,message,5,0);
		std::this_thread::sleep_for(0.4s);
		return;		
	}

	if (usedSSH){
		message[0] = 2;
		message[1] = RASPA_mainRoadInfraction;
		send(theClient.clientSocket,message,5,0);
		std::this_thread::sleep_for(0.3s);
		
		message[0] = 4;
		message[1] = RASPA_secondaryRoadInfraction;
		send(theClient.clientSocket,message,5,0);
		std::this_thread::sleep_for(0.3s);

		message[0] = 6;
		message[1] = RASPA_VelocityInfraction;
		send(theClient.clientSocket,message,5,0);
		std::this_thread::sleep_for(0.4s);
		return;
	}
	message[0] = 20;
	message[1] = RASPB_mainRoadInfraction;
	send(theClient.clientSocket,message,5,0);
	std::this_thread::sleep_for(0.3s);
		
	message[0] = 40;
	message[1] = RASPB_secondaryRoadInfraction;
	send(theClient.clientSocket,message,5,0);
	std::this_thread::sleep_for(0.3s);

	message[0] = 60;
	message[1] = RASPB_VelocityInfraction;
	send(theClient.clientSocket,message,5,0);
	std::this_thread::sleep_for(0.4s);	
}

void setIp(char* theIP){
	theIP[0] = '1';
	theIP[1] = '6';
	theIP[2] = '4';
	theIP[3] = '.';
	theIP[4] = '4';
	theIP[5] = '1';
	theIP[6] = '.';
	theIP[7] = '9';
	theIP[8] = '8';
	theIP[9] = '.';
	theIP[10] = '1';
	theIP[11] = '7';
}

void trafficIntersection::controlIntersection(){
	char* theIP = new(char[12]);
	setIp(theIP);
	
	int port;

	if (usedSSH){
		if (this->useDefault){
			port = 10021;
		}else{
			port = 10022;
		}
	}else{

		if (this->useDefault){
			port = 10023;
		}else{
			port = 10024;
		}		
	}


	client intersectionClient(port,theIP);

	intersectionClient.connectClient();

	std::thread Listener1(recievCommands,intersectionClient);

	this->listenButton(this->buttonOne);
	this->listenButton(this->buttonTwo);

	this->listenButton(this->carSensorOne);
	this->listenButton(this->carSensorTwo);

	this->getVelocity(this->velocityOneA,this->velocityOneB);
	this->getVelocity(this->velocityTwoA,this->velocityTwoB);

	this->secondaryRoadRedLightInfraction(this->carSensorOne,this->carSensorTwo);

	// this->getVelocity(this->velocityTwoA,this->velocityTwoB);
	
	this->theSemaphore.changeStates(this->useDefault,5);//off 		off
	
	std::this_thread::sleep_for(5s);
	for (int i = 0; i < 100; ++i){
		switch(message[0]) {
			case 2399:
				std::cout << "Setting emergencyMode: " << std::endl;
				this->emergencyMode();
			break;

			case 4788:
				std::cout << "Setting nightMode: " << std::endl;
				this->nightMode();
			break;

			case 7777:
				std::cout << "Closing intersection: " << std::endl;
				send(intersectionClient.clientSocket,message,5,0);
				return;
			break;
		}	
		
		this->reportToServer(intersectionClient);

		this->theSemaphore.changeStates(this->useDefault,0);//green 		red
		roadStatus = SECONDARY_ROAD_RED;
		this->manageTime();
		
		this->theSemaphore.changeStates(this->useDefault,1);//yellow 	red
		std::this_thread::sleep_for(3s);
		
		this->theSemaphore.changeStates(this->useDefault,2);//red 		red
		roadStatus = BOTH_ROAD_RED;
		std::this_thread::sleep_for(1s);
		
		this->theSemaphore.changeStates(this->useDefault,3);//red 		green
		roadStatus = MAIN_ROAD_RED;
		std::this_thread::sleep_for(5s);

		this->theSemaphore.changeStates(this->useDefault,4);//red 		yellow
		std::this_thread::sleep_for(3s);

		this->theSemaphore.changeStates(this->useDefault,2);//red 		red
		roadStatus = BOTH_ROAD_RED;

	}
	close(intersectionClient.clientSocket);

}