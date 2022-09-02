#include "../includes/menu.h"

//lcd_init
menu::menu(){
	// Initialise display
	this->WriteOnLcd(false,"AirFryer pronta");
}

void menu::preHeating(float internalTemperature, float referenceTemperature){
	this->WriteOnLcd(false,"Aquecendo:      ");
	this->WriteFloat(true,true,"",internalTemperature);
	this->WriteFloat(false,true,"//",referenceTemperature);
}

void menu::baking(float currentTime, float userTime){
	this->WriteOnLcd(false,"Assando:        ");
	this->WriteFloat(true,true,"Tempo: ",internalTemperature);
	this->WriteFloat(false,true,"//",referenceTemperature);
}