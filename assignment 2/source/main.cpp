#include "../includes/airFryer.h"
#include "../includes/menu.h"
#include "../includes/bme280Communicate.h"
#include <iostream>
#include <thread>



int main(int argc, char const *argv[]){
	
	// airFryer test;
	// test.PreHeating();
	bme280Communicate temp;
	std::cout << "Temperatura ambiente: " << temp.getTemperature() << std::endl;
	return 0;
}