#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "ModuleInterface.h"

class VideoPlayer : public Module {

public:
    VideoPlayer();
    int Init(void) override;
    int Cycle_Step(void) override;
    int Deinit(void) override;

private:
    cv::Mat frame_bgr;
    cv::Mat frame_rgb;
};