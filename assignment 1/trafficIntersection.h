#ifndef TRAFFICINTERSECTION_H
#define TRAFFICINTERSECTION_H

#include "semaphore.h"
#include <bits/stdc++.h>
#include <sys/wait.h>

class trafficIntersection{

public:
	std::vector<semaphore> states;
	int minGreenTime;
	int maxGreenTime;
	int minRedTime;
	int maxRedTime;
	int yellowTime;

	trafficIntersection(std::vector<semaphore> thestates,
		int theminGreenTime,
		int themaxGreenTime,
		int theminRedTime,
		int themaxRedTime,
		int theyellowTime);

	void Print();

	void PrintInTime();

};

#endif //TRAFFICINTERSECTION_H