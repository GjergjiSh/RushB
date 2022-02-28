#include "Reader.h"

Reader::Reader()
{
    name = "Reader";
    logger.Set_Name(name);
}

int Reader::Init()
{
    try {
        logger.Info(std::string("Reader says: ").append(parameters.at("HELLO")));

    } catch (std::exception& e) {
        logger.Error_Description("Failed to read parameter: ", e.what());
        return -1;
    }
    return 0;
}

int Reader::Cycle_Step()
{
    logger.Info(std::string("Top Servo: ").append((std::to_string(shared_data->servos.top_servo))));
    logger.Info(std::string("Left Servo: ").append((std::to_string(shared_data->servos.left_servo))));
    logger.Info(std::string("Right Servo: ").append((std::to_string(shared_data->servos.right_servo))));

    return 0;
}

int Reader::Deinit()
{
    return 0;
}

// Factory Method
std::shared_ptr<Module> Create_Instance()
{
    return std::make_shared<Reader>();
}