#include "VideoSub.h"

static GstBusSyncReply Bus_Message_Callback(GstBus* bus, GstMessage* message, gpointer pipeline)
{
    switch (GST_MESSAGE_TYPE(message)) {
    case GST_MESSAGE_ERROR:
        gchar* debug;
        GError* error;
        gst_message_parse_error(message, &error, &debug);
        g_free(debug);
        g_printerr("[E][VideoPipeline ] %s\n", error->message);
        g_error_free(error);
        break;

    default:
        break;
    }
    return GST_BUS_PASS;
}

/********************************************************************************************************************************
 * @note: Used to link decodebin and videoconvert.
 * Decodebin uses something called a "sometimes-pad", which is basically a pad that will show up when a certain condition is met,
 * in decodebin's case that is media being decoded. gst-launch will do this sort of thing automagically,
 * but in code you need to register a callback, and then link the pad in that callback
 ********************************************************************************************************************************/
static void Pad_Callback(GstElement* element, GstPad* pad, gpointer data)
{
    gchar* name;
    GstCaps* caps;
    gchar* description;
    GstElement* video_convert;

    name = gst_pad_get_name(pad);
    //video_sub->logger.Info(std::string("A new pad was created"));

    caps = gst_pad_get_pad_template_caps(pad);
    description = gst_caps_to_string(caps);
    g_free(description);

    video_convert = GST_ELEMENT(data);

    if (!gst_element_link_pads(element, name, video_convert, "sink")) {
        //video_sub->logger.Error("Failed to link decodebin and autoconvert");
    }

    g_free(name);
}

// This callback gets called whenever data reaches the sink of the pipeline
// The video shared data is updated accordingly
static GstFlowReturn Update_Shared_Video_Data(GstElement* sink, VideoSub* video_sub)
{
    GstSample* sample;
    g_signal_emit_by_name(sink, "pull-sample", &sample);
    if (sample) {
        GstBuffer* buffer = gst_sample_get_buffer(sample);
        if (!buffer) {
            video_sub->logger.Error("gst_sample_get_buffer() returned NULL");
            return GST_FLOW_ERROR;
        }
        GstMapInfo map;
        if (!gst_buffer_map(buffer, &map, GST_MAP_READ)) {
            video_sub->logger.Error("gst_buffer_map() failed");
            return GST_FLOW_ERROR;
        }
        if (!map.data) {
            video_sub->logger.Error("gst_buffer had NULL data pointer");
            return GST_FLOW_ERROR;
        }

       // Write the received video data into the shared memory
       std::scoped_lock<std::mutex> lock(video_sub->video_mutex); {
           memcpy(video_sub->shared_data->video.frame, map.data, map.size);
           gst_buffer_unmap(buffer, &map);
           gst_sample_unref(sample);
       }
    }
    return GST_FLOW_OK;
}

VideoSub::VideoSub() {
    name="VideoSub";
    logger.Set_Name(name);
}

int VideoSub::Init()
{
    logger.Info("Video Sub Initializing...");

    if (Construct_Pipeline() != 0) return -1;
    if (Set_Pipeline_State_Playing() != 0) return -1;

    return 0;
}

int VideoSub::Cycle_Step()
{
    return 0;
}

int VideoSub::Deinit()
{
    logger.Info("Deinitializing...");
    return Destroy_Pipeline();
}

int VideoSub::Construct_Pipeline()
{
    m_pipeline = new VideoPipeline_t();

    gst_init(NULL, NULL);

    if (Create_Elements() != 0) return -1;
    if (Configure_Elements() != 0) return -1;
    if (Link_Elements() != 0) return -1;

    logger.Info("Video Pipeline successfully constructed");
    return 0;
}

int VideoSub::Create_Elements()
{
    m_pipeline->pipe = gst_pipeline_new("Subscriber Video Pipeline");
    m_pipeline->udpsrc = gst_element_factory_make("udpsrc", NULL);
    m_pipeline->filter = gst_element_factory_make("capsfilter", NULL);
    m_pipeline->rtph264depay = gst_element_factory_make("rtph264depay", NULL);
    m_pipeline->decodebin = gst_element_factory_make("decodebin", NULL);
    m_pipeline->videoconvert = gst_element_factory_make("videoconvert", NULL);
    m_pipeline->convert_filter = gst_element_factory_make("capsfilter", NULL);
    m_pipeline->queue = gst_element_factory_make("queue", NULL);
    m_pipeline->videosink = gst_element_factory_make("appsink", NULL);

    if (!m_pipeline->pipe ||
        !m_pipeline->udpsrc ||
        !m_pipeline->filter ||
        !m_pipeline->rtph264depay ||
        !m_pipeline->decodebin ||
        !m_pipeline->videoconvert ||
        !m_pipeline->convert_filter ||
        !m_pipeline->queue ||
        !m_pipeline->videosink) {
        logger.Error("Failed to create all pipeline elements");

        delete m_pipeline;
        return -1;
    }

    //Add elements to the Pipeline
    gst_bin_add_many(GST_BIN(m_pipeline->pipe),
                     m_pipeline->udpsrc,
                     m_pipeline->filter,
                     m_pipeline->rtph264depay,
                     m_pipeline->decodebin,
                     m_pipeline->videoconvert,
                     m_pipeline->convert_filter,
                     m_pipeline->queue,
                     m_pipeline->videosink, NULL);

    return 0;
}

int VideoSub::Configure_Elements()
{
    GstCaps* caps = gst_caps_new_simple("application/x-rtp",
        "media", G_TYPE_STRING, "video",
        "clock-rate", G_TYPE_INT, 90000,
        "encoding-name", G_TYPE_STRING, "H264",
        "payload", G_TYPE_INT, 96, NULL);

    GstCaps* convert_caps = gst_caps_new_simple("video/x-raw",
            "format", G_TYPE_STRING, "RGB", NULL);

    g_object_set(G_OBJECT(m_pipeline->udpsrc), "port", std::stoi(parameters.at("IN_PORT")), NULL);
    g_object_set(G_OBJECT(m_pipeline->filter), "caps", caps, NULL);
    g_object_set(G_OBJECT(m_pipeline->convert_filter), "caps", convert_caps, NULL);
    gst_caps_unref(caps);
    gst_caps_unref(convert_caps);


    //Register Callbacks
    g_signal_connect(m_pipeline->decodebin, "pad-added", G_CALLBACK(Pad_Callback), m_pipeline->videoconvert);
    GstBus* bus = gst_pipeline_get_bus(GST_PIPELINE(m_pipeline->pipe));

    gst_bus_add_signal_watch(bus);
    g_signal_connect(bus, "message", (GCallback)Bus_Message_Callback, m_pipeline->pipe);

    //g_signal_connect(pipeline->videosink, "pull-sample", (GCallback)Update_Shared_Video_Data, this);
    g_object_set(G_OBJECT(m_pipeline->videosink), "emit-signals", TRUE, "sync", FALSE, NULL);
    g_signal_connect(m_pipeline->videosink, "new-sample", G_CALLBACK(Update_Shared_Video_Data), this);

    return 0;
}

int VideoSub::Link_Elements()
{
    //Link udpsrc through to decode bin
    if (!gst_element_link_many(
            m_pipeline->udpsrc,
            m_pipeline->filter,
            m_pipeline->rtph264depay,
            m_pipeline->decodebin, NULL)) {
        logger.Error("Failed to link first branch of pipeline elements");

        delete m_pipeline;
        return -1;
    }

    //Decode bin and videoconvert are linked by the Pad Callback
    //Link videoconvert through to videosink
    if (!gst_element_link_many(
            m_pipeline->videoconvert,
            m_pipeline->convert_filter,
            m_pipeline->queue,
            m_pipeline->videosink, NULL)) {
        logger.Error("Failed to link second branch of pipeline elements");

        delete m_pipeline;
        return -1;
    }

    return 0;
}

int VideoSub::Destroy_Pipeline()
{
    GstStateChangeReturn ret = gst_element_set_state(m_pipeline->pipe, GST_STATE_NULL);
    if (ret == GST_STATE_CHANGE_FAILURE) {
        logger.Error("Failed to destroy the video pipeline");
        delete m_pipeline;
        return -1;
    }

    logger.Info("Subscriber video pipeline destroyed");
    delete m_pipeline;
    return 0;
}

int VideoSub::Set_Pipeline_State_Playing()
{
    //Set State to playing
    GstStateChangeReturn ret = gst_element_set_state(m_pipeline->pipe, GST_STATE_PLAYING);
    if (ret == GST_STATE_CHANGE_FAILURE) {
        logger.Error("Unable to set the pipeline to the playing m_state");

        delete m_pipeline;
        return -1;
    }

    logger.Info("Video pipeline set to playing");
    return 0;
}

// Factory Method
std::shared_ptr<Module> Create_Instance()
{
    return std::make_shared<VideoSub>();
}