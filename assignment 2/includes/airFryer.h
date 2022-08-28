#ifndef AIRFRYER_H
#define AIRFRYER_H

#include <iostream>
#include <wiringPi.h>
#include <softPwm.h>
#include <stdlib.h> 
#include "UART.h"
#include "pid.h"

#define GPIO23 4
#define GPIO24 5

class airFryer : public uart, public pid{

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> timeStart;
	std::chrono::time_point<std::chrono::high_resolution_clock> timeEnd;
	std::chrono::duration<float> Timer;
	
	void activateResistence(int percentage);
	void activateFan(int percentage);

public:
	
	airFryer();
	~airFryer();
	void controlTemperature();
};

#endif //AIRFRYER_H