#include "../includes/UART.h"

uart::uart(){
	this->uart0_filestream = -1;
	this->uart1_filestream = -1;

	this->openUart0 = false;
	this->openUart1 = false;
}

uart::~uart(){
	if (this->openUart0) close(this->uart0_filestream);
	if (this->openUart1) close(this->uart1_filestream);
}

bool uart::openUart(int theuart){
	if (theuart == 0){
		this->uart0_filestream = open("/dev/serial0",O_RDWR | O_NOCTTY | O_NDELAY);
		if (this->uart0_filestream == -1){
			std::cout << "Failed to open uart serial 0" << std::endl;
			return false;
		}
		this->openUart0 = true;
		return true;
	}

	if (theuart == 1){
		this->uart1_filestream = open("/dev/serial1",O_RDWR | O_NOCTTY | O_NDELAY);
		if (this->uart1_filestream == -1){
			std::cout << "Failed to open uart serial 1" << std::endl;
			return false;
		}
		this->openUart1 = true;
		return true;
	}
	return false;
}

bool uart::defaultOptions(int theuart){
	struct termios options;

	if (theuart == 0){
		if (this->uart0_filestream == -1){
			std::cout << "Uart 0 was not properly open, can't set options" << std::endl;
			return false;
		}
		tcgetattr(this->uart0_filestream, &options);	
	}

	if (theuart == 1){
		if (this->uart1_filestream == -1){
			std::cout << "Uart 1 was not properly open, can't set options" << std::endl;
			return false;
		}
		tcgetattr(this->uart1_filestream, &options);	
	}

	options.c_cflag = B115200 | CS8 | CLOCAL | CREAD;
	options.c_iflag = IGNPAR;
	options.c_oflag = 0;
	options.c_lflag = 0;

	if (theuart == 0){
		tcflush(this->uart0_filestream, TCIFLUSH);
		tcsetattr(this->uart0_filestream, TCSANOW, &options);
		return true;
	}

	tcflush(this->uart1_filestream, TCIFLUSH);
	tcsetattr(this->uart1_filestream, TCSANOW, &options);
	return true;	
}

bool uart::sendMessage(int theuart,std::string message){
	int count;
	// void* p_message = message;

	if (theuart == 0) count = write(this->uart0_filestream, (void*)message.c_str(),message.length());
	if (theuart == 1) count = write(this->uart1_filestream, (void*)message.c_str(),message.length());

	if (count < 0){
		std::cout << "Failed to send data" << std::endl;
		return false;
	}

	this->buffer = message;
	return true;
}

bool uart::readMessage(int theuart){
	int count;
	
	if (theuart == 0) count = read(this->uart0_filestream,(void*)this->buffer.c_str(),100);
	if (theuart == 1) count = read(this->uart1_filestream,(void*)this->buffer.c_str(),100); 

	if (count < 0){
		std::cout << "Failed to read data" << std::endl;
		return false;		
	}

	if (count == 0){
		std::cout << "No data available" << std::endl;
		return true;
	}

	if (getCode(INTERNAL_TEMPERATURE) == this->buffer){
		std::cout<<"Got temperature: " << std::endl;	
	}
	std::cout<<"RECEIVED MESSAGE: " << this->buffer << std::endl;
	return true;
}

std::string uart::getCode(int code){
	std::string message;
	int index;
	switch(code){
		case INTERNAL_TEMPERATURE:
		
			message = ADDRESS;
			message += GET;
			message += INTERNAL_TEMP;
			break;
		
		case REFERENCE_TEMPERATURE:

			message += ADDRESS;
			message += GET;
			message += REFERENCE_TEMP;
			break;
		
		default:
			std::cout << "UnKnow option"<<std::endl;
	}

	message += REGISTRATION[0];
	message += REGISTRATION[1];
	message += REGISTRATION[2];
	message += REGISTRATION[3];

	for (int i = 0; i < message.length(); ++i){
		std::cout << std::hex << message[i];
	}

	std::cout<<std::endl;
	
	return message;
}

float uart::getTemperature(int theuart){
	this->sendMessage(theuart,getCode(INTERNAL_TEMPERATURE));
	this->readMessage(theuart);
}