/**
 * @file PictureSendModuleExt.cpp
 * @brief PictureSendModule extension
 *
 * This file is created at Almende B.V. It is open-source software and part of the Common 
 * Hybrid Agent Platform (CHAP). A toolbox with a lot of open-source tools, ranging from 
 * thread pools and TCP/IP components to control architectures and learning algorithms. 
 * This software is published under the GNU Lesser General Public license (LGPL).
 *
 * It is not possible to add usage restrictions to an open-source license. Nevertheless,
 * we personally strongly object against this software being used by the military, in the
 * bio-industry, for animal experimentation, or anything that violates the Universal
 * Declaration of Human Rights.
 *
 * Copyright © 2013 Your Name <your@email>
 *
 * @author	Your Name
 * @date	Current date
 * @company	Your Company
 * @project	Specific Software Project
 */

#include <PictureSendModuleExt.h>

using namespace rur;
PictureSendModuleExt::PictureSendModuleExt(){
	//load the image (for now hardcoded)
	std::ifstream file("test.jpg", std::ios::binary);

	// convert to stream
//	std::ostringstream ostrm;
	ostrm << file.rdbuf();

	// output as new jpg (debug)
//	std::ofstream out("out.jpg", std::ios::binary);
//	out << ostrm.str();
}

//! Replace with your own functionality
void PictureSendModuleExt::Tick() {
	// send image over port
	std::vector<char> data(ostrm.str().begin(),ostrm.str().end());
	writeImage(data);
}

//! Replace with your own functionality
bool PictureSendModuleExt::Stop() {
	return false;
//	return true;
}

