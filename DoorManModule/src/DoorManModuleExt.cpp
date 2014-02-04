/**
 * @file DoorManModuleExt.cpp
 * @brief DoorManModule extension
 *
 * This file is created at "DO bots". It is open-source software and part of "dodedodo". 
 * This software is published under the Apache Licence license (LGPLv3).
 *
 * Copyright © 2014 Marc Hulscher <marc@almende.org>
 *
 * @author                   Marc Hulscher
 * @date                     jan 27, 2014
 * @organisation             DO bots
 * @project                  dodedodo
 */

#include <DoorManModuleExt.h>
#include <ctime>
#include "execute_command.hpp"
#include <iostream>
#include <unistd.h>				/* usleep */
#include <string>
#include <time.h>       /* time_t, struct tm, difftime, time, mktime */

using namespace rur;

//! Replace with your own code
DoorManModuleExt::DoorManModuleExt() {
	std::string prefix = "sudo /home/pi/ardushield/rftransmit.o -c ";
	std::string suffix= " -a 9.135.101.67.33.0.0.0";
	opencommand = prefix + "34" + suffix;
	closecommand = prefix + "51" + suffix;
	fileopen = "/home/pi/open.txt";
	fileclose = "/home/pi/close.txt";
	outputfile = "/home/pi/doorData.txt";
	threshold = 25;
	waitPeriod = 5;
	time(&lastAction);
}

DoorManModuleExt::~DoorManModuleExt() {

}

void DoorManModuleExt::openDoor(){
	std::cout << "opening door" << std::endl;
	execute_command(opencommand);
	createFile(outputfile,"1");
}
void DoorManModuleExt::closeDoor(){
	std::cout << "closing door" << std::endl;
	execute_command(closecommand);
	createFile(outputfile,"0");
}

void DoorManModuleExt::Tick() {
	int *read = readopendoor();
	if (read != NULL) {
		int copy = *read;
		if(copy>threshold){
			openDoor();
			time(&lastAction);
		} else if(copy<=threshold && difftime(time(NULL),lastAction)>waitPeriod){
			closeDoor();
			time(&lastAction);
		}
		std::cout << "Received value: " << copy << std::endl;
	}

	// check output from EVE
	if(fileExists(fileopen)){
		openDoor();
		deleteFile(fileopen);
	} else if(fileExists(fileclose)){
		closeDoor();
		deleteFile(fileclose);
	}
	createFile(outputfile,"1");
	usleep(10000);
}

//! Replace with your own code
bool DoorManModuleExt::Stop() {
	return false;
}

