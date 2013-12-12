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
#include <unistd.h>				//usleep, sleep

using namespace rur;

//! Replace with your own code
MorsePifaceModuleExt::MorsePifaceModuleExt() {
mMorseMessage.clear();
mPause = 1000;

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
	if (read != NULL && !read->empty()) {
		mMorseMessage = *read;
		std::cout << "Incoming string received: " << mMorseMessage << std::endl;
		//parse string
		//blink those lights yo!!
	}
    // Write to output
    pifacedigital_write_reg(0x00, OUTPUT, hw_addr);
    sleep(1);
    pifacedigital_write_reg(0xaa, OUTPUT, hw_addr);
    sleep(1);
    pifacedigital_write_reg(0x55, OUTPUT, hw_addr);
    sleep(1);
    pifacedigital_write_reg(0x00, OUTPUT, hw_addr);

	usleep(10000);
}

//! Replace with your own code
bool MorsePifaceModuleExt::Stop() {
	return false;
}

bool MorsePifaceModuleExt::switchlight(bool on){
	return true;
}
