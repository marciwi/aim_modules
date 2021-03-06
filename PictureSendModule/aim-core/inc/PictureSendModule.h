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

#ifndef PICTURESENDMODULE_H_
#define PICTURESENDMODULE_H_

#include <string>
#include <vector>
#include <string>
#include <vector>

namespace rur {

struct Param {
  std::string module_id;
  int parameter;
};

typedef std::vector<char> char_seq;

class PictureSendModule {
private:
  Param *cliParam;
  
protected:
  static const int channel_count = 1;
  const char* channel[1];
public:
  PictureSendModule();
  
  ~PictureSendModule();
  
  // Extend this with your own code, first call PictureSendModule::Init(name);
  void Init(std::string& name);
  
  // Function to get Param struct (to subsequently set CLI parameters)
  inline Param *GetParam() { return cliParam; }
  
  // Overwrite this function with your own code
  virtual void Tick() {}
  
  // Overwrite this function with your own code
  bool Stop() { return false; }
  
  // Write to this function and assume it ends up at some receiving module
  bool writeImage(const char_seq &input);
  
};
} // End of namespace

#endif // PICTURESENDMODULE_H_
