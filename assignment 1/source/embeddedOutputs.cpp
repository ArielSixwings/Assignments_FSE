#include "../includes/embeddedOutputs.h"

embeddedOutputs::embeddedOutputs(){
}

bool embeddedOutputs::setOutput(int* pins){
	for (int i = 0; i < sizeof(pins)/sizeof(int); ++i){
		pinMode(this->theMap[pins[i]], OUTPUT);
	}
	return true;
}

bool embeddedOutputs::setGroup(int* pins){
	if (pins == NULL){
		return false;
	}
	this->group = pins;
	this->groupSize = sizeof(this->group)/sizeof(int);
	return true;
}

bool embeddedOutputs::onOff(int* states){
	int thesize = sizeof(states)/sizeof(int);

	if (thesize != this->groupSize){
		return false;
	}
	for (int i = 0; i < thesize; ++i){
		digitalWrite (this->theMap[this->group[i]], states[i]);
	}
	return true;
}

void embeddedOutputs::printOutputs(){
	for (int i = 0; i < 28; ++i){
		std::cout << i << ": " << this->theMap[i] << std::endl;
	}
}