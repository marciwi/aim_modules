/**
 * @file Txt2MorseModuleMain.cpp
 * @brief Entry function for Txt2MorseModule
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
 
#include <Txt2MorseModuleExt.h>

#include <stdlib.h>
#include <iostream>

using namespace rur;
using namespace std;

/**
 * Every module is a separate binary and hence has its own main method. It is recommended
 * to have a version of your code running without any middleware wrappers, so preferably
 * have this file and the Txt2MorseModule header and code in a separate "aim" directory.
 */
int main(int argc, char *argv[])  {
	Txt2MorseModuleExt *m = new Txt2MorseModuleExt();

	if (argc < 2) {
		std::cout << "Use an identifier as argument for this instance" << endl;
		return EXIT_FAILURE;
	}
	std::string identifier = argv[1];
	m->Init(identifier);

	do {
		m->Tick();
	} while (!m->Stop()); 

	delete m;

	return EXIT_SUCCESS;
}
