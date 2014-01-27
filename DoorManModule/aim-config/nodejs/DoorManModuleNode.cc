#define BUILDING_NODE_EXTENSION
#include <node.h>
#include <DoorManModuleExt.h>

using namespace v8;
using namespace rur;

void RegisterModule(Handle<Object> exports) {
  DoorManModuleExt::NodeRegister(exports);
}

NODE_MODULE(DoorManModule, RegisterModule)
