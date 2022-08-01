#ifndef CLIENT_H
#define CLIENT_H


#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <chrono>
#include <thread>


class client{

public:
	unsigned short port;
	int serverSocket;
	
	struct sockaddr_in serverAddr;
	struct sockaddr_in clientAddr;
	client(int thePort);
};

#endif //CLIENT_H
