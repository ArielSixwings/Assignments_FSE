#ifndef EMBEDDEDOUTPUTS_H
#define EMBEDDEDOUTPUTS_H

#include <iostream>
//#include <wiringPi.h>
#include <bits/stdc++.h>

class embeddedOutputs{
	
public:
	int pinMap[28];
	
	embeddedOutputs();
	bool setOutput(int* pins);
	void printOutputs();

};

#endif //EMBEDDEDOUTPUTS_H