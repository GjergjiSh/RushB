#include "VideoPlayer.h"


VideoPlayer::VideoPlayer()
{
    name = "VideoPlayer";
    logger.Set_Name(name);
}

int VideoPlayer::Init()
{
    logger.LOG_INFO("Initializing...");
    cv::namedWindow("Video Viewer");

    return 0;
}

int VideoPlayer::Cycle_Step()
{
    frame_bgr= cv::Mat(480, 640, CV_8UC3, (void *)this->shared_data->video.frame);
    if (frame_bgr.data) {
        cv::cvtColor(frame_bgr, frame_rgb, cv::COLOR_RGB2BGR);
        cv::imshow("Video Viewer", frame_rgb);
        cv::waitKey(1);
    }

    return 0;
}

int VideoPlayer::Deinit()
{
    logger.LOG_INFO("Deinitializing...");
    cv::destroyAllWindows();
    return 0;
}

// Factory Method
extern "C" std::shared_ptr<Module> Create_Instance()
{
    return std::make_shared<VideoPlayer>();
}