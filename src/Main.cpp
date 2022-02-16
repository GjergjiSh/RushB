#include "ModuleHandler.h"
#include <iostream>

int main(int argc, char* argv[])
{
    ModuleHandler module_handler("Modules.xml", NO_VERB);
    module_handler.Init();
    module_handler.Run();
    module_handler.Deinit();
    return 0;
}