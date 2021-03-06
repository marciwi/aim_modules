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
 * Copyright © 2012 Anne van Rossum <anne@almende.com>
 *
 * @author  ...
 * @date    ...
 * @company Almende B.V.
 * @case    Artificial Intelligence Framework
 */
#include <iostream>
#include <fstream>

#include <PictureDisplayModule.h>
#include "CImg.h"

namespace rur {

class PictureDisplayModuleExt: public PictureDisplayModule{
	// unsigned char might be replaced by the correct type for the transferred image
	cimg_library::CImg<unsigned char> image;
	cimg_library::CImgDisplay display;
public:
	PictureDisplayModuleExt();
	// simple function to fully construct the image
	void assignImage();

	// simple function to show the image
	void showImage();

	// read the port and save any image to "tmp.jpg"
	void readPort();

	// The tick function will be called from the PictureDisplayModuleMain file
	void Tick();

	// As soon as Stop() returns "true", the PictureDisplayModuleMain will stop the module
	bool Stop();
};

}

