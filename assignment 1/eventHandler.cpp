#include "eventHandler.h"

eventHandler::eventHandler(int theminTime, int themaxTime,int thePort){
	this->port = thePort;

	this->minTime = theminTime;
	this->maxTime = themaxTime;

}

bool eventHandler::stablishConnection(){
	std::cout <<  this->port << std::endl;
	// Open socket
	if((this->serverSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0){
		std::cout << "Failed to open server socket" << std::endl;
	}

	// build sockaddr_in
	memset(&(this->serverAddr), 0, sizeof(this->serverAddr));
	this->serverAddr.sin_family = AF_INET;
	this->serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	this->serverAddr.sin_port = htons(this->port);

	// Bind
	if(bind(this->serverSocket, (struct sockaddr *) &(this->serverAddr), sizeof(this->serverAddr)) < 0){
		std::cout << "Failed to bind" << std::endl;
		return false;
	}

	// Listen
	if(listen(this->serverSocket, 10) < 0){
		std::cout << "Listen Failed" << std::endl;
		return false;
	}
	return true;
}

void eventHandler::handleClient(int socketCliente) {
	char buffer[16];
	int recievedLength;

	if((recievedLength = recv(socketCliente, buffer, 16, 0)) < 0){
		std::cout << "Error at recv" << std::endl;
	}

	while (recievedLength > 0) {
		if(send(socketCliente, buffer, recievedLength, 0) != recievedLength){
			std::cout << "Error at send" << std::endl;
		}
		
		if((recievedLength = recv(socketCliente, buffer, 16, 0)) < 0){
			std::cout << "Error at recv" << std::endl;
		}
	}

}

int main(){
	unsigned int clientLength;
	int socketCliente;

	eventHandler test(5,10,5000);
	test.stablishConnection();

	while(1) {
		clientLength = sizeof(test.clientAddr);
		if((socketCliente = accept(test.serverSocket, (struct sockaddr *) &(test.clientAddr), &clientLength)) < 0){
			std::cout << "Failed at accept" << std::endl;
			return 0;
		}
		
		std::cout << "Connect to client %s"<< inet_ntoa(test.clientAddr.sin_addr) << std::endl;
		
		test.handleClient(socketCliente);
		close(socketCliente);

	}
	close(test.serverSocket);
}
