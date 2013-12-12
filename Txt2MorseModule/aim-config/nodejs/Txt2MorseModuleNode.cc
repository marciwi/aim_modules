#define BUILDING_NODE_EXTENSION
#include <node.h>
#include <Txt2MorseModuleExt.h>

using namespace v8;
using namespace rur;

void RegisterModule(Handle<Object> exports) {
  Txt2MorseModuleExt::NodeRegister(exports);
}

NODE_MODULE(Txt2MorseModule, RegisterModule)
