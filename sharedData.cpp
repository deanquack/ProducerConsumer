/*CS480, Spring 2022
Assignment #4, Real-time messaging for ridesharing 
FILE: sharedData.cpp
Dean Quach, cssc1445 & Gian Kyle Nicolas, cssc1438
Copyright (c) 2022 Dean Quach. Gian Nicolas. All rights reserved.
*/

#include "sharedData.h"

sharedData::sharedData (unsigned int max) {

	//initializes the max requests passed in by the optional arguments
	maxRequests = max;

	//intitializing semaphores 
	sem_init(&mutex, 0, 1); //initialize mutex
	sem_init(&unconsumed, 0, 0); //initialize unconsumed sem
	sem_init(&spaceInQueue, 0, 12);
	sem_init(&spaceForHumanDrivers, 0, 4);
	sem_init(&totalConsumed, 0, 0);

}

//consumer attribute scope resolution 
consumerAttr::consumerAttr(sharedData* broker, unsigned int waitTime, Consumers consumerType){
	userWait = waitTime;
	this->algo = consumerType;
	this->broker = broker;
}

//producer attribute scope resolution 
producerAttr::producerAttr(sharedData* broker, unsigned int waitTime, RequestType requestType) {
	userWait = waitTime;
	this->request = requestType;
	this->broker = broker;
	

}