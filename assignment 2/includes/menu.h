#ifndef MENU_H
#define MENU_H

#include "lcd.h"


class menu : public lcd{
private:

public:
	menu();
	void presentPreHeating(float intTemp, float refTemp);
	void presentBaking(float currentTime, float userTime);

};

#endif //MENU_H