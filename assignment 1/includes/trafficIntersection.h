#ifndef TRAFFICINTERSECTION_H
#define TRAFFICINTERSECTION_H

#include "semaphore.h"
#include "pinMap.h"
#include <bits/stdc++.h> 
#include <sys/wait.h>
#include <thread>

static float velocity;
static int useTime = 10;
static int minTime = 5;
static std::chrono::time_point<std::chrono::high_resolution_clock> timeStart;
static std::chrono::time_point<std::chrono::high_resolution_clock> timeEnd;

class trafficIntersection: public pinMap
{

public:
	semaphore theSemaphore;

	int velocityOneA;
	int velocityOneB;

	int velocityTwoA;
	int velocityTwoB;	

	int buttonOne;
	int buttonTwo;

	int carSensorOne;
	int carSensorTwo;

	trafficIntersection();

	void manageTime();
	void getVelocity(int sensorA, int sensorB);
	void listenButton(int pin);
	void controlIntersection();

};

#endif //TRAFFICINTERSECTION_H