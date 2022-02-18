#include "ModuleInterface.h"

#define LOG_INFO(msg) \
    std::cout << "[I][Writer] " << msg << std::endl;
#define LOG_TIME_INFO(msg, time) \
    std::cerr << "[I][Writer] " << msg << " [" << time << " ms]" << std::endl;
#define LOG_WARNING(msg) \
    std::cerr << "[W][Writer] " << msg << std::endl;
#define LOG_ERROR_DESCRIPTION(msg, err) \
    std::cerr << "[E][Writer] " << msg << " " << err << std::endl;
#define LOG_ERROR(msg) \
    std::cerr << "[E][Writer] " << msg << std::endl;

class Writer : public Module {

public:
    Writer();
    int Init(void) override;
    int Cycle_Step(void) override;
    int Deinit(void) override;
};