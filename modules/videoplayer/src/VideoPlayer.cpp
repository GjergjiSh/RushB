#include "VideoPlayer.h"
#include<unistd.h>

VideoPlayer::VideoPlayer()
{
    this->name = "VideoPlayer";
}

int VideoPlayer::Init()
{
    LOG_INFO("Initializing...");
    XInitThreads();
    cv::namedWindow("Video Viewer");

    return 0;
}

int VideoPlayer::Cycle_Step()
{
    cv::Mat frame(480, 640, CV_8UC1, this->shared_data->video.frame);
    if (frame.data) {

        cv::imshow("Video Viewer", frame);
        //cv::cvtColor(frame, frame, cv::COLOR_GRAY2RGB);
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