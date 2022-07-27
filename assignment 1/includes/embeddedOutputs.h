#ifndef EMBEDDEDOUTPUTS_H
#define EMBEDDEDOUTPUTS_H

#include <iostream>
#include <wiringPi.h>
#include <bits/stdc++.h>

class embeddedOutputs{
	
public:
	int pinMap[28];
	int group[2][6];
	
	embeddedOutputs();
	bool setOutput(int* pins);
	bool setGroup(int groupIndex,int* pins);
	bool onOff(int groupIndex,int* states);
	void printOutputs();

};

#endif //EMBEDDEDOUTPUTS_H