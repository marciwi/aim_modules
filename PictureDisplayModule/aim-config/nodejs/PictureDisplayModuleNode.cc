#define BUILDING_NODE_EXTENSION
#include <node.h>
#include <PictureDisplayModuleExt.h>

using namespace v8;
using namespace rur;

void RegisterModule(Handle<Object> exports) {
  PictureDisplayModuleExt::NodeRegister(exports);
}

NODE_MODULE(PictureDisplayModule, RegisterModule)
