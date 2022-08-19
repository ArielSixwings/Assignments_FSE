#include "../includes/pid.h"
#include <iostream>
#include <thread>

using namespace std::literals::chrono_literals;

int main(int argc, char const *argv[]){

	pid test(80);
	
	float output;
	
	for (int i = 0; i < 80; ++i){
		output = test.controlTemperature(i);
		std::cout <<"output: " << output << std::endl;
		std::this_thread::sleep_for(1s);
	}
		
	return 0;
}