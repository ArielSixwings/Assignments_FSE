#include "../includes/pid.h"
#include "../includes/UART.h"
#include <iostream>
#include <thread>

using namespace std::literals::chrono_literals;

int main(int argc, char const *argv[]){
	
	float output;

	float useTimer = 5.0;
	float referenceTemperature = 0.0;
	float internalTemperature = 0.0;

	uart UartConnection;

	UartConnection.openUart(); 
	UartConnection.defaultOptions();

	timeStart = std::chrono::high_resolution_clock::now();
	timeEnd = std::chrono::high_resolution_clock::now();

	std::chrono::duration<float> Timer = timeEnd - timeStart;
	
	pid pidController(0);

	for (; Timer < std::chrono::duration<float>(useTimer);){
		referenceTemperature = UartConnection.getReferenceTemperature();
		internalTemperature = UartConnection.getInternalTemperature();

		pidController.setReferenceTemperature(referenceTemperature);

		output = pidController.controlTemperature(internalTemperature);
		
		std::cout <<"output: " << output;
		std::this_thread::sleep_for(0.5s);
	}

	return 0;
}