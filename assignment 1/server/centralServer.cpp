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

void eventHandler::sendCloseMensage(){
	message = 7777;
	send(this->theClientSocket, &message, sizeof(message), MSG_CONFIRM);
}

void eventHandler::setEmergencyMode(){
	message = 2399;
	send(this->theClientSocket, &message, sizeof(message), MSG_CONFIRM);
}

void eventHandler::setNightMode(){
	message = 4788;
	std::cout<< "at function setNightMode: " << message << std::endl;
	send(this->theClientSocket, &message, sizeof(message), MSG_CONFIRM);
}


void eventHandler::handleClient(int socketClient) {
	int* buffer = new(int[16]);
	int recievedLength;
	int embebedSignal = 0;

	while((recievedLength = recv(socketClient, buffer, 16, 0)) > 0){
		switch(buffer[0]) {
			case 1:
				INTERSECTION_1_mainRoadRedInfraction += buffer[1];
				INTERSECTION_1_secondaryRoadRedInfraction += buffer[2];
				INTERSECTION_1_velocityInfraction += buffer[3];
				
				break;

			case 2:
				INTERSECTION_2_mainRoadRedInfraction += buffer[1];
				INTERSECTION_2_secondaryRoadRedInfraction += buffer[2];
				INTERSECTION_2_velocityInfraction += buffer[3];
				
				break;

			case 10:
				INTERSECTION_3_mainRoadRedInfraction += buffer[1];
				INTERSECTION_3_secondaryRoadRedInfraction += buffer[2];
				INTERSECTION_3_velocityInfraction += buffer[3];
				
				break;
			case 20:
				INTERSECTION_4_mainRoadRedInfraction += buffer[1];
				INTERSECTION_4_secondaryRoadRedInfraction += buffer[2];
				INTERSECTION_4_velocityInfraction += buffer[3];

				break;
					
		default:
			std::cout << "UnKnow client" << std::endl;
		}
		if (this->port == 10021 ){
			std::cout << "Send message to client 1" << std::endl;
			send(socketClient,&message,5,0);
			
		}
		if (this->port == 10022 ){
			std::cout << "Send message to client 2" << std::endl;
			send(socketClient,&message,5,0);
		
		}
		if (this->port == 10023 ){
			std::cout << "Send message to client 3" << std::endl;
			send(socketClient,&message,5,0);
			
		}
		if (this->port == 10024){
			std::cout << "Send message to client 4" << std::endl;
			send(socketClient,&message,5,0);
			
		}
	}
}

void eventHandler::closeServer(){
	close(this->serverSocket);
}

bool eventHandler::stablishConnetion(){

	unsigned int clientLength;
	int socketClient;
	
	std::cout << "Listening" << std::endl;
	clientLength = sizeof(this->clientAddr);
	if((socketClient = accept(this->serverSocket, (struct sockaddr *) &(this->clientAddr), &clientLength)) < 0){
		std::cout << "Failed at accept" << std::endl;
		return false;
	}

	this->theClientSocket = socketClient;
		
	std::cout << "Connect to client %s"<< inet_ntoa(this->clientAddr.sin_addr) << std::endl;
	
	for (int i = 0; i < 100; ++i){
		this->handleClient(socketClient);
	}

	close(socketClient);
	close(this->serverSocket);
	return true;
}

void work(eventHandler theHandler){
	theHandler.stablishConnetion();
}

void closeAll(  eventHandler Handler_One,
					eventHandler Handler_Two,
					eventHandler Handler_Three,
					eventHandler Handler_Four){
	Handler_One.sendCloseMensage();
	Handler_Two.sendCloseMensage();
	Handler_Three.sendCloseMensage();
	Handler_Four.sendCloseMensage();
}

void presentData(){
	std::cout << "====================================================================================" << std::endl;
	std::cout << "=                 Main Road red Light  === Secondary Road red Light  === Velocity  ="<<std::endl;
	std::cout << "= intersection 1" << "               "<< INTERSECTION_1_mainRoadRedInfraction << "               " << INTERSECTION_1_secondaryRoadRedInfraction << "               " << INTERSECTION_1_velocityInfraction << "                   =" << std::endl;
	std::cout << "= intersection 2" << "               "<< INTERSECTION_2_mainRoadRedInfraction << "               " << INTERSECTION_2_secondaryRoadRedInfraction << "               " << INTERSECTION_2_velocityInfraction << "                   =" << std::endl;
	std::cout << "= intersection 3" << "               "<< INTERSECTION_3_mainRoadRedInfraction << "               " << INTERSECTION_3_secondaryRoadRedInfraction << "               " << INTERSECTION_3_velocityInfraction << "                   =" << std::endl;
	std::cout << "= intersection 4" << "               "<< INTERSECTION_4_mainRoadRedInfraction << "               " << INTERSECTION_4_secondaryRoadRedInfraction << "               " << INTERSECTION_4_velocityInfraction << "                   =" << std::endl;
	std::cout << "====================================================================================" << std::endl;
}

int main(){

	eventHandler intersection1(10021);
	eventHandler intersection2(10022);
	eventHandler intersection3(10023);
	eventHandler intersection4(10024);

	intersection1.openServer();
	std::this_thread::sleep_for(1s);
	intersection2.openServer();
	std::this_thread::sleep_for(1s);
	intersection3.openServer();
	std::this_thread::sleep_for(1s);
	intersection4.openServer();

	std::thread Listener1(work,intersection1);
	std::thread Listener2(work,intersection2);
	std::thread Listener3(work,intersection3);
	std::thread Listener4(work,intersection4);
	
	for (;option != 0 or option != 1;){

		std::cout << "Use 0 to close the server" << std::endl;
		std::cout << "Use 1 to close the server and all the intersections" << std::endl;
		std::cout << "Use 2 to set EMERGENCY mode at all intersections" << std::endl; 
		std::cout << "Use 3 to set NIGHT mode at all intersections" << std::endl;
		std::cout << "Use 4 to present data from intersections" << std::endl;
		std::cout << "Use 5 to set NORMAL mode at all intersections" << std::endl;

		std::cin >> option;

		switch(option) {
			case 0:
				std::cout << "Closing server: " << std::endl;

				intersection1.closeServer();
				intersection2.closeServer();
				intersection3.closeServer();
				intersection4.closeServer();
				closeAll(intersection1,intersection2,intersection3,intersection4);
				
				return 0;
			break;

			case 1:
				std::cout << "Closing server and all intersetions: " << std::endl;
				
				intersection1.closeServer();
				intersection2.closeServer();
				intersection3.closeServer();
				intersection4.closeServer();
				closeAll(intersection1,intersection2,intersection3,intersection4);
				
				return 0;
			break;

			case 2:
				std::cout << "Setting all intersetions to emergency mode: " << std::endl;
				
				message = 2399;
				
			break;

			case 3:
				std::cout << "Setting all intersetions to night mode: " << std::endl;
				
				message = 4788;
				
			break;

			case 4:
				presentData();
			break;

		default:
			std::cout << "UnKnow option" << std::endl;
		}
	}
	

}