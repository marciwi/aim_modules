/**
 * 456789------------------------------------------------------------------------------------------------------------120
 *
 * @brief 
 * @file execute_command.hpp
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
 * @date      Dec 3, 2013
 * @project   
 * @company   Almende B.V.
 * @company   Distributed Organisms B.V.
 * @case      
 */

#ifndef EXECUTE_COMMAND_HPP_
#define EXECUTE_COMMAND_HPP_

#include <string>
#include <fstream>
//#include <iostream>
//#include <sstream>
//#include <stdlib.h>     /* system, NULL, EXIT_FAILURE */
#include <vector>
#include <stdio.h>		/* memcpy() remove() */
#include <unistd.h>		/* fork() */
#include <cstring>
#include <sys/stat.h>	/* stat() */
#include <time.h>

#include "line_split.hpp"

bool execute_command(std::vector<std::string> command){
    char** cmd = new char*[command.size()+1];
    for (unsigned int i=0; i<command.size(); ++i) {
        cmd[i] = new char[command[i].size()+1];
        memcpy(cmd[i], command[i].c_str(), command[i].size()+1);
    }
    cmd[command.size()] = new char[1];
    cmd[command.size()] = (char*) 0;

    int pid = fork();
    if (pid == 0) {
        if (execvp(cmd[0], cmd) == -1)
            return false;
        else
            return true;
    }
    else if (pid > 0) {
//        std::cout << "[" << pid << "] " << cmd[0] << std::endl;
        return true;
    }
    else
        return false;
    return false;
}

bool execute_command(std::string command){
	std::cout << "Executing command: " << command << std::endl;
	std::vector<std::string> newcommand = split_string(command);
	return execute_command(newcommand);
}

bool fileExists( const std::string& name ){
	//http://stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exist-using-standard-c-c11-c
    struct stat buf;
    return (stat( name.c_str(), &buf )==0);
}

bool deleteFile(const std::string& name ){
	return remove(name.c_str());
}

const std::string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d,%X", &tstruct);

    return buf;
}

void createFile(const std::string& name, std::string contents){
	std::fstream file;
	file.open(name.c_str(),std::fstream::out);
	file << currentDateTime() << "," << contents;
	file.close();
}

#endif /* EXECUTE_COMMAND_HPP_ */
