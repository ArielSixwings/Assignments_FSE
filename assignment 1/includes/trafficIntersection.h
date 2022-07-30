#ifndef TRAFFICINTERSECTION_H
#define TRAFFICINTERSECTION_H

#include "semaphore.h"
#include "pinMap.h"
#include <bits/stdc++.h> 
#include <sys/wait.h>
#include <thread>

static int useTime = 5;
static int minTime = 5;

class trafficIntersection: public pinMap
{

public:
	semaphore theSemaphore;

	int buttonOne;
	int buttonTwo;

	trafficIntersection();

	void manageTime();
	void listenButton(int pin);
	void controlIntersection();

};

#endif //TRAFFICINTERSECTION_H