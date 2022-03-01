#include <CppLinuxSerial/Exception.hpp>
#include <CppLinuxSerial/SerialPort.hpp>

#include "IModuleInterface.h"

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

    mn::CppLinuxSerial::SerialPort* m_serial_port;
};