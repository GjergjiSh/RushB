#include "ModuleManager.h"

int main(int argc, char* argv[])
{
    ModuleManager module_handler("ModuleConfig.xml", NO_VERB);

    if (module_handler.Init() == 0) {
        module_handler.Run();
    }

    module_handler.Deinit();
    return 0;
}