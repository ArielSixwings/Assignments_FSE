#ifndef EMBEDDEDINPUTS_H
#define EMBEDDEDINPUTS_H

#include <iostream>
#include <wiringPi.h>
#include <bits/stdc++.h>

class embeddedInputs : pinMap{
	
public:
	int* group;
	int groupSize;
	
	embeddedInputs();
};

#endif //EMBEDDEDINPUTS_H