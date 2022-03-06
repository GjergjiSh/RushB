#include "VideoPub.h"

VideoPub::VideoPub() {
    name="VideoPub";
    logger.Set_Name(name);
}

int VideoPub::Init()
{
    logger.Info("Initializing...");

    if (Construct_Pipeline() != 0) return -1;
    if (Set_Pipeline_State_Playing() != 0) return -1;

    return 0;
}

int VideoPub::Cycle_Step()
{
    /* Video Compression and Publishing handled in gstreamer pipeline */
    return 0;
}

int VideoPub::Deinit()
{
    logger.Info("Deinitializing...");
    return Destroy_Pipeline();
}

int VideoPub::Construct_Pipeline()
{
    this->m_pipeline = std::make_shared<VideoPipeline_t>();

    gst_init(nullptr, nullptr);
    if (Create_Elements() != 0) return -1;
    if (Configure_Elements() != 0) return -1;
    if (Link_Elements() != 0) return -1;

    logger.Info("Video pipeline successfully constructed");
    return 0;
}

int VideoPub::Create_Elements() {
    this->m_pipeline->pipe = gst_pipeline_new("Publisher Video Pipeline");
    this->m_pipeline->v4l2src = gst_element_factory_make("v4l2src", "source");
    this->m_pipeline->videoconvert = gst_element_factory_make("videoconvert", "conversion");
    this->m_pipeline->x264enc = gst_element_factory_make("x264enc", "decoding");
    this->m_pipeline->rtph264pay = gst_element_factory_make("rtph264pay", "pay");
    this->m_pipeline->udpsink = gst_element_factory_make("udpsink", "sink");

    if (!m_pipeline->pipe ||
        !this->m_pipeline->v4l2src ||
        !this->m_pipeline->videoconvert ||
        !this->m_pipeline->x264enc ||
        !this->m_pipeline->rtph264pay ||
        !this->m_pipeline->udpsink) {

        logger.Error("Elements could not be created");
        return -1;
    }

    gst_bin_add_many(GST_BIN(m_pipeline->pipe),
                     this->m_pipeline->v4l2src,
                     this->m_pipeline->videoconvert,
                     this->m_pipeline->x264enc,
                     this->m_pipeline->rtph264pay,
                     this->m_pipeline->udpsink, NULL);

    return 0;
}

int VideoPub::Configure_Elements() {
    try {
        g_object_set(m_pipeline->v4l2src, "device", parameters.at("CAMERA_INDEX").c_str(), NULL);
        g_object_set(m_pipeline->x264enc, "tune", 4, NULL);
        g_object_set(m_pipeline->x264enc, "speed-preset", 1, NULL);
        g_object_set(m_pipeline->x264enc, "bitrate", std::stoi(parameters.at("BITRATE")), NULL);
        g_object_set(G_OBJECT(m_pipeline->udpsink), "host", parameters.at("REMOTE_HOST").c_str(), NULL);
        g_object_set(G_OBJECT(m_pipeline->udpsink), "port", std::stoi(parameters.at("OUT_PORT")), NULL);
    } catch (std::exception &e) {
        logger.Error_Description("Failed to configure elements", e.what());
        return -1;
    }

    return 0;
}

int VideoPub::Link_Elements()
{
    if (!gst_element_link_many(
            m_pipeline->v4l2src,
            m_pipeline->videoconvert,
            m_pipeline->x264enc,
            m_pipeline->rtph264pay,
            m_pipeline->udpsink, NULL)) {
        logger.Error("Elements could not be linked");
        gst_object_unref(m_pipeline->pipe);
        return -1;
    }
    return 0;
}

int VideoPub::Destroy_Pipeline()
{
    gst_element_set_state(this->m_pipeline->pipe, GST_STATE_NULL);
    gst_object_unref(GST_OBJECT(this->m_pipeline->pipe));

    logger.Info("Video pipeline destroyed");
    return 0;
}

int VideoPub::Set_Pipeline_State_Playing()
{
    GstStateChangeReturn ret = gst_element_set_state(m_pipeline->pipe, GST_STATE_PLAYING);
    if (ret == GST_STATE_CHANGE_FAILURE) {
        logger.Error("Unable to set the pipeline to the playing m_state");
        gst_object_unref(m_pipeline->pipe);
        return -1;
    } else {
        logger.Info("Video pipeline set to playing");
    }
    return 0;
}


// Factory Methods
Module *Create_Instance() {
    return new VideoPub;
}

void Destroy_Instance(Module *module) {
    delete module;
}
