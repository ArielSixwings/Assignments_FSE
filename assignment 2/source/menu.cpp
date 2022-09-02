#include "../includes/menu.h"

//lcd_init
menu::menu(){
	// Initialise display
	this->WriteOnLcd(false,"AirFryer pronta");
}

void menu::presentPreHeating(float intTemp, float refTemp){
	this->WriteOnLcd(false,"Aquecendo:      ");
	this->WriteFloat(true,true,"",intTemp);
	this->WriteFloat(false,true,"//",refTemp);
}

void menu::presentBaking(float currentTime, float userTime){
	this->WriteOnLcd(false,"Assando:        ");
	this->WriteFloat(true,true,"Tempo: ",currentTime);
	this->WriteFloat(false,true,"//",userTime);
}