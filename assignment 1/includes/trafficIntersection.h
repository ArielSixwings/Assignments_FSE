#ifndef TRAFFICINTERSECTION_H
#define TRAFFICINTERSECTION_H

#include "semaphore.h"
#include "pinMap.h"
#include <bits/stdc++.h> 
#include <sys/wait.h>
#include <thread>

static int useTime;
static int minTime;

class trafficIntersection: public pinMap
{

public:
	semaphore theSemaphore;
	
	int minGreenTime;
	int maxGreenTime;
	int minRedTime;
	int maxRedTime;
	int yellowTime;

	int buttonOne;
	int buttonTwo;

	trafficIntersection(int theminGreenTime,
						int themaxGreenTime,
						int theminRedTime,
						int themaxRedTime,
						int theyellowTime);

	void print();
	void manageTime();
	void listenButton(int pin);
	void controlIntersection();

};

#endif //TRAFFICINTERSECTION_H