#include "ModuleInterface.h"
#include "Logger.h"

#include <CppLinuxSerial/Exception.hpp>
#include <CppLinuxSerial/SerialPort.hpp>

class InoLink : public Module {

public:
    InoLink();
    int Init(void) override;
    int Cycle_Step(void) override;
    int Deinit(void) override;

    Logger logger;

private:
    int Init_Serial_Port();
    int Deinit_Serial_Port();
    std::string Convert_Servo_Vals();
    int Write_Servo_Vals();

    mn::CppLinuxSerial::SerialPort* serial_port;
};