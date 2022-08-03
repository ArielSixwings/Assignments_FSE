#ifndef TRAFFICINTERSECTION_H
#define TRAFFICINTERSECTION_H

#include "semaphore.h"
#include "client.h"
#include "pinMap.h"
#include <sys/wait.h>
#include <thread>

#define BOTH_ROAD_RED 15
#define MAIN_ROAD_RED 20
#define SECONDARY_ROAD_RED 10

static bool usedSSH = false;
static int roadStatus = 0;
static float velocity = 0.0;

static int RASPA_VelocityInfraction = 0;
static int RASPA_mainRoadInfraction = 0;
static int RASPA_secondaryRoadInfraction = 0;

static int RASPB_VelocityInfraction = 0;
static int RASPB_mainRoadInfraction = 0;
static int RASPB_secondaryRoadInfraction = 0;

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

	bool useDefault;

	trafficIntersection(bool defaultUse,bool rasp);

	void manageTime();
	void getVelocity(int sensorA, int sensorB);
	void listenButton(int pin);
	void controlIntersection();
	void mainRoadRedLightInfraction(int sensorA, int sensorB);
	void secondaryRoadRedLightInfraction(int sensorA, int sensorB);
	void reportToServer(client theClient);

};

#endif //TRAFFICINTERSECTION_H