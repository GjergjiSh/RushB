#include "Reader.h"


Reader::Reader() {
    name="Reader";
    logger.Set_Name(name);
}

int Reader::Init()
{
    try {
    logger.LOG_INFO(std::string("Reder says: ").append(parameters.at("HELLO")));

    } catch(std::exception& e) {
        logger.LOG_ERROR_DESCRIPTION("Failed to read parameter: ", e.what());
        return -1;
    }
    return 0;
}

int Reader::Cycle_Step()
{
    logger.LOG_INFO(std::string("Top Servo: ").append(parameters.at(std::to_string(shared_data->servos.top_servo))));
    logger.LOG_INFO(std::string("Left Servo: ").append(parameters.at(std::to_string(shared_data->servos.left_servo))));
    logger.LOG_INFO(std::string("Right Servo: ").append(parameters.at(std::to_string(shared_data->servos.right_servo))));

    return 0;
}

int Reader::Deinit()
{
    return 0;
}

extern "C" Module* Create() { return new Reader;}
extern "C" void Destroy(Module* module) {delete module;}