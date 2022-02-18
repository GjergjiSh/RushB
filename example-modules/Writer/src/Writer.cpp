#include "Writer.h"

Writer::Writer()
{
    this->name = "Writer";
}

int Writer::Init()
{
    try {

    } catch (std::exception& e) {
        std::cout << "Top Servo Will be Set to: " << parameters.at("TOP_SERVO") << std::endl;
        std::cout << "Left Servo Will be Set to: " << parameters.at("LEFT_SERVO") << std::endl;
        std::cout << "Right Servo Will be Set to: " << parameters.at("RIGHT_SERVO") << std::endl;
        return -1;
    }
    return 0;
}

int Writer::Cycle_Step()
{
    try {
        shared_data->servos.top_servo = stoi(this->parameters.at("TOP_SERVO"));
        shared_data->servos.left_servo = stoi(this->parameters.at("LEFT_SERVO"));
        shared_data->servos.right_servo = stoi(this->parameters.at("RIGHT_SERVO"));

    } catch (std::exception& e) {
        LOG_ERROR_DESCRIPTION("Failed to set servo values: ", e.what());
        return -1;
    }
    return 0;
}

int Writer::Deinit()
{
    return 0;
}

extern "C" Module* Create() { return new Writer; }
extern "C" void Destroy(Module* module) { delete module; }