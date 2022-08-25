#include "../includes/pid.h"
#include "../includes/UART.h"
#include <iostream>
#include <thread>

using namespace std::literals::chrono_literals;

int main(int argc, char const *argv[]){

	// pid test(80);
	
	// float output;
	
	// for (int i = 0; i < 80; ++i){
	// 	output = test.controlTemperature(i);
	// 	std::cout <<"output: " << output;
	// 	std::cout <<"  temp : " << i << std::endl;
	// 	std::this_thread::sleep_for(0.5s);
	// }
		

	uart test;
	test.openUart(0);
	test.defaultOptions(0);

	std::string message = "salve salve familia";
	
	test.sendMessage(0,message);
	test.readMessage(0);

	test.getTemperature(0);

	return 0;
}