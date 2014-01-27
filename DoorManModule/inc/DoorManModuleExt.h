/**
 * @file DoorManModuleExt.h
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

#include <DoorManModule.h>

namespace rur {

/**
 * Your Description of this module.
 */
class DoorManModuleExt: public DoorManModule {
public:
	//! The constructor
	DoorManModuleExt();

	//! The destructor
	virtual ~DoorManModuleExt();

	//! The tick function is the "heart" of your module, it reads and writes to the ports
	void Tick();

	//! As soon as Stop() returns "true", the DoorManModuleMain will stop the module
	bool Stop();
};

}

