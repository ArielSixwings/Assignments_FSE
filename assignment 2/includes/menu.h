#include "lcd.h"


class menu : public lcd{
private:

public:
	menu();
	void preHeating(float internalTemperature, float referenceTemperature);

};