#include "../includes/eventHandler.h"

eventHandler::eventHandler(int thePort){
	this->port = thePort;
}

bool eventHandler::openServer(){
	std::cout <<"Using port: " << this->port << std::endl;
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
	int embebedSignal = 0;

	if((recievedLength = recv(socketCliente, buffer, 16, 0)) < 0){
		std::cout << "Error at recv" << std::endl;
	}
	std::cout << "mensage recieved" << std::endl;
}

bool eventHandler::stablishConnetion(){

	unsigned int clientLength;
	int socketCliente;
	
	for (int i = 0; i < 100; ++i){
		std::cout << "Listening" << std::endl;
		clientLength = sizeof(this->clientAddr);
		if((socketCliente = accept(this->serverSocket, (struct sockaddr *) &(this->clientAddr), &clientLength)) < 0){
			std::cout << "Failed at accept" << std::endl;
			return false;
		}
			
		std::cout << "Connect to client %s"<< inet_ntoa(this->clientAddr.sin_addr) << std::endl;
		

		this->handleClient(socketCliente);
		close(socketCliente);
	}
	
	close(this->serverSocket);
	return true;
}

void work(eventHandler theHandler){
	theHandler.stablishConnetion();
}

int main(){

	eventHandler test(8000);
	test.openServer();

	std::thread Listener(work,test);
	Listener.join();
}