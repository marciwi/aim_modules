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

#ifndef MORSEPIFACEMODULE_H_
#define MORSEPIFACEMODULE_H_

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

class MorsePifaceModule {
private:
  Param *cliParam;
  
  std::string dummyMorse;
protected:
  static const int channel_count = 1;
  const char* channel[1];
public:
  // Default constructor
  MorsePifaceModule();
  
  // Default destructor
  virtual ~MorsePifaceModule();
  
  // Extend this with your own code, first call MorsePifaceModule::Init(name);
  void Init(std::string& name);
  
  // Function to get Param struct (to subsequently set CLI parameters)
  inline Param *GetParam() { return cliParam; }
  
  // Overwrite this function with your own code
  virtual void Tick() = 0;
  
  // Overwrite this function with your own code
  bool Stop() { return false; }
  
  // Read from this function and assume it means something
  // Remark: check if result is not NULL
  std::string *readMorse(bool blocking=false);
  
};
} // End of namespace

#endif // MORSEPIFACEMODULE_H_
