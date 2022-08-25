#ifndef UART_H
#define UART_H

#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>
// #include <wiringPi.h>

#define INTERNAL_TEMPERATURE 1
#define REFERENCE_TEMPERATURE 2

#define ADDRESS 0x01
#define POST 0x16
#define GET 0x23
#define INTERNAL_TEMP 0xC1
#define REFERENCE_TEMP 0xC2
#define USER_COMMANDS 0xC3

static const std::string REGISTRATION = { '6', '3', '2', '8' };

class uart{

private:
	int uart0_filestream;
	int uart1_filestream;

	bool openUart0;
	bool openUart1;

	std::string buffer;
	std::string getCode(int code);

public:
	uart();
	~uart();
	bool openUart(int theuart);
	bool defaultOptions(int theuart);
	bool sendMessage(int theuart,std::string message);
	bool readMessage(int theuart);
	float getTemperature(int theuart);
};

#endif //UART_H