#ifndef EMBEDDEDOUTPUTS_H
#define EMBEDDEDOUTPUTS_H

#include <iostream>
#include <wiringPi.h>
#include <bits/stdc++.h>

class embeddedOutputs{
	
public:
	int pinMap[28];
	std::vector<int*> groups;
	
	embeddedOutputs();
	bool setOutput(int* pins);
	bool setGroup(int* pins);
	bool onOff(int groupIndex,int* states);
	void printOutputs();

};

#endif //EMBEDDEDOUTPUTS_H