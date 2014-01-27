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
 * @author               Marc Hulscher
 * @copyright            DO bots
 * @date                 jan 27, 2014
 * @license              Apache Licence
 */

#include "DoorManModule.h"

namespace rur {

DoorManModule::DoorManModule():
  cliParam(0)
{
  const char* const channel[2] = {"readopendoor", "writesend433"};
  cliParam = new Param();
  dummyopendoor = char_seq(0);
}

DoorManModule::~DoorManModule() {
  delete cliParam;
}

void DoorManModule::Init(std::string & name) {
  cliParam->module_id = name;
  
}

char_seq* DoorManModule::readopendoor(bool blocking) {
  return &dummyopendoor;
}

bool DoorManModule::writesend433(const char_seq &output) {
  return true;
}

} // namespace
