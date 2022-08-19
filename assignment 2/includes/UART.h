#ifndef UART_H
#define UART_H

#include <iostream>
#include <unistd>
#include <fcntl.h>
#include <termios.h>
#include <string.h>
// #include <wiringPi.h>

class uart{

private:
	int uart0_filestream;
	int uart1_filestream;

	std::string buffer;

public:
	uart();
	bool openUart(int theuart);
	bool defaultOptions(int theuart);
	bool sentMensage(std::string message);
};

#endif //UART_H