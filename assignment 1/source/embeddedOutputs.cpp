#include "../includes/embeddedOutputs.h"

embeddedOutputs::embeddedOutputs(){
	this->pinMap();
}

bool embeddedOutputs::setOutput(int* pins){
	for (int i = 0; i < sizeof(pins)/sizeof(int); ++i){
		pinMode (this->pinMap[pins[i]], OUTPUT);
	}
	return true;
}

bool embeddedOutputs::setGroup(int* pins){
	if (pins == NULL){
		return false;
	}
	this->groups = pins;
	this->groupSize = sizeof(this->groups)/sizeof(int);
	return true;
}

bool embeddedOutputs::onOff(int* states){
	int thesize = sizeof(states)/sizeof(int);

	if (thesize != this->groupSize){
		return false;
	}
	for (int i = 0; i < thesize; ++i){
		digitalWrite (this->pinMap[this->groups[i]], states[i]);
	}
	return true;
}

void embeddedOutputs::printOutputs(){
	for (int i = 0; i < 28; ++i){
		std::cout << i << ": " << this->pinMap[i] << std::endl;
	}
}