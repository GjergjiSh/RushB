#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "IModuleInterface.h"

class VideoPlayer : public Module {

public:
    VideoPlayer();

    int Init() override;
    int Cycle_Step() override;
    int Deinit() override;

private:
    void Set_Resize(const std::string &resize_parameter);

    int m_frame_width;
    int m_frame_height;
    bool m_resize_frames;

    cv::Mat m_frame_bgr;
    cv::Mat m_frame_rgb;
};