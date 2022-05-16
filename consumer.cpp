/*CS480, Spring 2022
Assignment #4, Real-time messaging for ridesharing 
FILE: consumer.cpp
Dean Quach, cssc1445 & Gian Kyle Nicolas, cssc1438
Copyright (c) 2022 Dean Quach. Gian Nicolas. All rights reserved.
*/

#include "consumer.h"
#include <unistd.h>

//the method constructor for the consumer attributes, including the sleepTime and the consumer/sharedData types
consumer::consumer(consumerAttr* attr) {
	userWait = attr->userWait;
	broker = attr->broker;
	this->algo = attr->algo;
	sleepTime.tv_sec = (long) userWait / 1000;
	sleepTime.tv_nsec = (long) (userWait % 1000) * 1000000;
}

void consumer::consumerFunction(){
	RequestType request; //declare requesttype

	//loops when there are requests left to consume, stops when the queue is empty or when it's not full
	while(!broker->queueFull || !broker->requestQueue.empty()){

		//sleep
		if(nanosleep(&sleepTime,nullptr) == -1){
			cout << "invalid sleep time" << endl;
			perror("invalid sleep");
			exit(EXIT_FAILURE);
		}
		//wait for all of the produced requests to be consumed
		sem_wait(&broker->unconsumed);
		sem_wait(&broker->mutex);

		//obtains the very first request type in the broker
		request = broker->requestQueue.front();
		
		//pops the first request type in broker
		broker->requestQueue.pop();
		
		//if the request was a human request type then signal for available human requests in broker
		if(request == HumanDriver){
			sem_post(&broker->spaceForHumanDrivers);
		}

		//decrement the requests in request array and increment the consumption 
		broker->requested[request]--;
		broker->consumed[algo][request]++;
		
		//print what's being consumed by requesttype, consumertype, and how much it consumes, then give access to the consumers to consume
		io_remove_type(algo, request, broker->requested, broker->consumed[algo]); 
		sem_post(&broker->mutex);

		sem_post(&broker->spaceInQueue);
	}
	sem_post(&broker->totalConsumed); //then signal for total consumption
}
