#include "ModuleInterface.h"

#define LOG_INFO(msg) \
    std::cout << "[I][Reader] " << msg << std::endl;
#define LOG_TIME_INFO(msg, time) \
    std::cerr << "[I][Reader] " << msg << " [" << time << " ms]" << std::endl;
#define LOG_WARNING(msg) \
    std::cerr << "[W][Reader] " << msg << std::endl;
#define LOG_ERROR_DESCRIPTION(msg, err) \
    std::cerr << "[E][Reader] " << msg << " " << err << std::endl;
#define LOG_ERROR(msg) \
    std::cerr << "[E][Reader] " << msg << std::endl;

class Reader : public Module {

public:
    Reader();
    int Init(void) override;
    int Cycle_Step(void) override;
    int Deinit(void) override;
};