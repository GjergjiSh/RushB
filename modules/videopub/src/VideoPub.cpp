#include "VideoPub.h"

VideoPub::VideoPub() {
    name="VideoPub";
    logger.Set_Name(name);
}

int VideoPub::Init()
{
    logger.LOG_INFO("Initializing...");

    if (Construct_Pipeline() != 0) return -1;
    if (Set_Pipeline_State_Playing() != 0) return -1;

    return 0;
}

int VideoPub::Cycle_Step()
{
    return 0;
}

int VideoPub::Deinit()
{
    logger.LOG_INFO("Deinitializing...");
    return Destroy_Pipeline();
}

int VideoPub::Construct_Pipeline()
{
    this->pipeline = std::make_shared<VideoPipeline_t>();

    gst_init(NULL, NULL);
    if (Create_Elements() != 0) return -1;
    if (Configure_Elements() != 0) return -1;
    if (Link_Elements() != 0) return -1;

    logger.LOG_INFO("Video pipeline successfuly constructed");
    return 0;
}

int VideoPub::Create_Elements()
{
    this->pipeline->pipe = gst_pipeline_new("Publisher Video Pipeline");
    this->pipeline->v4l2src = gst_element_factory_make("v4l2src", NULL);
    this->pipeline->videoconvert = gst_element_factory_make("videoconvert", NULL);
    this->pipeline->x264enc = gst_element_factory_make("x264enc", NULL);
    this->pipeline->rtph264pay = gst_element_factory_make("rtph264pay", NULL);
    this->pipeline->udpsink = gst_element_factory_make("udpsink", NULL);

    if (!pipeline->pipe ||
        !this->pipeline->v4l2src ||
        !this->pipeline->videoconvert ||
        !this->pipeline->x264enc ||
        !this->pipeline->rtph264pay ||
        !this->pipeline->udpsink) {

        logger.LOG_ERROR("Elements could not be created");
        return -1;
    }

    gst_bin_add_many(GST_BIN(pipeline->pipe),
        this->pipeline->v4l2src,
        this->pipeline->videoconvert,
        this->pipeline->x264enc,
        this->pipeline->rtph264pay,
        this->pipeline->udpsink, NULL);

    return 0;
}

int VideoPub::Configure_Elements()
{
    g_object_set(pipeline->v4l2src, "device", parameters.at("CAMERA_INDEX").c_str(), NULL);
    g_object_set(pipeline->x264enc, "tune", 4, NULL);
    g_object_set(pipeline->x264enc, "speed-preset", 1, NULL);
    g_object_set(pipeline->x264enc, "bitrate", std::stoi(parameters.at("BITRATE")), NULL);
    g_object_set(G_OBJECT(pipeline->udpsink), "host", parameters.at("REMOTE_HOST").c_str(), NULL);
    g_object_set(G_OBJECT(pipeline->udpsink), "port", std::stoi(parameters.at("OUT_PORT")), NULL);

    return 0;
}

int VideoPub::Link_Elements()
{
    if (!gst_element_link_many(
        pipeline->v4l2src,
        pipeline->videoconvert,
        pipeline->x264enc,
        pipeline->rtph264pay,
        pipeline->udpsink, NULL)) {
        logger.LOG_ERROR("Elements could not be linked");
        gst_object_unref(pipeline->pipe);
        return -1;
    }
    return 0;
}

int VideoPub::Destroy_Pipeline()
{
    gst_element_set_state(this->pipeline->pipe, GST_STATE_NULL);
    gst_object_unref(GST_OBJECT(this->pipeline->pipe));

    logger.LOG_INFO("Video pipeline destroyed");
    return 0;
}

int VideoPub::Set_Pipeline_State_Playing()
{
    GstStateChangeReturn ret = gst_element_set_state(pipeline->pipe, GST_STATE_PLAYING);
    if (ret == GST_STATE_CHANGE_FAILURE) {
        logger.LOG_ERROR("Unable to set the pipeline to the playing state");
        gst_object_unref(pipeline->pipe);
        return -1;
    } else {
        logger.LOG_INFO("Video pipeline set to playing");
    }
    return 0;
}


extern "C" Module* Create() { return new VideoPub;}
extern "C" void Destroy(Module* module) {delete module;}