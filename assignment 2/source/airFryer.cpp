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

void airFryer::controlTemperature(){
	
	float userTimer = 125.0;
	float percentage;
	float internalTemperature = 0.0;
	float referenceTemperature = 0.0;

	bool startTimer = true;

	this->timeStart = std::chrono::high_resolution_clock::now();
	this->timeEnd = std::chrono::high_resolution_clock::now();
	
	this->Timer = this->timeEnd - this->timeStart;

	for (; this->Timer < std::chrono::duration<float>(userTimer) or startTimer == false;){
		
		referenceTemperature =  this->getReferenceTemperature();
		internalTemperature = this->getInternalTemperature();

		if (abs(referenceTemperature - internalTemperature) <= 1 and startTimer == true){
			startTimer = false;
			this->timeStart = std::chrono::high_resolution_clock::now();
			std::cout << "Pre aquecimento feito, Iniciando timer de: " << userTimer/60 << "minutos    " << abs(referenceTemperature - internalTemperature) << std::endl;
			std::this_thread::sleep_for(2s);
		}

		this->setReferenceTemperature(referenceTemperature);
		percentage = this->computePID(internalTemperature);

		
		std::cout <<"percentage: " << percentage << std::endl;
		
		if (percentage > 0){
			this->activateResistence(percentage);
		}

		if (percentage < 0){
			this->activateFan(-1*percentage);
		}

		this->timeEnd = std::chrono::high_resolution_clock::now();
		this->Timer = this->timeEnd - this->timeStart;
		
		if (startTimer == false){
			std::cout << "Timer: " << float(this->Timer.count()) << "/" << userTimer << std::endl;
		} 
	}
}