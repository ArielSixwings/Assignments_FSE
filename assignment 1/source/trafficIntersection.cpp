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
	for (int i = 0; i < 100 and recievedMessage == 4788; ++i){
		this->theSemaphore.changeStates(this->useDefault,6);//yellow	yellow
		std::this_thread::sleep_for(1s);
		this->theSemaphore.changeStates(this->useDefault,5);//off 		off
	}
	std::cout << "out of night mode" << recievedMessage << std::endl;
}

void trafficIntersection::emergencyMode(){
	this->theSemaphore.changeStates(this->useDefault,0);//green 		red
	while(recievedMessage == 4788){
		std::this_thread::sleep_for(1s);
		std::cout << "Emergency Mode" << std::endl;
	}
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
	message = new(int[4]);
	
	if (this->useDefault){
		if (usedSSH){
			message[0] = 1;
			message[1] = RASPA_mainRoadInfraction;
			message[2] = RASPA_secondaryRoadInfraction;
			message[3] = RASPA_VelocityInfraction;
			
			send(theClient.clientSocket,message,5,0);
			
			std::this_thread::sleep_for(1s);
			
			recv(theClient.clientSocket, &recievedMessage, 16, 0);
			std::cout << "Recieve message from sever 1" << std::endl;
			return;
		}

		message[0] = 10;
		message[1] = RASPB_mainRoadInfraction;
		message[2] = RASPB_secondaryRoadInfraction;
		message[3] = RASPB_VelocityInfraction;
		
		send(theClient.clientSocket,message,5,0);
		
		std::this_thread::sleep_for(1s);

		recv(theClient.clientSocket, &recievedMessage, 16, 0);
		std::cout << "Recieve message from sever 3" << std::endl;
		return;		
	}

	if (usedSSH){
		message[0] = 2;
		message[1] = RASPA_mainRoadInfraction;
		message[2] = RASPA_secondaryRoadInfraction;
		message[3] = RASPA_VelocityInfraction;
		
		send(theClient.clientSocket,message,5,0);
		
		std::this_thread::sleep_for(1s);
		


		recv(theClient.clientSocket, &recievedMessage, 16, 0);
		std::cout << "Recieve message from sever 2" << std::endl;
		return;
	}
	message[0] = 20;
	message[1] = RASPB_mainRoadInfraction;
	message[2] = RASPB_secondaryRoadInfraction;
	message[3] = RASPB_VelocityInfraction;
	
	send(theClient.clientSocket,message,5,0);
	
	std::this_thread::sleep_for(1s);
		


	recv(theClient.clientSocket, &recievedMessage, 16, 0);
	std::cout << "Recieve message from sever 4" << std::endl;
}

void trafficIntersection::controlIntersection(){

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


	std::string theIp = "164.41.98.17";
	client intersectionClient(port,theIp);

	intersectionClient.connectClient();

	this->listenButton(this->buttonOne);
	this->listenButton(this->buttonTwo);

	this->listenButton(this->carSensorOne);
	this->listenButton(this->carSensorTwo);

	this->getVelocity(this->velocityOneA,this->velocityOneB);
	this->getVelocity(this->velocityTwoA,this->velocityTwoB);

	this->secondaryRoadRedLightInfraction(this->carSensorOne,this->carSensorTwo);
	
	this->theSemaphore.changeStates(this->useDefault,5);//off 		off
	
	std::this_thread::sleep_for(5s);
	for (int i = 0; i < 100; ++i){

		std::cout << "recievedMessage: "<< recievedMessage << std::endl;
		if (recievedMessage == 2399){
			std::cout << "Setting emergencyMode: " << std::endl;
			this->emergencyMode();
			
		}

		if(recievedMessage == 4788){
			std::cout << "Setting nightMode: " << std::endl;
			while(recievedMessage == 4788){
				this->theSemaphore.changeStates(this->useDefault,6);//yellow	yellow
				std::this_thread::sleep_for(1s);
				this->theSemaphore.changeStates(this->useDefault,5);//off 		off
			}
		}

		if(recievedMessage == 7777){
			std::cout << "Closing intersection: " << std::endl;
			send(intersectionClient.clientSocket,&recievedMessage,5,0);
			return;
		}

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

		this->reportToServer(intersectionClient);
	}
	close(intersectionClient.clientSocket);

}