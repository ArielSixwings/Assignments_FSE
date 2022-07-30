#include "../includes/semaphore.h"

semaphore::semaphore(){

	int conf0[6] = {1,0,0,0,0,1}; //green 		red
	int conf1[6] = {0,1,0,0,0,1}; //yellow 		red
	int conf2[6] = {0,0,1,0,0,1}; //red 		red
	int conf3[6] = {0,0,1,1,0,0}; //red 		green
	int conf4[6] = {0,0,1,0,1,0}; //red 		yellow	
	int conf5[6] = {0,0,0,0,0,0}; //off 		off
	int conf6[6] = {0,1,0,0,1,0}; //yellow	yellow

	this->states = new int*[7];	
	
	this->states[0] = new int[6];	
	this->states[1] = new int[6];
	this->states[2] = new int[6];
	this->states[3] = new int[6];
	this->states[4] = new int[6];
	this->states[5] = new int[6];
	this->states[6] = new int[6];

	for (int i = 0; i < 6; ++i){
		this->states[0][i] = conf0[i];

		this->states[1][i] = conf1[i];

		this->states[2][i] = conf2[i];

		this->states[3][i] = conf3[i];

		this->states[4][i] = conf4[i];

		this->states[5][i] = conf5[i];

		this->states[6][i] = conf6[i];
	}
	
	
	for (int i = 0; i < 6; ++i){
		std::cout << this->states[0][i] << " ";
	}

	this->setOutputs();
}

void semaphore::setOutputs(){
	pinMode(this->theMap[1],  OUTPUT);
	pinMode(this->theMap[26], OUTPUT);
	pinMode(this->theMap[21], OUTPUT);

	pinMode(this->theMap[20], OUTPUT);
	pinMode(this->theMap[16], OUTPUT);
	pinMode(this->theMap[12], OUTPUT);
}

void semaphore::changeStates(int state){
	digitalWrite(this->theMap[1],  this->states[state][0]);
	digitalWrite(this->theMap[26], this->states[state][1]);
	digitalWrite(this->theMap[21], this->states[state][2]);

	digitalWrite(this->theMap[20], this->states[state][3]);
	digitalWrite(this->theMap[16], this->states[state][4]);
	digitalWrite(this->theMap[12], this->states[state][5]);
}