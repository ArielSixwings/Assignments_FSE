#ifndef TRAFFICINTERSECTION_H
#define TRAFFICINTERSECTION_H

#include "semaphore.h"
#include "pinMap.h"
#include <bits/stdc++.h> 
#include <sys/wait.h>
#include <thread>

static int useTime = 10;
static int minTime = 5;

class trafficIntersection: public pinMap
{

public:
	semaphore theSemaphore;

	int buttonOne;
	int buttonTwo;
	int carSensorOne;
	int carSensorTwo;

	trafficIntersection();

	void manageTime();
	void listenButton(int pin);
	void controlIntersection();

};

#endif //TRAFFICINTERSECTION_H