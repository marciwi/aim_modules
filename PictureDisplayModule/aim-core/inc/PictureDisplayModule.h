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

#ifndef PICTUREDISPLAYMODULE_H_
#define PICTUREDISPLAYMODULE_H_

#include <string>
#include <vector>
#include <string>
#include <vector>
#include <sstream>
#include <yarp/os/BufferedPort.h>
#include <yarp/os/Network.h>
#include <yarp/os/Bottle.h>

namespace rur {

struct Param {
  std::string module_id;
  int parameter;
};

typedef std::vector<char> char_seq;

class PictureDisplayModule {
private:
  Param *cliParam;
  
  yarp::os::Network yarp;
  char_seq portImageBuf;
  yarp::os::BufferedPort<yarp::os::Bottle> *portImage;
protected:
  static const int channel_count = 1;
  const char* channel[1];
  // Read from this function and assume it means something
  // Remark: caller is responsible for evoking vector->clear()
  char_seq *readImage(bool blocking=false);
  
public:
  PictureDisplayModule();
  
  ~PictureDisplayModule();
  
  // Extend this with your own code, first call PictureDisplayModule::Init(name);
  void Init(std::string& name);
  
  // Function to get Param struct (to subsequently set CLI parameters)
  inline Param *GetParam() { return cliParam; }
  
  // Overwrite this function with your own code
  virtual void Tick() {}
  
  // Overwrite this function with your own code
  bool Stop() { return false; }
  
};
} // End of namespace

#endif // PICTUREDISPLAYMODULE_H_
