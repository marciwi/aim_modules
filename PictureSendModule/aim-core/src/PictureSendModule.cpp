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

#include "PictureSendModule.h"

namespace rur {

PictureSendModule::PictureSendModule():
  cliParam(0)
{
  const char* const channel[1] = {"writeImage"};
  cliParam = new Param();
}

PictureSendModule::~PictureSendModule() {
  delete cliParam;
}

void PictureSendModule::Init(std::string & name) {
  cliParam->module_id = name;
  
}

bool PictureSendModule::writeImage(const char_seq &input) {
  return true;
}

} // namespace
