#include "Reader.h"
#include <stdio.h>
#include <unistd.h>
Reader::Reader() {
    this->name="Reader";
}

int Reader::Init()
{
    std::cout << parameters.at("HELLO") << std::endl;
    return 0;
}

int Reader::Cycle_Step()
{
    std::cout << "Top Servo: " << this->shared_data->servos.top_servo << std::endl;
    std::cout << "Left Servo: " << this->shared_data->servos.left_servo << std::endl;
    std::cout << "Right Servo: " << this->shared_data->servos.right_servo << std::endl;

    return 0;
}

int Reader::Deinit()
{
    return 0;
}

extern "C" Module* Create() { return new Reader;}
extern "C" void Destroy(Module* module) {delete module;}