#include "TEMPLATE.h"

TEMPLATE::TEMPLATE() {
    this->name="TEMPLATE";
}

int TEMPLATE::Init()
{
    for (auto parameter : parameters) {
        std::cout << parameter.first << " value is " << parameter.second << std::endl;
    }

    LOG_INFO("Initializing...");
    return 0;
}

int TEMPLATE::Cycle_Step()
{

    return 0;
}

int TEMPLATE::Deinit()
{

    LOG_INFO("Deinitializing...");
    return 0;
}

extern "C" Module* Create() { return new TEMPLATE;}
extern "C" void Destroy(Module* module) {delete module;}