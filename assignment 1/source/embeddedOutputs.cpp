#include "../includes/embeddedOutputs.h"

embeddedOutputs::embeddedOutputs(){

	this->pinMap[0] = 30;
	this->pinMap[1] = 31;
	this->pinMap[2] = 8;
	this->pinMap[3] = 9;
	this->pinMap[4] = 7;
	this->pinMap[5] = 21;
	this->pinMap[6] = 22;
	this->pinMap[7] = 11;
	this->pinMap[8] = 10;
	this->pinMap[9] = 13;
	this->pinMap[10] = 12;
	this->pinMap[11] = 14;
	this->pinMap[12] = 26;
	this->pinMap[13] = 23;
	this->pinMap[14] = 15;
	this->pinMap[15] = 16;
	this->pinMap[16] = 27;
	this->pinMap[17] = 0;
	this->pinMap[18] = 1;
	this->pinMap[19] = 24;
	this->pinMap[20] = 28;
	this->pinMap[21] = 29;
	this->pinMap[22] = 3;
	this->pinMap[23] = 4;
	this->pinMap[24] = 5;
	this->pinMap[25] = 6;
	this->pinMap[26] = 25;
	this->pinMap[27] = 2;

}

bool embeddedOutputs::setOutput(int* pins){
	for (int i = 0; i < sizeof(pins)/sizeof(int); ++i){
		pinMode (this->pinMap[pins[i]], OUTPUT);
	}
	return true;
}

bool embeddedOutputs::onOff(int groupIndex,int* states){
	for (int i = 0; i < sizeof(states)/sizeof(int); ++i){
		digitalWrite (this->pinMap[this->group[groupIndex][i]], states[i]);
	}
	return true;
}

void embeddedOutputs::printOutputs(){
	for (int i = 0; i < 28; ++i){
		std::cout << i << ": " << this->pinMap[i] << std::endl;
	}
}

bool embeddedOutputs::setGroup(int groupIndex,int* pins){
	for (int i = 0; i < 6; ++i){
		this->group[groupIndex][i] = pins[i];
	}
	return true;
}