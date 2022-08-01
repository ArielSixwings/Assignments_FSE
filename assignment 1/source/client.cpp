
#include "../includes/client.h"
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

client::client(int thePort,char *ipServer){
	this->port = thePort;
	this->serverIp = ipServer;
}


void client::connectClient(){
	struct sockaddr_in serverAddr;

	//Create socket
	if((this->clientSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0){
		std::cout << "Socket error" <<std::endl;
	}

	//Build struct sockaddr_in
	memset(&serverAddr, 0, sizeof(serverAddr)); // Zerando a estrutura de dados
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = inet_addr(this->serverIp);
	serverAddr.sin_port = htons(this->port);

	// Connect
	if(connect(this->clientSocket, (struct sockaddr *) &serverAddr, 
							sizeof(serverAddr)) < 0){
		std::cout <<"Error to connect"<< std::endl;
	}
}


int main(void) {

	char* theIP = "127.0.0.1";
	client test(8000,theIP);

	for (int i = 0; i < 10; ++i){
		std::cout << "sla mano" <<std::endl;
		test.connectClient();
		send(test.clientSocket,"salve",5,0);
		sleep(2);
	}
	close(test.clientSocket);
}