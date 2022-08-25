#ifndef UART_H
#define UART_H

#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>
#include "crc16.h"
// #include <wiringPi.h>

#define INTERNAL_TEMPERATURE 1
#define REFERENCE_TEMPERATURE 2

const unsigned char ADDRESS = 0x01;
const unsigned char POST = 0x16;
const unsigned char GET = 0x23;
const unsigned char INTERNAL_TEMP = 0xC1;
const unsigned char REFERENCE_TEMP = 0xC2;
const unsigned char USER_COMMANDS = 0xC3;

const unsigned char REGISTRATION0 = 0x06;
const unsigned char REGISTRATION1 = 0x03;
const unsigned char REGISTRATION2 = 0x02;
const unsigned char REGISTRATION3 = 0x08;

class uart{

private:
	int uart0_filestream;
	int uart1_filestream;

	bool openUart0;
	bool openUart1;

	unsigned char* buffer;

public:
	uart();
	~uart();
	bool openUart(int theuart);
	bool defaultOptions(int theuart);
	bool sendMessage(int theuart,unsigned char *message);
	bool readMessage(int theuart);
	void getTemperature(int theuart);
};

#endif //UART_H