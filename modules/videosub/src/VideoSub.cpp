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
    //video_sub->logger.LOG_INFO(std::string("A new pad was created"));

    caps = gst_pad_get_pad_template_caps(pad);
    description = gst_caps_to_string(caps);
    g_free(description);

    video_convert = GST_ELEMENT(data);

    if (!gst_element_link_pads(element, name, video_convert, "sink")) {
        //video_sub->logger.LOG_ERROR("Failed to link decidebin and autoconvert");
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
            video_sub->logger.LOG_ERROR("gst_sample_get_buffer() returned NULL");
            return GST_FLOW_ERROR;
        }
        GstMapInfo map;
        if (!gst_buffer_map(buffer, &map, GST_MAP_READ)) {
            video_sub->logger.LOG_ERROR("gst_buffer_map() failed");
            return GST_FLOW_ERROR;
        }
        if (!map.data) {
            video_sub->logger.LOG_ERROR("gst_buffer had NULL data pointer");
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
    logger.LOG_INFO("Video Sub Initializing...");

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
    logger.LOG_INFO("Deinitializing...");
    return Destroy_Pipeline();
}

int VideoSub::Construct_Pipeline()
{
    pipeline = new VideoPipeline_t();

    gst_init(NULL, NULL);

    if (Create_Elements() != 0) return -1;
    if (Configure_Elements() != 0) return -1;
    if (Link_Elements() != 0) return -1;

    logger.LOG_INFO("Video Pipeline successfuly constructed");
    return 0;
}

int VideoSub::Create_Elements()
{
    pipeline->pipe = gst_pipeline_new("Subscriber Video Pipeline");
    pipeline->udpsrc = gst_element_factory_make("udpsrc", NULL);
    pipeline->filter = gst_element_factory_make("capsfilter", NULL);
    pipeline->rtph264depay = gst_element_factory_make("rtph264depay", NULL);
    pipeline->decodebin = gst_element_factory_make("decodebin", NULL);
    pipeline->videoconvert = gst_element_factory_make("videoconvert", NULL);
    pipeline->convert_filter = gst_element_factory_make("capsfilter", NULL);
    pipeline->queue = gst_element_factory_make("queue", NULL);
    pipeline->videosink = gst_element_factory_make("appsink", NULL);

    if (!pipeline->pipe ||
        !pipeline->udpsrc ||
        !pipeline->filter ||
        !pipeline->rtph264depay ||
        !pipeline->decodebin ||
        !pipeline->videoconvert ||
        !pipeline->convert_filter ||
        !pipeline->queue ||
        !pipeline->videosink) {
        logger.LOG_ERROR("Failed to create all pipeline elements");

        delete pipeline;
        return -1;
    }

    //Add elements to the Pipeline
    gst_bin_add_many(GST_BIN(pipeline->pipe),
        pipeline->udpsrc,
        pipeline->filter,
        pipeline->rtph264depay,
        pipeline->decodebin,
        pipeline->videoconvert,
        pipeline->convert_filter,
        pipeline->queue,
        pipeline->videosink, NULL);

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

    g_object_set(G_OBJECT(pipeline->udpsrc), "port", std::stoi(parameters.at("IN_PORT")), NULL);
    g_object_set(G_OBJECT(pipeline->filter), "caps", caps, NULL);
    g_object_set(G_OBJECT(pipeline->convert_filter), "caps", convert_caps, NULL);
    gst_caps_unref(caps);
    gst_caps_unref(convert_caps);


    //Register Callbacks
    g_signal_connect(pipeline->decodebin, "pad-added", G_CALLBACK(Pad_Callback), pipeline->videoconvert);
    GstBus* bus = gst_pipeline_get_bus(GST_PIPELINE(pipeline->pipe));

    gst_bus_add_signal_watch(bus);
    g_signal_connect(bus, "message", (GCallback)Bus_Message_Callback, pipeline->pipe);

    //g_signal_connect(pipeline->videosink, "pull-sample", (GCallback)Update_Shared_Video_Data, this);
    g_object_set(G_OBJECT(pipeline->videosink), "emit-signals", TRUE, "sync", FALSE, NULL);
    g_signal_connect(pipeline->videosink, "new-sample", G_CALLBACK(Update_Shared_Video_Data), this);

    return 0;
}

int VideoSub::Link_Elements()
{
    //Link udpsrc through to decode bin
    if (!gst_element_link_many(
            pipeline->udpsrc,
            pipeline->filter,
            pipeline->rtph264depay,
            pipeline->decodebin, NULL)) {
        logger.LOG_ERROR("Failed to link first branch of pipeline elements");

        delete pipeline;
        return -1;
    }

    //Decode bin and videoconvert are linked by the Pad Callback
    //Link videoconvert through to videosink
    if (!gst_element_link_many(
            pipeline->videoconvert,
            pipeline->convert_filter,
            pipeline->queue,
            pipeline->videosink, NULL)) {
        logger.LOG_ERROR("Failed to link second branch of pipeline elements");

        delete pipeline;
        return -1;
    }

    return 0;
}

int VideoSub::Destroy_Pipeline()
{
    GstStateChangeReturn ret = gst_element_set_state(pipeline->pipe, GST_STATE_NULL);
    if (ret == GST_STATE_CHANGE_FAILURE) {
        logger.LOG_ERROR("Failed to destroy the video pipeline");
        delete pipeline;
        return -1;
    }

    logger.LOG_INFO("Subscriber video pipeline destroyed");
    delete pipeline;
    return 0;
}

int VideoSub::Set_Pipeline_State_Playing()
{
    //Set State to playing
    GstStateChangeReturn ret = gst_element_set_state(pipeline->pipe, GST_STATE_PLAYING);
    if (ret == GST_STATE_CHANGE_FAILURE) {
        logger.LOG_ERROR("Unable to set the pipeline to the playing state");

        delete pipeline;
        return -1;
    }

    logger.LOG_INFO("Video pipeline set to playing");
    return 0;
}

// Factory Method
std::shared_ptr<Module> Create_Instance()
{
    return std::make_shared<VideoSub>();
}