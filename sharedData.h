/*CS480, Spring 2022
Assignment #4, Real-time messaging for ridesharing 
FILE: sharedData.h
Dean Quach, cssc1445 & Gian Kyle Nicolas, cssc1438
Copyright (c) 2022 Dean Quach. Gian Nicolas. All rights reserved.
*/

//this is the data structure that the producer/consumer will use

#include "io.h"
#include <stdio.h>
#include <semaphore.h>
#include <queue>
#include <ctime>
#include <iostream>


#ifndef SHAREDDATA_H_
#define SHAREDDATA_H_
using namespace std;


class sharedData { 
	public:
		sharedData(unsigned int maxR);
		int maxRequests;	
		sem_t spaceForHumanDrivers{};
		sem_t spaceInQueue{};
		sem_t unconsumed{};
		sem_t mutex{};
		sem_t totalConsumed{};
				 //
    	queue<RequestType> requestQueue; //the buffer needed when accessing the requests
		int requested[2]{};
    	int consumed[2][2]{};
    	int produced[2]{};
		bool queueFull = false;
		

		//sleep times
		int humanSleepTime;
		int robotSleepTime;
		int fastSleepTime;
		int costSleepTime;
};

//this is the structure that hold the request type pointer to the broker queue and holds the user's request time (human/robot)
struct producerAttr {
	producerAttr (sharedData* broker, unsigned int specWaitTime, RequestType request);
	RequestType request;
	sharedData* broker{};
	unsigned int userWait;
};

//this is the structure that holds the consumer type pointer that will also hold the user's algorithm time (fast/cost)
struct consumerAttr {
	consumerAttr (sharedData* broker, unsigned int specWaitTime, ConsumerType algo);
	ConsumerType algo;
	sharedData* broker{};
	unsigned int userWait;
};


#endif


