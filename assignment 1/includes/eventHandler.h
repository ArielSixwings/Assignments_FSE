#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "tcpProtocol.h"
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <chrono>
#include <thread>


class eventHandler : public tcpProtocol {
public:

	int serverSocket;
	
	eventHandler(int thePort);

	bool openServer();
	bool stablishConnetion();
	void handleClient(int socketCliente);
	bool resetTimes();

};

#endif //EVENTHANDLER_H