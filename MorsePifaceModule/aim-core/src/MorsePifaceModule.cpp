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
 * @date                 dec 10, 2013
 * @license              Apache Licence
 */

#include "MorsePifaceModule.h"

namespace rur {

MorsePifaceModule::MorsePifaceModule():
  cliParam(0)
{
  const char* const channel[1] = {"readMorse"};
  cliParam = new Param();
  dummyMorse = std::string(0);
}

MorsePifaceModule::~MorsePifaceModule() {
  delete cliParam;
}

void MorsePifaceModule::Init(std::string & name) {
  cliParam->module_id = name;
  
}

std::string* MorsePifaceModule::readMorse(bool blocking) {
  return &dummyMorse;
}

} // namespace
