#include "VideoPlayer.h"


VideoPlayer::VideoPlayer()
{
    name = "VideoPlayer";
    logger.Set_Name(name);
}

int VideoPlayer::Init()
{
    cv::namedWindow("Video Viewer");

    m_frame_height = std::stoi(parameters.at("FRAME_HEIGHT"));
    m_frame_width = std::stoi(parameters.at("FRAME_WIDTH"));
    Set_Resize(parameters.at("RESIZE"));

    return 0;
}

int VideoPlayer::Cycle_Step()
{
    m_frame_bgr= cv::Mat(m_frame_height, m_frame_width, CV_8UC3, (void *)this->shared_data->video.frame);
    if (m_frame_bgr.data) {
        cv::cvtColor(m_frame_bgr, m_frame_rgb, cv::COLOR_RGB2BGR);

        if (m_resize_frames)
            cv::resize(m_frame_rgb, m_frame_rgb, cv::Size(640, 460));

        cv::imshow("Video Viewer", m_frame_rgb);
        cv::waitKey(1);
    }

    return 0;
}

int VideoPlayer::Deinit()
{
    cv::destroyAllWindows();
    return 0;
}

void VideoPlayer::Set_Resize(const std::string &resize_parameter) {
    if (resize_parameter == "1" ||
        resize_parameter == "TRUE" ||
        resize_parameter == "True") {
        m_resize_frames = true;
    } else {
        m_resize_frames = false;
    }
}

// Factory Methods
Module *Create_Instance() {
    return new VideoPlayer;
}

void Destroy_Instance(Module *module) {
    delete module;
}