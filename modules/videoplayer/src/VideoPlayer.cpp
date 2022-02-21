#include "VideoPlayer.h"


VideoPlayer::VideoPlayer()
{
    this->name = "VideoPlayer";
}

int VideoPlayer::Init()
{
    LOG_INFO("Initializing...");
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
    LOG_INFO("Deinitializing...");
    cv::destroyAllWindows();
    return 0;
}

extern "C" Module* Create() { return new VideoPlayer; }
extern "C" void Destroy(Module* module) { delete module; }