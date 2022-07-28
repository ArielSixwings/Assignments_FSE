#ifndef EMBEDDEDOUTPUTS_H
#define EMBEDDEDOUTPUTS_H

#include <iostream>
#include <wiringPi.h>
#include <bits/stdc++.h>

class embeddedOutputs : pinMap{
	
public:
	int* group;
	int groupSize;
	
	embeddedOutputs();
	bool setOutput(int* pins);
	bool setGroup(int* pins);
	bool onOff(int* states);
	void printOutputs();

};

#endif //EMBEDDEDOUTPUTS_H