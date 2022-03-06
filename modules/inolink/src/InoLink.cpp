#include "InoLink.h"

InoLink::InoLink() {
    name="InoLink";
    logger.Set_Name(name);
}

int InoLink::Init()
{
    try {
        std::string port = parameters.at("SERIAL_PORT");
        m_serial_port = new mn::CppLinuxSerial::SerialPort();
        m_serial_port->SetDevice(port);
        m_serial_port->SetBaudRate(std::stoi(parameters.at("BAUD_RATE")));

        m_serial_port->SetTimeout(-1);
        m_serial_port->Open();
        logger.Info("Arduino board connected on port: " + port);
    } catch (mn::CppLinuxSerial::Exception& ex) {
        logger.Error_Description("Connection to Arduino failed to initialize.", ex.what());
        return -1;
    }
    return 0;
}

int InoLink::Cycle_Step()
{
    try {
        const std::string output_servo_string =  Convert_Servo_Vals();
        m_serial_port->Write(output_servo_string);
    } catch (mn::CppLinuxSerial::Exception &ex) {
        logger.Error_Description("Failed to write driver wishes to the robot.", ex.what());
        return -1;
    }
    return 0;
}

int InoLink::Deinit()
{
    try {
        m_serial_port->Close();
        logger.Info("Connection to Arduino deinitialized");
    } catch (mn::CppLinuxSerial::Exception& ex) {
        logger.Error_Description("Connection to Arduino failed to deinitialize", ex.what());
        delete m_serial_port;
        return -1;
    }

    delete m_serial_port;
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

// Factory Method
Module *Create_Instance() {
    return new InoLink;
}

void Destroy_Instance(Module *module) {
    delete module;
}