#include "ModuleInterface.h"

#include <gst/gst.h>
#include <memory>

#define LOG_INFO(msg) \
    std::cout << "[I][VideoPub] " << msg << std::endl;
#define LOG_TIME_INFO(msg, time) \
    std::cerr << "[I][VideoPub] " << msg << " [" << time << " ms]" << std::endl;
#define LOG_WARNING(msg) \
    std::cerr << "[W][VideoPub] " << msg << std::endl;
#define LOG_ERROR_DESCRIPTION(msg, err) \
    std::cerr << "[E][VideoPub] " << msg << " " << err << std::endl;
#define LOG_ERROR(msg) \
    std::cerr << "[E][VideoPub] " << msg << std::endl;



/**************************************    Pipeline    *********************************

    gst-launch-1.0 -v v4l2src device=/dev/video0 ! \
    videoconvert ! \
    x264enc tune=zerolatency bitrate=2000 speed-preset=ultrafast ! \
    rtph264pay ! \
    udpsink host=xxxx.xx.xx.xx port=xxxx

 ****************************************************************************************/


typedef struct
{
    GstElement* pipe;
    GstElement* v4l2src;
    GstElement* videoconvert;
    GstElement* x264enc;
    GstElement* rtph264pay;
    GstElement* udpsink;
} VideoPipeline_t;


class VideoPub : public Module {

public:
    VideoPub();
    int Init(void) override;
    int Cycle_Step(void) override;
    int Deinit(void) override;

private:
    int Construct_Pipeline();
    int Destroy_Pipeline();
    int Set_Pipeline_State_Playing();
    int Create_Elements();
    int Configure_Elements();
    int Link_Elements();

    std::shared_ptr<VideoPipeline_t> pipeline;
};