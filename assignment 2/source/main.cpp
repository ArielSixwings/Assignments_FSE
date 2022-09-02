#include "../includes/airFryer.h"
#include "../includes/menu.h"
#include <iostream>
#include <thread>



int main(int argc, char const *argv[]){
	
	airFryer test;
	// test.controlTemperature();

	menu testlcd;
	testlcd.preHeating(88.0, 200.0);
	return 0;
}