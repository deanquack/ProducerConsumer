/*CS480, Spring 2022
Assignment #4, Real-time messaging for ridesharing 
FILE: main.cpp
Dean Quach, cssc1445 & Gian Kyle Nicolas, cssc1438
Copyright (c) 2022 Dean Quach. Gian Nicolas. All rights reserved.
*/

#include <iostream>
#include <fstream>
#include <stdio.h>
#include "ridesharing.h"
#include <getopt.h>
#include "producer.h"
#include "consumer.h"
#include "io.h"

using namespace std;

//this is the producer thread that can be used for external linkage (threads)
extern "C" void * producerThread(void* attr) {
	producer* producerInstance = new producer((producerAttr *) attr); 
	producerInstance->producerFunction(); 
	pthread_exit(attr);
	return nullptr;

}
//this is the consumer thread that can be used for external linkage (threads)
extern "C" void * consumerThread(void* attr) {
	consumer* consumerInstance = new consumer((consumerAttr *) attr); 
	consumerInstance->consumerFunction(); 
	pthread_exit(attr);
	return nullptr;
}


int main(int argc, char** argv){
	bool BADFLAG = false; //when there is a badflag
    int option;
    
	unsigned int humanSleepTime = 0;
	unsigned int robotSleepTime = 0;
	unsigned int fastSleepTime = 0;
	unsigned int costSleepTime = 0;
	unsigned int totalRequests = 120;
	
	
	//optional arguments
    while ( (option = getopt(argc, argv, "n:c:f:h:a:")) != -1) { 
        switch(option){
            case 'n': //total number of request from the production side
				if(optarg) {
					totalRequests = atoi(optarg);
				}
            	//thread execution, default is 120 if not specified.
        		break;
            case 'c': //cost-saving dispatcher in milliseconds, should be invoked each time it removes request from queue, use sleep
				if(optarg) {
					costSleepTime = atoi(optarg);
				}
            	break;
            case 'f': //fast-matching dispatcher, similar to cost-saving dispatcher
				if(optarg) {
					fastSleepTime = atoi(optarg);
				}	
				break;
			case 'h': //number of milliseconds to request for a human driver
				if (optarg) {
					humanSleepTime = atoi(optarg);
				}
				break;
			case 'a': //number of milliseconds to request a autonomous driver
				if (optarg) {
					robotSleepTime = atoi(optarg);
				}
                break;
            default: //assuming it's a bad case
				break;
        }
	}   
	
	
	//instantiate the common data structure/broker and creating the producer/consumer attribute for each thread
	sharedData* broker = new sharedData(totalRequests); 
	producerAttr* human = new producerAttr(broker, humanSleepTime, HumanDriver);  
	producerAttr* robot = new producerAttr(broker, robotSleepTime, RoboDriver);
	consumerAttr* fast = new consumerAttr(broker, fastSleepTime, FastAlgoDispatch);
	consumerAttr* cost = new consumerAttr(broker, costSleepTime, CostAlgoDispatch);

	//declare pthreads
	pthread_t humanThread, robotThread, fastThread, costThread;

	//create pthreads
	pthread_create(&humanThread, nullptr, &producerThread, human);
	pthread_create(&robotThread, nullptr, &producerThread, robot);
	pthread_create(&fastThread, nullptr, &consumerThread, fast);
	pthread_create(&costThread, nullptr, &consumerThread, cost);

	//wait until all request types are consumed 
	sem_wait(&broker->totalConsumed); 

	int* yuh[2] = {broker->consumed[0], broker->consumed[1]}; //the array that holds the different consumer types to pass in to the report
	
	io_production_report(broker->produced, yuh); //call production report from passed in shared data produced array and consumed array

}

