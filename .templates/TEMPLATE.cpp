#include "TEMPLATE.h"

TEMPLATE::TEMPLATE() {
    name="TEMPLATE";
    logger.Set_Name(name);
}

int TEMPLATE::Init()
{
    for (auto parameter : parameters) {
        std::cout << parameter.first << " value is " << parameter.second << std::endl;
    }

    logger.LOG_INFO("Initializing...");
    return 0;
}

int TEMPLATE::Cycle_Step()
{

    return 0;
}

int TEMPLATE::Deinit()
{

    logger.LOG_INFO("Deinitializing...");
    return 0;
}

// Factory Methods
Module* Create_Instance()
{
    return new ZmqPipeline;
}

void Destroy_Instance(Module* module)
{
    delete module;
}