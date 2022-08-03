#include "centralServer.h"

using namespace std::literals::chrono_literals;

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
	int* buffer = new(int[16]);
	int recievedLength;
	int embebedSignal = 0;

	if((recievedLength = recv(socketCliente, buffer, 16, 0)) < 0){
		std::cout << "Error at recv" << std::endl;
	}
	switch(buffer[0]) {
		case 1:
			std::cout << "Run red light infraction on main road at intersection 3: " << buffer[1] << std::endl;
			break;
		case 3:
			std::cout << "Run red light infraction on secondary road at intersection 3: " << buffer[1] << std::endl;
			break;
		case 5:
			std::cout << "Number of Velocity infractions at intersection 3: " << buffer[1] << std::endl;
			break;
		case 2:
			std::cout << "Run red light infraction on main road at intersection 4: " << buffer[1] << std::endl;
			break;
		case 4:
			std::cout << "Run red light infraction on secondary road at intersection 4: " << buffer[1] << std::endl;
			break;
		case 6:
			std::cout << "Number of Velocity infractions at intersection 4: " << buffer[1] << std::endl;
			break;			
	default:
		std::cout << "UnKnow client" << std::endl;
	}
}

bool eventHandler::stablishConnetion(){

	unsigned int clientLength;
	int socketCliente;
	
	std::cout << "Listening" << std::endl;
	clientLength = sizeof(this->clientAddr);
	if((socketCliente = accept(this->serverSocket, (struct sockaddr *) &(this->clientAddr), &clientLength)) < 0){
		std::cout << "Failed at accept" << std::endl;
		return false;
	}
		
	std::cout << "Connect to client %s"<< inet_ntoa(this->clientAddr.sin_addr) << std::endl;
	
	for (int i = 0; i < 100; ++i){
		this->handleClient(socketCliente);
	}

	close(socketCliente);
	close(this->serverSocket);
	return true;
}

void work(eventHandler theHandler){
	theHandler.stablishConnetion();
}

int main(){

	eventHandler intersection3(8000);
	eventHandler intersection4(9000);

	intersection3.openServer();
	std::this_thread::sleep_for(1s);
	intersection4.openServer();

	std::thread Listener3(work,intersection3);
	std::thread Listener4(work,intersection4);
	
	Listener3.join();
	Listener4.join();
}