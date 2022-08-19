#include "../includes/UART.h"

uart::uart(){
	this->uart0_filestream = -1;
	this->uart1_filestream = -1;
}

bool uart::openUart(int theuart){
	if (uart = 0){
		this->uart0_filestream = open("/dev/serial0",O_RDWR | O_NOCTTY | O_DELAY);
		if (this->uart0_filestream == -1){
			std::cout << "Failed to open uart serial 0" << std::endl;
			return false;
		}
		return true;
	}

	if (uart == 1){
		this->uart1_filestream = open("/dev/serial1",O_RDWR | O_NOCTTY | O_DELAY);
		if (this->uart1_filestream == -1){
			std::cout << "Failed to open uart serial 1" << std::endl;
			return false;
		}
		return true;
	}
}

bool uart::defaultOptions(int theuart){
	struct termios options;

	if (theuart == 0){
		if (this->uart0_filestream == -1){
			std::cout << "Uart 0 was not properly open, can't set options" << std::endl;
			return false
		}
		tcgeattr(this->uart0_filestream, &options);	
	}

	if (theuart == 1){
		if (this->uart1_filestream == -1){
			std::cout << "Uart 1 was not properly open, can't set options" << std::endl;
			return false
		}
		tcgeattr(this->uart1_filestream, &options);	
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

bool uart::sentMensage(int theuart,std::string message){
	int count;
	p_message = *message;

	if (theuart == 0) count = write(this->uart0_filestream, &message[0],(p_message - &message[0]));
	if (theuart == 1) count = write(this->uart1_filestream, &message[0],(p_message - &message[0]));

	if (count < 0){
		std::cout << "Failed to send data" << std::endl;
		return false;
	}

	return true;

}