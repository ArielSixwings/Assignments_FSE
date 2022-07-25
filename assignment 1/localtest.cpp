/*
 * blink.c:
 *      blinks the first LED
 *      Gordon Henderson, projects@drogon.net
 */

#include <iostream>
#include <bits/stdc++.h>
#include <sys/wait.h>
// #include <wiringPi.h>

class semaphore{
	
public:
	int lights[6];
	
	semaphore(int thelights[6]){
		for (int i = 0; i < 6; ++i){
			lights[i] = thelights[i];
		}
	}
	
	// ~semaphore();

	void Print(){
		for (int i = 0; i < 6; ++i){
			std::cout << lights[i];
		}
		std::cout << std::endl;
	}
	

};

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
		int theyellowTime)
	{
		this->states = thestates;
		
		int conf0[6] = {0,0,0,0,0,0};
		semaphore state0(conf0);

		this->minGreenTime = theminGreenTime;
		this->maxGreenTime = themaxGreenTime;
		this->minRedTime = theminRedTime;
		this->maxRedTime = themaxRedTime;
		this->yellowTime = theyellowTime;
	}

	void Print(){
		std::cout << "states" << std::endl;
		for (int i = 0; i < states.size(); ++i){
			this->states[i].Print();
		}

		std::cout << this->minGreenTime << "  " << this->maxGreenTime << std::endl;
		std::cout << this->yellowTime << std::endl;
		std::cout << this->minRedTime << "  " << this->maxRedTime << std::endl;
	}

	void PrintInTime(){
		this->states[1].Print();
		sleep(this->minGreenTime);
		this->states[2].Print();
		sleep(this->yellowTime);
		this->states[3].Print();
		sleep(1);
		this->states[4].Print();
		sleep(this->minGreenTime);
		this->states[5].Print();
		sleep(this->yellowTime);
		this->states[0].Print();
	}

	void flashingAmber(){

	}
};


int main (void){
	std::cout << "Trafic lights" << std::endl;

	int conf1[6] = {0,0,1,0,0,1};
	int conf2[6] = {1,0,0,0,0,1};
	int conf3[6] = {0,1,0,0,0,1};
	int conf4[6] = {0,0,1,0,0,1};
	int conf5[6] = {0,0,1,1,0,0};
	int conf6[6] = {0,0,1,0,1,0};
	
	semaphore state1(conf1);
	semaphore state2(conf2);
	semaphore state3(conf3);
	semaphore state4(conf4);
	semaphore state5(conf5);
	semaphore state6(conf6);
	
	
	std::vector<semaphore> states;

	states.push_back(state1);
	states.push_back(state2);
	states.push_back(state3);
	states.push_back(state4);
	states.push_back(state5);
	states.push_back(state6);
	
	// for (int i = 0; i < states.size(); ++i){
	// 	states[i].Print();
	// }

	trafficIntersection theIntersection(states,10,20,5,10,3);
	// theIntersection.Print();
	theIntersection.PrintInTime();
}

// g++ -o arielteste teste.cpp -lwiringPi