#include "ZmqPipeline.h"

// #TODO redundant methods
ZmqPipeline::ZmqPipeline()
{
    name = "ZmqPipeline";
    logger.Set_Name(name);

    m_publisher_funcs = {
        std::make_pair("USS", &ZmqPipeline::Publish_Uss),
        std::make_pair("SERVOS", &ZmqPipeline::Publish_Servos),
    };

    m_subscriber_funcs = {
        std::make_pair("USS", &ZmqPipeline::Update_Uss),
        std::make_pair("SERVOS", &ZmqPipeline::Update_Servos),
    };
}

int ZmqPipeline::Init()
{
    return Init_Connection();
}

int ZmqPipeline::Cycle_Step()
{
    // Publish all pub topics and their data
    for (auto topic : m_publisher_topics) {
        if ((this->*m_publisher_funcs.at(topic))(topic) != 0)
            return -1;
    }

    // Read all sub topics and update shared data
    for (auto topic : m_subscriber_topics) {
        if ((this->*m_subscriber_funcs.at(topic))() != 0)
            return -1;
    }

    return 0;
}

int ZmqPipeline::Deinit()
{
    return Deinit_Connection();
}

int ZmqPipeline::Construct_Sockets()
{
    // Create the publisher socket
    m_publisher = zmq::socket_t(m_zmq_context, zmq::socket_type::pub);

    try { // Create the subscriber sockets and register the pub/sub topics
        for (const auto &parameter: parameters) {
            if (parameter.first == "SUB_TOPIC") {
                m_subscribers.emplace(std::make_pair(parameter.second,
                                                     zmq::socket_t(m_zmq_context,
                                                                   zmq::socket_type::sub)));

                m_subscriber_topics.push_back(parameter.second);
            } else if (parameter.first == "PUB_TOPIC") {
                m_publisher_topics.push_back(parameter.second);
            }
        }
    } catch (zmq::error_t& e) {
        logger.Error_Description("Failed to construct the m_subscribers: ", e.what());
        return -1;
    }

    return 0;
}

int ZmqPipeline::Configure_Sockets()
{
    try { // Configure the m_publisher socket
        m_publisher.setsockopt(ZMQ_LINGER, 0);
        m_publisher.bind(m_output_endpoint);
    } catch (zmq::error_t& e) {
        logger.Error_Description("Failed to configure the m_publisher: ", e.what());
        return -1;
    }

    try { // Configure the subscriber sockets and assing their topics
        for (auto& [topic, socket] : m_subscribers) {
            socket.setsockopt(ZMQ_SUBSCRIBE, topic.c_str(), topic.size());
            socket.setsockopt(ZMQ_LINGER, 0);
            socket.connect(m_input_endpoint);
        }
    } catch (zmq::error_t& e) {
        logger.Error_Description("Failed to configure the m_subscribers: ", e.what());
        return -1;
    }

    return 0;
}

int ZmqPipeline::Init_Connection()
{
    try { // Initialize the zmq context
        m_zmq_context = zmq::context_t(1);
    } catch (zmq::error_t& e) {
        logger.Error_Description("Failed to initialize the zmq context: ", e.what());
        return -1;
    }

    if (Init_Endpoints() != 0) return -1;
    if (Construct_Sockets() != 0) return -1;
    if (Configure_Sockets() != 0) return -1;

    return 0;
}

int ZmqPipeline::Init_Endpoints()
{
    try { // Create the zmq endpoint strings
        m_input_endpoint.append(parameters.at("REMOTE"));
        m_input_endpoint.append(":");
        m_input_endpoint.append(parameters.at("IN_PORT"));
        m_output_endpoint.append(parameters.at("OUT_PORT"));
    } catch (std::exception& e) {
        logger.Error_Description("Failed to initialize the endpoints", e.what());
        return -1;
    }

    return 0;
}

int ZmqPipeline::Deinit_Connection()
{
    try { // Close the m_publisher socket
        m_publisher.close();
    } catch (zmq::error_t& e) {
        logger.Error_Description("Failed to close the m_publisher: ", e.what());
        return -1;
    }

    try { // Close the subscriber sockets
        for (auto& [topic, socket] : m_subscribers) {
            socket.close();
        }
    } catch (zmq::error_t& e) {
        logger.Error_Description("Failed to close the m_subscribers: ", e.what());
        return -1;
    }

    try { // Close the zmq context
        m_zmq_context.close();
    } catch (zmq::error_t& e) {
        logger.Error_Description("Failed to close the zmq context: ", e.what());
        return -1;
    }

    return 0;
}


int ZmqPipeline::Send(const std::string& topic, std::string& data)
{
    try { // Init message and topic from parameter size
        zmq::message_t zmq_topic(topic.length());
        zmq::message_t zmq_message(data.length());

        // Construct message and topic from parameter data
        memcpy(zmq_topic.data(), topic.data(), topic.length());
        memcpy(zmq_message.data(), data.data(), data.length());

        // Send message and topic
        m_publisher.send(zmq_topic, zmq::send_flags::sndmore);
        m_publisher.send(zmq_message, zmq::send_flags::dontwait);

        // Rebuild message and topic from parameter size
        zmq_topic.rebuild(topic.size());
        zmq_message.rebuild(data.length());
    } catch (zmq::error_t& e) {
        logger.Error_Description("Failed to send data" + topic, e.what());
        return -1;
    }

    return 0;
}

int ZmqPipeline::Recv(const std::string& topic, std::string& data)
{
    zmq::message_t zmq_topic;
    zmq::message_t zmq_msg;

    zmq::pollitem_t poll_item = {m_subscribers.at(topic), 0, ZMQ_POLLIN, 0 };
    try {
        zmq::poll(&poll_item, 1, 0);

        if (poll_item.revents & ZMQ_POLLIN) {

            int recv = m_subscribers.at(topic).recv(&zmq_topic, ZMQ_RCVMORE);
            recv = m_subscribers.at(topic).recv(&zmq_msg) && recv;

            data.assign(static_cast<char*>(zmq_msg.data()), zmq_msg.size());

            if (recv < 0)
                logger.Warning("Failed to receive data!");
        }
    } catch (zmq::error_t& e) {
        logger.Error_Description("Failed to poll sockets", e.what());
        return -1;
    }

    return 0;
}

int ZmqPipeline::Serialize_Servos(std::string& output_string)
{
    ServoValues_Proto proto_servos;
    proto_servos.set_top_servo(shared_data->servos.top_servo);
    proto_servos.set_right_servo(shared_data->servos.right_servo);
    proto_servos.set_left_servo(shared_data->servos.left_servo);
    if (!proto_servos.SerializeToString(&output_string)) {
        logger.Error("Failed to serialize servo values");
        return -1;
    }

    return 0;
}

int ZmqPipeline::Serialize_Uss(std::string& output_string)
{
    UltraSonicValues_Proto proto_uss;
    proto_uss.set_distance(shared_data->uss.distance);
    if (!proto_uss.SerializeToString(&output_string)) {
        logger.Error("Failed to serialize servo values");
        return -1;
    }
    return 0;
}


int ZmqPipeline::Deserialize_Uss(std::string& input_string, UltraSonicValues_Proto& uss)
{
    if (Recv("USS", input_string) != 0)
        return -1;

    if (!uss.ParseFromString(input_string)) {
        logger.Error("Failed to deserialize ultra sonic values");
        return -1;
    }

    return 0;
}

int ZmqPipeline::Deserialize_Servos(std::string& input_string, ServoValues_Proto& servos)
{
    if (Recv("SERVOS", input_string) != 0)
        return -1;

    if (!servos.ParseFromString(input_string)) {
        logger.Error("Failed to deserialize servo values");
        return -1;
    }

    return 0;
}

int ZmqPipeline::Publish_Servos(std::string& servos)
{
    if (Serialize_Servos(servos) != 0) return -1;
    if (Send("SERVOS", servos) != 0) return -1;

    return 0;
}

int ZmqPipeline::Publish_Uss(std::string& uss)
{
    if (Serialize_Uss(uss) != 0) return -1;
    if (Send("USS", uss) != 0) return -1;

    return 0;
}

int ZmqPipeline::Update_Uss()
{
    std::string serialized_uss;
    UltraSonicValues_Proto uss;

    if (Recv("USS", serialized_uss) == -1) return -1;
    if (Deserialize_Uss(serialized_uss, uss) != 0) return -1;

    shared_data->uss.distance = uss.distance();

    return 0;
}

int ZmqPipeline::Update_Servos()
{
    std::string serialzed_servos;
    ServoValues_Proto servos;

    if (Recv("SERVOS", serialzed_servos) == -1) return -1;
    if (Deserialize_Servos(serialzed_servos, servos) != 0) return -1;

    shared_data->servos.left_servo = servos.left_servo();
    shared_data->servos.right_servo = servos.right_servo();
    shared_data->servos.top_servo = servos.top_servo();

    return 0;
}

// Factory Methods
Module *Create_Instance() {
    return new ZmqPipeline;
}

void Destroy_Instance(Module *module) {
    delete module;
}