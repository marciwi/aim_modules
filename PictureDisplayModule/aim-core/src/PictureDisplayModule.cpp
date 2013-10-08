/**
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
 * @author You
 * @copyright Your Company
 * @date 21 Jun. 2013
 * @license LGPLv3
 */

#include "PictureDisplayModule.h"

namespace rur {
using namespace yarp::os;

PictureDisplayModule::PictureDisplayModule():
  cliParam(0)
{
  const char* const channel[1] = {"readImage"};
  cliParam = new Param();
  portImage = new BufferedPort<Bottle>();
}

PictureDisplayModule::~PictureDisplayModule() {
  delete cliParam;
  delete portImage;
}

void PictureDisplayModule::Init(std::string & name) {
  cliParam->module_id = name;
  
  std::stringstream yarpPortName;
  yarpPortName.str(""); yarpPortName.clear();
  yarpPortName << "/picturedisplaymodule" << name << "/image";
  portImage->open(yarpPortName.str().c_str());
  
}

char_seq* PictureDisplayModule::readImage(bool blocking) {
  Bottle *b = portImage->read(blocking);
  if (b != NULL) {
    for (int i = 0; i < b->size(); ++i) {
