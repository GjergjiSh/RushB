#include "ModuleInterface.h"

#include <gst/gst.h>
#include <mutex>

/**************************************    Pipeline    *********************************

    gst-launch-1.0 -v udpsrc port=5553 ! \
   "application/x-rtp, media=video, clock-rate=90000, encoding-name=H264, payload=96" ! \
    rtph264depay ! \
    decodebin ! \
    videoconvert ! \
    queue ! \
    autovideosink

 ****************************************************************************************/

typedef struct
{
    GstElement* pipe;
    GstElement* udpsrc;
    GstElement* filter;
    GstElement* rtph264depay;
    GstElement* decodebin;
    GstElement* videoconvert;
    GstElement* queue;
    GstElement* convert_filter;
    GstElement* videosink;
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

    std::shared_ptr<VideoPipeline_t> m_pipeline;
};