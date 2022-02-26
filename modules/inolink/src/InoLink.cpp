#include "InoLink.h"

InoLink::InoLink() {
    name="InoLink";
    logger.Set_Name(name);
}

int InoLink::Init()
{
    logger.LOG_INFO("Initializing...");
    return Init_Serial_Port();
}

int InoLink::Cycle_Step()
{
    return Write_Servo_Vals();
}

int InoLink::Deinit()
{
    logger.LOG_INFO("Deinitializing...");
    if (Deinit_Serial_Port() != 0) {
        return -1;
        delete serial_port;
    }

    delete serial_port;
    return 0;
}

int InoLink::Init_Serial_Port()
{
    try {
        std::string port = parameters.at("SERIAL_PORT");
        serial_port = new mn::CppLinuxSerial::SerialPort();
        serial_port->SetDevice(port);
        serial_port->SetBaudRate(std::stoi(parameters.at("BAUD_RATE")));

        serial_port->SetTimeout(-1);
        serial_port->Open();
        logger.LOG_INFO("Arduino board connected on port: " + port);
    } catch (mn::CppLinuxSerial::Exception& ex) {
        logger.LOG_ERROR_DESCRIPTION("Connection to Arduino failed to initialize." , ex.what());
        return -1;
    }
    return 0;
}

int InoLink::Deinit_Serial_Port()
{
    try {
        serial_port->Close();
        logger.LOG_INFO("Connection to Arduino deinitialized");
    } catch (mn::CppLinuxSerial::Exception& ex) {
        logger.LOG_ERROR_DESCRIPTION("Connection to Arduino failed to deinitialize", ex.what());
        return -1;
    }
    return 0;
}

std::string InoLink::Convert_Servo_Vals()
{
    /* (int)(((-1 * stick_coordinates[RIGHTSTICK].x + 32767) * 90) / 32767) */
    int c_left_servo = ((shared_data->servos.left_servo + 100) * 90) / 100;
    int c_right_servo = ((shared_data->servos.right_servo + 100) * 90) / 100;
    int c_top_servo = ((shared_data->servos.top_servo + 100) * 90) / 100;

    std::string left_servo = std::to_string(c_left_servo) + "@";
    std::string right_servo = std::to_string(c_right_servo) + "#";
    std::string top_servo = std::to_string(c_top_servo) + "$";

    std::string output_servo_string = "!"+ left_servo
                                         + right_servo
                                         + top_servo +"\n";
    return output_servo_string;
}

int InoLink::Write_Servo_Vals()
{
    try {
        const std::string output_servo_string =  Convert_Servo_Vals();
        serial_port->Write(output_servo_string);
    } catch (mn::CppLinuxSerial::Exception& ex) {
        logger.LOG_ERROR_DESCRIPTION("Failed to write driver wishes to the robot.", ex.what());
        return -1;
    }
    return 0;
}

extern "C" Module* Create() { return new InoLink;}
extern "C" void Destroy(Module* module) {delete module;}