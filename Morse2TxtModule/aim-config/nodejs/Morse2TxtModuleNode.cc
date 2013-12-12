#define BUILDING_NODE_EXTENSION
#include <node.h>
#include <Morse2TxtModuleExt.h>

using namespace v8;
using namespace rur;

void RegisterModule(Handle<Object> exports) {
  Morse2TxtModuleExt::NodeRegister(exports);
}

NODE_MODULE(Morse2TxtModule, RegisterModule)
