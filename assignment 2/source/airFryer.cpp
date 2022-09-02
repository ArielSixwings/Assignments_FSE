#include "../includes/airFryer.h"

using namespace std::literals::chrono_literals;

airFryer::airFryer(){
	wiringPiSetup();

	softPwmCreate (GPIO23, 0, 100) ;
	softPwmCreate (GPIO24, 0, 100) ;

	this->openUart(); 
	this->defaultOptions();
}

airFryer::~airFryer(){
	softPwmWrite(GPIO23,0);
	softPwmWrite(GPIO24,0);
}

void airFryer::activateResistence(int percentage){
	softPwmWrite(GPIO24,0);
	softPwmWrite(GPIO23,percentage);
}

void airFryer::activateFan(int percentage){
	if (percentage < 40) percentage = 40;
	softPwmWrite(GPIO23,0);
	softPwmWrite(GPIO24,percentage);
}

void airFryer::PreHeating(){
	
	float percentage;
	float internalTemperature = 0.0;
	float referenceTemperature = 0.0;

	int startTimer = 5;
	bool stay = true;

	for (; stay ;){
		
		referenceTemperature =  this->getReferenceTemperature();
		internalTemperature = this->getInternalTemperature();

		this->presentPreHeating(internalTemperature, referenceTemperature);

		if (abs(referenceTemperature - internalTemperature) <= 1 and stay == true){
			startTimer--;
			std::cout <<"Stable temperature: " << startTimer << std::endl;
			if (startTimer == 0){
				stay = false;
			}
		}

		if (abs(referenceTemperature - internalTemperature) > 1 and stay == false){
			startTimer++;
			std::cout <<"Unstable reading, adding to verification varible: " << startTimer << std::endl;
		}

		this->setReferenceTemperature(referenceTemperature);
		percentage = this->computePID(internalTemperature);

		
		std::cout <<"percentage: " << percentage << std::endl;
		
		if (percentage > 0) this->activateResistence(percentage);
		if (percentage < 0) this->activateFan(-1*percentage);
	}
}