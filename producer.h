/*CS480, Spring 2022
Assignment #4, Real-time messaging for ridesharing 
FILE: producer.h
Dean Quach, cssc1445 & Gian Kyle Nicolas, cssc1438
Copyright (c) 2022 Dean Quach. Gian Nicolas. All rights reserved.
*/

#include "sharedData.h"

#ifndef PRODUCER_H
#define PRODUCER_H
class producer{ //the producer class

	public://the public variables/methods to have the producerThread access
		explicit producer(producerAttr* attr);

		void producerFunction();
		unsigned int userWait;
		
	private://give access to only the producerThread
		struct sharedData* broker;
		struct timespec sleepTime{};	
		RequestType request;
}; 



#endif