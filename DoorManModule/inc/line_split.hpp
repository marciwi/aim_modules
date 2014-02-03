/**
 * 456789------------------------------------------------------------------------------------------------------------120
 *
 * @brief 
 * @file line_split.hpp
 *
 * This file is created at Almende B.V. and Distributed Organisms B.V. It is open-source software and belongs to a
 * larger suite of software that is meant for research on self-organization principles and multi-agent systems where
 * learning algorithms are an important aspect.
 *
 * This software is published under the GNU Lesser General Public license (LGPL).
 *
 * It is not possible to add usage restrictions to an open-source license. Nevertheless, we personally strongly object
 * against this software being used for military purposes, factory farming, animal experimentation, and "Universal
 * Declaration of Human Rights" violations.
 *
 * Copyright (c) 2013 Marc J. Hulscher <marc@dobots.nl>
 *
 * @author    marc
 * @date      Sep 9, 2013
 * @project   
 * @company   Almende B.V.
 * @company   Distributed Organisms B.V.
 * @case      
 */

#ifndef LINE_SPLIT_HPP_
#define LINE_SPLIT_HPP_

#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string>
#include <vector>

// used from http://stackoverflow.com/questions/236129/splitting-a-string-in-c
std::vector<std::string> split_string(std::string str)
{
    std::string buf; 							//initiate the buffer string
	std::stringstream stringStream(str);	 	//Insert the string into a stream
	std::vector<std::string> tokens; 			//Use a vector to hold the words
    while (stringStream >> buf){
        tokens.push_back(buf);
    }
    return tokens;								//Return Vector with tokens for each word (split at empty spaces)
}

std::vector<std::string> split_string_by_slash(std::string str){
	char Seperator = '/';
	std::string buf;
	std::istringstream stringStream(str);
	std::vector<std::string> tokens;
	while(getline(stringStream, buf, Seperator)){
		tokens.push_back(buf);
	}
	return tokens;
}

std::string interpretName(std::string name){
	std::string modulename;
	const unsigned int idx = name.find_last_of("\\/");
	if (std::string::npos != idx){
	    modulename = name.substr(idx + 1);
	} else {
		modulename=name;
	}
	return modulename;
}

#endif /* LINE_SPLIT_HPP_ */
