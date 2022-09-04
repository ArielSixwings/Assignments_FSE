#include "../includes/menu.h"

//lcd_init
menu::menu(){
	// Initialise display
	this->WriteOnLcd(false,"AirFryer pronta");
}

void menu::presentPreHeating(float intTemp, float refTemp){
	
	this->WriteOnLcd(true,"                ");
	this->WriteOnLcd(false,"                ");
	
	if(intTemp < refTemp) this->WriteOnLcd(false,"Aquecendo:      ");
	if(intTemp > refTemp) this->WriteOnLcd(false,"Resfriando:     ");
	
	this->WriteFloat(true,true,"",intTemp);
	this->WriteFloat(false,true,"//",refTemp);
}

// void WriteFloat(bool begin,bool line2,const char *str,float myFloat);
void menu::presentBaking(float currentTime, float userTime, float refTemp){
	
	this->WriteOnLcd(true,"                ");
	this->WriteOnLcd(false,"                ");

	this->WriteFloat(true,false,"Assando:        ",refTemp);
	this->WriteFloat(true,true,"Tempo: ",currentTime/60);
	this->WriteFloat(false,true,"//",userTime/60);
	
	std::cout << "currentTime: " << currentTime << std::endl;
}