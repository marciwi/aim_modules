/**
 * @file Txt2MorseModuleExt.h
 * @brief Txt2MorseModule extension
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

#include <Txt2MorseModule.h>

#include <string>
#include <vector>

namespace rur {

/**
 * Your Description of this module.
 */
class Txt2MorseModuleExt: public Txt2MorseModule {
private:
	std::string mMessage;
	std::vector<std::string> morse;
	std::vector<char> chars;
public:
	//! The constructor
	Txt2MorseModuleExt();

	//! The destructor
	virtual ~Txt2MorseModuleExt();

	//! The tick function is the "heart" of your module, it reads and writes to the ports
	void Tick();

	//! As soon as Stop() returns "true", the Txt2MorseModuleMain will stop the module
	bool Stop();

	std::string convertSingleCharacter(char thechar);
	unsigned findPos(char thechar);
};

}

