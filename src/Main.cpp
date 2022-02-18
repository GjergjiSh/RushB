#include "ModuleHandler.h"
#include <iostream>

int main(int argc, char* argv[])
{
    ModuleHandler module_handler("Modules.xml", NO_VERB);

    if (module_handler.Init() == 0) {
        module_handler.Run();
    }

    module_handler.Deinit();
    return 0;
}