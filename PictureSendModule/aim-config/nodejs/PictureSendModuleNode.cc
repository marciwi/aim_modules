#define BUILDING_NODE_EXTENSION
#include <node.h>
#include <PictureSendModuleExt.h>

using namespace v8;
using namespace rur;

void RegisterModule(Handle<Object> exports) {
  PictureSendModuleExt::NodeRegister(exports);
}

NODE_MODULE(PictureSendModule, RegisterModule)
