#include "InoLink.h"

InoLink::InoLink() {
    this->name="InoLink";
}

int InoLink::Init()
{
    LOG_INFO("Initializing...");
    return Init_Serial_Port();
}

int InoLink::Cycle_Step()
{
    return Update_Servos();
}

int InoLink::Deinit()
{
    if (Deinit_Serial_Port() != 0) {
        return -1;
        delete serial_port;
    }
    delete serial_port;
    LOG_INFO("Deinitializing...");
    return 0;
}

int InoLink::Init_Serial_Port()
{
    try {
        std::string port = parameters.at("SERIAL_PORT");
        this->serial_port = new mn::CppLinuxSerial::SerialPort(port,
            mn::CppLinuxSerial::BaudRate::B_460800);

        this->serial_port->SetTimeout(-1);
        this->serial_port->Open();
        LOG_INFO("Arduino board connected on port: " + port);
    } catch (mn::CppLinuxSerial::Exception& ex) {
        LOG_ERROR_DESCRIPTION("Connection to Arduino failed to initialize." , ex.what());
        return -1;
    }
    return 0;
}

int InoLink::Deinit_Serial_Port()
{
    try {
        this->serial_port->Close();
        LOG_INFO("Connection to Arduino deinitialized")
    } catch (mn::CppLinuxSerial::Exception& ex) {
        LOG_ERROR_DESCRIPTION("InoLink ] Connection to Arduino failed to deinitialize", ex.what());
        return -1;
    }
    return 0;
}

int InoLink::Update_Servos()
{
    try {
        std::string left_servo = std::to_string(shared_data->servos.left_servo) + "%";
        std::string right_servo = std::to_string(shared_data->servos.right_servo) + "#";
        std::string top_servo = std::to_string(shared_data->servos.top_servo)  + "&";
        std::string s_driver_wish = left_servo + right_servo + top_servo;

        std::cout << s_driver_wish << std::endl;
        this->serial_port->Write("!" + s_driver_wish + "\n");

    } catch (mn::CppLinuxSerial::Exception& ex) {
        LOG_ERROR_DESCRIPTION("Failed to write driver wishes to the robot.", ex.what());
        return -1;
    }
    return 0;
}

extern "C" Module* Create() { return new InoLink;}
extern "C" void Destroy(Module* module) {delete module;}