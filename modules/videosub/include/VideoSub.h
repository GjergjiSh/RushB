#include "ModuleInterface.h"

#include <gst/gst.h>
#include <mutex>

#define LOG_INFO(msg) \
    std::cout << "[I][VideoSub] " << msg << std::endl;
#define LOG_TIME_INFO(msg, time) \
    std::cerr << "[I][VideoSub] " << msg << " [" << time << " ms]" << std::endl;
#define LOG_WARNING(msg) \
    std::cerr << "[W][VideoSub] " << msg << std::endl;
#define LOG_ERROR_DESCRIPTION(msg, err) \
    std::cerr << "[E][VideoSub] " << msg << " " << err << std::endl;
#define LOG_ERROR(msg) \
    std::cerr << "[E][VideoSub] " << msg << std::endl;

/**************************************    Pipeline    *********************************

    gst-launch-1.0 -v udpsrc port=5553 ! \
   "application/x-rtp, media=video, clock-rate=90000, encoding-name=H264, payload=96" ! \
    rtph264depay ! \
    decodebin ! \
    videoconvert ! \
    queue ! \
    autovideosink

 ****************************************************************************************/
typedef void (*ReceivedSample_t)(const void *const data, const size_t size);

typedef struct
{
    GstElement* pipe;
    GstElement* udpsrc;
    GstElement* filter;
    GstElement* rtph264depay;
    GstElement* decodebin;
    GstElement* videoconvert;
    GstElement* queue;
    GstElement* videosink;
    ReceivedSample_t Received_Sample;
} VideoPipeline_t;

class VideoSub : public Module {

public:
    VideoSub();
    int Init(void) override;
    int Cycle_Step(void) override;
    int Deinit(void) override;

    std::mutex video_mutex;

private:
    int Construct_Pipeline();
    int Create_Elements();
    int Configure_Elements();
    int Link_Elements();
    int Destroy_Elements();
    int Destroy_Pipeline();
    int Set_Pipeline_State_Playing();
    void Start_Gloop();

    VideoPipeline_t* pipeline;
};