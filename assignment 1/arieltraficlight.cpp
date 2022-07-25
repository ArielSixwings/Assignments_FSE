/*
 * blink.c:
 *      blinks the first LED
 *      Gordon Henderson, projects@drogon.net
 */

#include <iostream>
#include <wiringPi.h>
#include <bits/stdc++.h>




int main (void){
	std::cout << "Trafic lights" << std::endl;

	if (wiringPiSetup () == -1){
		std::cout << "No setup" << std::endl; 
		return 1;
	}

	pinMode (0, OUTPUT);         // aka BCM_GPIO pin 17
	pinMode (2, OUTPUT);         // aka BCM_GPIO pin 27
	pinMode (3, OUTPUT);         // aka BCM_GPIO pin 27


	int[6] state1 = [0,0,1,0,0,1];
	int[6] state2 = [1,0,0,0,0,1];
	int[6] state3 = [0,1,0,0,0,1];
	int[6] state4 = [0,0,1,0,0,1];
	int[6] state5 = [0,0,1,1,0,0];
	int[6] state6 = [0,0,1,0,1,0];
	
	std::vector<int[6]> states;

	leds.push_back(state1);
	leds.push_back(state2);
	leds.push_back(state3);
	leds.push_back(state4);
	leds.push_back(state5);
	leds.push_back(state6);
	
	for (int i = 0; i < leds.size(); ++i){
		std::cout << leds[i] << std::endl;
	}
}

// g++ -o arielteste teste.cpp -lwiringPi