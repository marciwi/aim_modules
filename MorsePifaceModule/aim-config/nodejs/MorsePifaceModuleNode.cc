#define BUILDING_NODE_EXTENSION
#include <node.h>
#include <MorsePifaceModuleExt.h>

using namespace v8;
using namespace rur;

void RegisterModule(Handle<Object> exports) {
  MorsePifaceModuleExt::NodeRegister(exports);
}

NODE_MODULE(MorsePifaceModule, RegisterModule)
