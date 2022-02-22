#include "ModuleInterface.h"

#include <CppLinuxSerial/Exception.hpp>
#include <CppLinuxSerial/SerialPort.hpp>

#define LOG_INFO(msg) \
    std::cout << "[I][InoLink] " << msg << std::endl;
#define LOG_TIME_INFO(msg, time) \
    std::cerr << "[I][InoLink] " << msg << " [" << time << " ms]" << std::endl;
#define LOG_WARNING(msg) \
    std::cerr << "[W][InoLink] " << msg << std::endl;
#define LOG_ERROR_DESCRIPTION(msg, err) \
    std::cerr << "[E][InoLink] " << msg << " " << err << std::endl;
#define LOG_ERROR(msg) \
    std::cerr << "[E][InoLink] " << msg << std::endl;

class InoLink : public Module {

public:
    InoLink();
    int Init(void) override;
    int Cycle_Step(void) override;
    int Deinit(void) override;

private:
    int Init_Serial_Port();
    int Deinit_Serial_Port();
    std::string Convert_Servo_Vals();
    int Write_Servo_Vals();

    mn::CppLinuxSerial::SerialPort* serial_port;
};