#include "ModuleHandler.h"
#include <iostream>

int main(int argc, char* argv[])
{
    ModuleHandler module_handler("/home/shorty/Repos/control-center/resources/Modules.xml");
    module_handler.Init();
    module_handler.Run();
    module_handler.Deinit();


    return 0;
}