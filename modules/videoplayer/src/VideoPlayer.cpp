#include "VideoPlayer.h"


VideoPlayer::VideoPlayer()
{
    name = "VideoPlayer";
    logger.Set_Name(name);
}

int VideoPlayer::Init()
{
    logger.Info("Initializing...");
    cv::namedWindow("Video Viewer");

    return 0;
}

int VideoPlayer::Cycle_Step()
{
    m_frame_bgr= cv::Mat(480, 640, CV_8UC3, (void *)this->shared_data->video.frame);
    if (m_frame_bgr.data) {
        cv::cvtColor(m_frame_bgr, m_frame_rgb, cv::COLOR_RGB2BGR);
        cv::imshow("Video Viewer", m_frame_rgb);
        cv::waitKey(1);
    }

    return 0;
}

int VideoPlayer::Deinit()
{
    logger.Info("Deinitializing...");
    cv::destroyAllWindows();
    return 0;
}

// Factory Method
std::shared_ptr<Module> Create_Instance()
{
    return std::make_shared<VideoPlayer>();
}