#ifndef TCPPROTOCOL_H
#define TCPPROTOCOL_H


#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <chrono>
#include <thread>


class tcpProtocol{

public:
	unsigned short port;
	
	struct sockaddr_in serverAddr;
	struct sockaddr_in clientAddr;
};

#endif //TCPPROTOCOL_H
