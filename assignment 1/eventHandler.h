#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <chrono>
#include <thread>

static int useTime;

class eventHandler{
	

public:
	unsigned short port;

	int serverSocket;
	
	struct sockaddr_in serverAddr;
	struct sockaddr_in clientAddr;

	int minTime;
	int maxTime;

	eventHandler(int theminTime, int themaxTime,int thePort);

	bool openServer();
	bool stablishConnetion();
	void handleClient(int socketCliente);
	void handleTime();
	bool resetTimes();

};

#endif //EVENTHANDLER_H