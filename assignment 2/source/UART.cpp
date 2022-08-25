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

bool uart::sendMessage(int theuart,unsigned char *message){
	int count;

	if (theuart == 0) count = write(this->uart0_filestream,message,9);
	if (theuart == 1) count = write(this->uart1_filestream,message,9);

	if (count < 0){
		std::cout << "Failed to send data" << std::endl;
		return false;
	}

	// this->buffer = message;
	return true;
}

bool uart::readMessage(int theuart){
	int count;
	
	if (theuart == 0) count = read(this->uart0_filestream,(void*)this->buffer.c_str(),100);
	if (theuart == 1) count = read(this->uart1_filestream,(void*)this->buffer.c_str(),100); 

	if (count < 0){
		std::cout << "Failed to read data" << std::endl;
		std::cout << "buffer: " << this->buffer << std::endl;
		return false;
	}

	if (count == 0){
		std::cout << "No data available" << std::endl;
		return true;
	}

	std::cout<<"RECEIVED MESSAGE: " << this->buffer << std::endl;
	return true;
}

void uart::getTemperature(int theuart){
	unsigned char msg[9] = {ADDRESS, GET, INTERNAL_TEMP, 
		REGISTRATION0, 
		REGISTRATION1, 
		REGISTRATION2, 
		REGISTRATION3};


	uint16_t crc = computeCrc(msg,7);
	memcpy(&msg[7],&crc,sizeof(crc));

	for (int i = 0; i < 9; ++i){
		printf("%2X ",msg[i]);		
	}

	std::cout << std::endl;

	this->buffer = msg;
	write(this->uart0_filestream,this->buffer,9);

	// this->sendMessage(theuart,msg);
	this->readMessage(theuart);
}