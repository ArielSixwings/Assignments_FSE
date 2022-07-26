#include "eventHandler.h"

eventHandler::eventHandler(int theminTime, int themaxTime,int thePort){
	this->port = thePort;

	this->minTime = theminTime;
	this->maxTime = themaxTime;
	useTime = this->maxTime;

}

bool eventHandler::openServer(){
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
	int embebedSignal = 0;

	if((recievedLength = recv(socketCliente, buffer, 16, 0)) < 0){
		std::cout << "Error at recv" << std::endl;
	}

	useTime = this->minTime;

	std::cout << "Button pressed, using minimum time: " << useTime << std::endl;

}

void eventHandler::handleTime() {
	
	using namespace std::literals::chrono_literals;
	char buffer[16];
	int recievedLength;

	auto start = std::chrono::high_resolution_clock::now();
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float> duration = end - start;

	for (int i = 0; duration < std::chrono::duration<float>(useTime); ++i)
	{
		std::this_thread::sleep_for(1s);
		end = std::chrono::high_resolution_clock::now();
		duration = end - start;
		std::cout << duration.count() << "s  " << i << std::endl;
	}
	std::cout << "out of for, returning to proced to new state" << std::endl;

}

bool eventHandler::stablishConnetion(){

	unsigned int clientLength;
	int socketCliente;

	while(1) {
		std::cout << "Listening" << std::endl;
		clientLength = sizeof(this->clientAddr);
		if((socketCliente = accept(this->serverSocket, (struct sockaddr *) &(this->clientAddr), &clientLength)) < 0){
			std::cout << "Failed at accept" << std::endl;
		}
		
		std::cout << "Connect to client %s"<< inet_ntoa(this->clientAddr.sin_addr) << std::endl;
		
		this->handleClient(socketCliente);
		close(socketCliente);

	}
	close(this->serverSocket);
}

void work(eventHandler theHandler){
	theHandler.stablishConnetion();
}

int main(){

	eventHandler test(5,10,8000);
	test.openServer();

	std::thread Listener(work,test);
	test.handleTime();
	Listener.join();
}