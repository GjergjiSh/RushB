#include "ModuleInterface.h"

#define LOG_INFO(msg) \
    std::cout << "[I][TEMPLATE] " << msg << std::endl;
#define LOG_TIME_INFO(msg, time) \
    std::cerr << "[I][TEMPLATE] " << msg << " [" << time << " ms]" << std::endl;
#define LOG_WARNING(msg) \
    std::cerr << "[W][TEMPLATE] " << msg << std::endl;
#define LOG_ERROR_DESCRIPTION(msg, err) \
    std::cerr << "[E][TEMPLATE] " << msg << " " << err << std::endl;
#define LOG_ERROR(msg) \
    std::cerr << "[E][TEMPLATE] " << msg << std::endl;

class TEMPLATE : public Module {

public:
    TEMPLATE();
    int Init(void) override;
    int Cycle_Step(void) override;
    int Deinit(void) override;
};