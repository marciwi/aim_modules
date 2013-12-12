/**
 * @file MorsePifaceModuleExt.h
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

#include <MorsePifaceModule.h>

namespace rur {

/**
 * Your Description of this module.
 */
class MorsePifaceModuleExt: public MorsePifaceModule {
private:
	std::string mMorseMessage;
	unsigned int mPause;		// time between dit's & dah's (usleep)

	uint8_t hw_addr;

public:
	//! The constructor
	MorsePifaceModuleExt();

	//! The destructor
	virtual ~MorsePifaceModuleExt();

	//! The tick function is the "heart" of your module, it reads and writes to the ports
	void Tick();

	//! As soon as Stop() returns "true", the MorsePifaceModuleMain will stop the module
	bool Stop();

	void switchlight(bool on);
};

}

