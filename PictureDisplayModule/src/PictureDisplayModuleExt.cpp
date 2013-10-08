/**
 * @file PictureDisplayModuleExt.cpp
 * @brief PictureDisplayModule extension
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

#include <PictureDisplayModuleExt.h>

using namespace rur;

PictureDisplayModuleExt::PictureDisplayModuleExt(){
	this->assignImage();
	this->showImage();
}

void PictureDisplayModuleExt::assignImage(){
	std::ifstream check("temp.jpg");
	if (check.is_open()){
		check.close();
		image.clear();
		image.assign("temp.jpg");
	}
	else{
		check.close();
	}
}

void PictureDisplayModuleExt::showImage(){
	display.assign(image);
}

void PictureDisplayModuleExt::readPort(){
	std::vector<char> * vect = readImage();
	std::string temp(vect->begin(),vect->end());
	if(!temp.empty()){
		// save image
		std::ofstream out("temp.jpg", std::ios::binary);
		out << temp; //assign image to output file
		out.close();
	}
}

//! Replace with your own functionality
void PictureDisplayModuleExt::Tick() {
	if(!display.is_closed()){
		display.wait();
	}
}

//! Replace with your own functionality
bool PictureDisplayModuleExt::Stop() {
	return false;
//	return display.is_closed();	//will not work properly if display is shown belated
}

