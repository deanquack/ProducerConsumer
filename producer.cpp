/*CS480, Spring 2022
Assignment #4, Real-time messaging for ridesharing 
FILE: producer.cpp
Dean Quach, cssc1445 & Gian Kyle Nicolas, cssc1438
Copyright (c) 2022 Dean Quach. Gian Nicolas. All rights reserved.
*/

#include "sharedData.h"
#include "producer.h"
#include "io.h"
#include <unistd.h>


//the method constructor for the consumer attributes, including the sleepTime and the consumer/sharedData types
producer::producer(producerAttr* attr) {
	
	userWait = attr->userWait;	
	broker = attr->broker;
	sleepTime.tv_sec = (long) userWait / 1000;
	sleepTime.tv_nsec = (long) (userWait % 1000) * 1000000;
	this->request = attr->request;

	

}

void producer::producerFunction() {

	RequestType currentRequest;
	//loops until all of the total request are not less than maxRequests
	while(broker->produced[0] + broker->produced[1] < broker->maxRequests) {
		currentRequest = request;
			
		//wait for humanDriver
		if (currentRequest == HumanDriver) {
			sem_wait(&broker->spaceForHumanDrivers);
		}
		sem_wait(&broker->spaceInQueue);

		//sleep
		if(nanosleep(&sleepTime,nullptr) == -1){
			cout << "invalid sleep time" << endl;
			perror("invalid sleep");
			exit(EXIT_FAILURE);
			}

		//critical section
		sem_wait(&broker->mutex);
		
		sem_post(&broker->mutex);
		//if the combined total requests that are produced is greater than maxRequests then signal the space in queue and space for human drivers
		if (broker->produced[0] + broker->produced[1] >= broker->maxRequests) {

			sem_post(&broker->spaceForHumanDrivers);
			sem_post(&broker->spaceInQueue);
			break;

		}
		broker->requestQueue.push(currentRequest); //push the new request type to the queue in the broker
			
		//increment the request and produced array depending on currentRequest
		broker->requested[currentRequest]++;
		broker->produced[currentRequest]++;
		io_add_type(currentRequest, broker->requested, broker->produced); //print out the type of request 

		sem_post(&broker->mutex); //signal the mutex
		sem_post(&broker->unconsumed); //check space in brokerQueue, if full, wait until consumed
	}
		broker->queueFull = true; //sets queueFull to true if the queue is full

}






