/**
 * @file MorsePifaceModuleExt.cpp
 * @brief MorsePifaceModule extension
 *
 * This file is created at "DO bots". It is open-source software and part of "dodedodo". 
 * This software is published under the Apache Licence license (LGPLv3).
 *
 * Copyright © 2013 Marc Hulscher <marc@almende.org>
 *
 * @author                   Marc Hulscher
 * @date                     dec 10, 2013
 * @organisation             DO bots
 * @project                  dodedodo
 */

#include <MorsePifaceModuleExt.h>
#include <pifacedigital.h>

#include <iostream>				//std::cout
#include <stdlib.h>				//atoi
#include <string>
#include <unistd.h>				//usleep, sleep

using namespace rur;

//! Replace with your own code
MorsePifaceModuleExt::MorsePifaceModuleExt() {
mMorseMessage.clear();
mMorseMessage="0";
mPause = 1000*1000;

hw_addr=0;
pifacedigital_open(hw_addr);
}

//! Replace with your own code
MorsePifaceModuleExt::~MorsePifaceModuleExt() {
pifacedigital_close(hw_addr);
}

//! Replace with your own code
void MorsePifaceModuleExt::Tick() {
	const std::string* read = readMorse(false);
	std::string buf;
	if (read != NULL && !read->empty()) {
		mMorseMessage = *read;
		std::cout << "[MorsePifaceModule] New string received: " << mMorseMessage << std::endl;
	}
//	mMorseMessage = "101010111011101110101010";
	//parse string && blink those lights yo!!
	for(unsigned i=0;i<mMorseMessage.size();++i){
		buf = mMorseMessage.at(i);
		switchlight(buf=="1");
		usleep(mPause);
	}
	usleep(8*mPause);
}

//! Replace with your own code
bool MorsePifaceModuleExt::Stop() {
	return false;
//	return true;
}

void MorsePifaceModuleExt::switchlight(bool on){
	if(on){
		pifacedigital_write_bit(1,1,OUTPUT,hw_addr);
		pifacedigital_write_bit(1,0,OUTPUT,hw_addr);
	} else {
		pifacedigital_write_bit(0,1,OUTPUT,hw_addr);
		pifacedigital_write_bit(0,0,OUTPUT,hw_addr);
	}
}

void MorsePifaceModuleExt::switchlight(int on){
	if(on==0 || on==1){
		pifacedigital_write_bit(on,1,OUTPUT,hw_addr);
		pifacedigital_write_bit(on,0,OUTPUT,hw_addr);
	}
}
