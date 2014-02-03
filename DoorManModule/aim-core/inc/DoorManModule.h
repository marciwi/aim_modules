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

#ifndef DOORMANMODULE_H_
#define DOORMANMODULE_H_

#include <string>
#include <vector>
#include <string>
#include <vector>

namespace rur {

struct Param {
  std::string module_id;
  int parameter;
};

typedef std::vector<int> long_seq;

class DoorManModule {
private:
  Param *cliParam;
  
  int dummyopendoor;
protected:
  static const int channel_count = 1;
  const char* channel[1];
public:
  // Default constructor
  DoorManModule();
  
  // Default destructor
  virtual ~DoorManModule();
  
  // Extend this with your own code, first call DoorManModule::Init(name);
  void Init(std::string& name);
  
  // Function to get Param struct (to subsequently set CLI parameters)
  inline Param *GetParam() { return cliParam; }
  
  // Overwrite this function with your own code
  virtual void Tick() = 0;
  
  // Overwrite this function with your own code
  bool Stop() { return false; }
  
  // Read from this function and assume it means something
  // Remark: check if result is not NULL
  int *readopendoor(bool blocking=false);
  
};
} // End of namespace

#endif // DOORMANMODULE_H_
