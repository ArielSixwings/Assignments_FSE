#include "../includes/airFryer.h"
#include "../includes/lcdMenu.h"
#include <iostream>
#include <thread>



int main(int argc, char const *argv[]){
	
	airFryer test;
	// test.controlTemperature();
	lcdMenu testlcd;
	// testlcd.WriteOnLcd(false,"+ InTemp  time +");
	// testlcd.WriteOnLcd(true, "- InTemp  time -");
	testlcd.WriteInt(false,"int",1234);
	// testlcd.WriteInt(true,7777);
	return 0;
}