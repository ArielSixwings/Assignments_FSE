#ifndef MENU_H
#define MENU_H

#include "lcd.h"
#include <iostream> 


class menu : public lcd{
private:

public:
	menu();
	void presentPreHeating(float intTemp, float refTemp);
	void presentBaking(float currentTime, float userTime, float refTemp);

};

#endif //MENU_H