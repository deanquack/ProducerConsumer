/*CS480, Spring 2022
Assignment #4, Real-time messaging for ridesharing 
FILE: consumer.h
Dean Quach, cssc1445 & Gian Kyle Nicolas, cssc1438
Copyright (c) 2022 Dean Quach. Gian Nicolas. All rights reserved.
*/
#include "sharedData.h"

#ifndef CONSUMER_H
#define CONSUMER_H
class consumer{ //consumer class

	public: //give public access to the consumerthread from any file
		explicit consumer(consumerAttr* attr);

		void consumerFunction();
		unsigned int userWait;
		
	private: //only give access to the consumerThread(consumer.cpp) file
		struct sharedData* broker;
		struct timespec sleepTime;	
		ConsumerType algo;
}; 
#endif