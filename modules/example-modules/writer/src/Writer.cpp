#include "Writer.h"

Writer::Writer()
{
    name = "Writer";
    logger.Set_Name(name);
}

int Writer::Init()
{
    try {

    } catch (std::exception& e) {
        logger.LOG_INFO(std::string("Top Servo Will be Set to: ").append(parameters.at("TOP_SERVO")));
        logger.LOG_INFO(std::string("Left Servo Will be Set to: ").append(parameters.at("LEFT_SERVO")));
        logger.LOG_INFO(std::string("Right Servo Will be Set to: ").append(parameters.at("RIGHT_SERVO")));

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
        logger.LOG_ERROR_DESCRIPTION("Failed to set servo values: ", e.what());
        return -1;
    }
    return 0;
}

int Writer::Deinit()
{
    return 0;
}

// Factory Method
std::shared_ptr<Module> Create_Instance()
{
    return std::make_shared<Writer>();
}