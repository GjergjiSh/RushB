#include "ModuleInterface.h"

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <X11/Xlib.h>


#define LOG_INFO(msg) \
    std::cout << "[I][VideoPlayer] " << msg << std::endl;
#define LOG_TIME_INFO(msg, time) \
    std::cerr << "[I][VideoPlayer] " << msg << " [" << time << " ms]" << std::endl;
#define LOG_WARNING(msg) \
    std::cerr << "[W][VideoPlayer] " << msg << std::endl;
#define LOG_ERROR_DESCRIPTION(msg, err) \
    std::cerr << "[E][VideoPlayer] " << msg << " " << err << std::endl;
#define LOG_ERROR(msg) \
    std::cerr << "[E][VideoPlayer] " << msg << std::endl;

class VideoPlayer : public Module {

public:
    VideoPlayer();
    int Init(void) override;
    int Cycle_Step(void) override;
    int Deinit(void) override;
};