#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "../includes/tcpProtocol.h"
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <chrono>
#include <thread>

static int message = 3333;
static int option = 10;


static int INTERSECTION_1_mainRoadRedInfraction = 0;
static int INTERSECTION_1_secondaryRoadRedInfraction = 0;
static int INTERSECTION_1_velocityInfraction = 0;

static int INTERSECTION_2_mainRoadRedInfraction = 0;
static int INTERSECTION_2_secondaryRoadRedInfraction = 0;
static int INTERSECTION_2_velocityInfraction = 0;

static int INTERSECTION_3_mainRoadRedInfraction = 0;
static int INTERSECTION_3_secondaryRoadRedInfraction = 0;
static int INTERSECTION_3_velocityInfraction = 0;

static int INTERSECTION_4_mainRoadRedInfraction = 0;
static int INTERSECTION_4_secondaryRoadRedInfraction = 0;
static int INTERSECTION_4_velocityInfraction;

class eventHandler : public tcpProtocol {
public:

	int theClientSocket;
	int serverSocket;
	
	eventHandler(int thePort);

	bool openServer();
	bool stablishConnetion();
	void handleClient(int socketCliente);
	bool resetTimes();
	void setEmergencyMode();
	void setNightMode();
	void closeServer();
	void sendCloseMensage();

};

#endif //EVENTHANDLER_H