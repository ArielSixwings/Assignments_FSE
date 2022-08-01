#ifndef CLIENT_H
#define CLIENT_H

#include "tcpProtocol.h"
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <chrono>
#include <thread>


class client : public tcpProtocol{

public:
	char *serverIp;
	int clientSocket;
	
	client(int thePort,char *ipServer);
	void connectClient();
};

#endif //CLIENT_H
