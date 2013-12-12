/**
 * @file Morse2TxtModuleExt.h
 * @brief Morse2TxtModule extension
 *
 * This file is created at "DO bots". It is open-source software and part of "dodedodo". 
 * This software is published under the Apache Licence license (LGPLv3).
 *
 * Copyright © 2013 Marc Hulscher <marc@almende.org>
 *
 * @author                   Marc Hulscher
 * @date                     dec 11, 2013
 * @organisation             DO bots
 * @project                  dodedodo
 */

#include <Morse2TxtModule.h>

#include <algorithm>
#include <string>
#include <vector>

namespace rur {

/**
 * Your Description of this module.
 */
class Morse2TxtModuleExt: public Morse2TxtModule {
private:
	std::string mMessage;
	std::vector<std::string> morse;
	std::vector<char> chars;
public:
	//! The constructor
	Morse2TxtModuleExt();

	//! The destructor
	virtual ~Morse2TxtModuleExt();

	//! The tick function is the "heart" of your module, it reads and writes to the ports
	void Tick();

	//! As soon as Stop() returns "true", the Morse2TxtModuleMain will stop the module
	bool Stop();

	std::string convertSingleCharacter(std::string thestring);
	unsigned findPos(std::string thestring);

//	std::vector<std::string> split_to_words(std::string);		// between words, there are 7 zeroes
//	std::vector<std::string> split_to_letters(std::string);		// between letters there are 3 zeroes

	std::vector<std::string> split(const std::string& s, const std::string& delim, const bool keep_empty = true) {
	    std::vector<std::string> result;
	    if (delim.empty()) {
	        result.push_back(s);
	        return result;
	    }
	    std::string::const_iterator substart = s.begin(), subend;
	    while (true) {
	        subend = search(substart, s.end(), delim.begin(), delim.end());
	        std::string temp(substart, subend);
	        if (keep_empty || !temp.empty()) {
	            result.push_back(temp);
	        }
	        if (subend == s.end()) {
	            break;
	        }
	        substart = subend + delim.size();
	    }
	    return result;
	}
};

}

