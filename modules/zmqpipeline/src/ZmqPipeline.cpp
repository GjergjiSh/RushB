#include "ZmqPipeline.h"

ZmqPipeline::ZmqPipeline()
{
    name = "ZmqPipeline";
    logger.Set_Name(name);

    publisher_funcs = {
        std::make_pair("USS", &ZmqPipeline::Publish_Uss),
        std::make_pair("SERVOS", &ZmqPipeline::Publish_Servos),
    };

    subscriber_funcs = {
        std::make_pair("USS", &ZmqPipeline::Update_Uss),
        std::make_pair("SERVOS", &ZmqPipeline::Update_Servos),
    };
}

int ZmqPipeline::Init()
{
    logger.LOG_INFO("Initializing...");
    return Init_Connection();
}

int ZmqPipeline::Cycle_Step()
{
    // Publish all pub topics and their data
    for (auto topic : publisher_topics) {
        if ((this->*publisher_funcs.at(topic))(topic) != 0)
            return -1;
    }

    // Read all sub topics and update shared data
    for (auto topic : subscriber_topics) {
        if ((this->*subscriber_funcs.at(topic))() != 0)
            return -1;
    }

    return 0;
}

int ZmqPipeline::Deinit()
{
    logger.LOG_INFO("Deinitializing...");
    return Deinit_Connection();
}

int ZmqPipeline::Construct_Sockets()
{
    try { // Create the publisher socket
        publisher = zmq::socket_t(zmq_context, zmq::socket_type::pub);
    } catch (zmq::error_t& e) {
        logger.LOG_ERROR_DESCRIPTION("Failed to construct the publisher: ", e.what());
        return -1;
    }

    try { // Create the subscriber sockets and register the pub/sub topics
        for (auto parameter : parameters) {
            if (parameter.first == "SUB_TOPIC") {
                subscribers.emplace(std::make_pair(parameter.second,
                    zmq::socket_t(zmq_context, zmq::socket_type::sub)));
                subscriber_topics.push_back(parameter.second);
            } else if (parameter.first == "PUB_TOPIC") {
                publisher_topics.push_back(parameter.second);
            }
        }
    } catch (zmq::error_t& e) {
        logger.LOG_ERROR_DESCRIPTION("Failed to construct the subscribers: ", e.what());
        return -1;
    }

    return 0;
}

int ZmqPipeline::Configure_Sockets()
{
    try { // Configure the publisher socket
        publisher.setsockopt(ZMQ_LINGER, 0);
        publisher.bind(output_endpoint);
    } catch (zmq::error_t& e) {
        logger.LOG_ERROR_DESCRIPTION("Failed to configure the publisher: ", e.what());
        return -1;
    }

    try { // Configure the subscriber sockets and assing their topics
        for (auto& [topic, socket] : subscribers) {
            socket.setsockopt(ZMQ_SUBSCRIBE, topic.c_str(), topic.size());
            socket.setsockopt(ZMQ_LINGER, 0);
            socket.connect(input_endpoint);
        }
    } catch (zmq::error_t& e) {
        logger.LOG_ERROR_DESCRIPTION("Failed to configure the subscribers: ", e.what());
        return -1;
    }

    return 0;
}

int ZmqPipeline::Init_Connection()
{
    try { // Initialize the zmq context
        zmq_context = zmq::context_t(1);
    } catch (zmq::error_t& e) {
        logger.LOG_ERROR_DESCRIPTION("Failed to initialize the zmq context: ", e.what());
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
        input_endpoint.append(parameters.at("REMOTE"));
        input_endpoint.append(":");
        input_endpoint.append(parameters.at("IN_PORT"));
        output_endpoint.append(parameters.at("OUT_PORT"));
    } catch (std::exception& e) {
        logger.LOG_ERROR_DESCRIPTION("Failed to initialize the endpoints", e.what());
        return -1;
    }

    return 0;
}

int ZmqPipeline::Deinit_Connection()
{
    try { // Close the publisher socket
        publisher.close();
    } catch (zmq::error_t& e) {
        logger.LOG_ERROR_DESCRIPTION("Failed to close the publisher: ", e.what());
        return -1;
    }

    try { // Close the subscriber sockets
        for (auto& [topic, socket] : subscribers) {
            socket.close();
        }
    } catch (zmq::error_t& e) {
        logger.LOG_ERROR_DESCRIPTION("Failed to close the subscribers: ", e.what());
        return -1;
    }

    try { // Close the zmq context
        zmq_context.close();
    } catch (zmq::error_t& e) {
        logger.LOG_ERROR_DESCRIPTION("Failed to close the zmq context: ", e.what());
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
        publisher.send(zmq_topic, zmq::send_flags::sndmore);
        publisher.send(zmq_message, zmq::send_flags::dontwait);

        // Rebuild message and topic from parameter size
        zmq_topic.rebuild(topic.size());
        zmq_message.rebuild(data.length());
    } catch (zmq::error_t& e) {
        logger.LOG_ERROR_DESCRIPTION("Failed to send data" + topic, e.what());
        return -1;
    }

    return 0;
}

int ZmqPipeline::Recv(const std::string& topic, std::string& data)
{
    int recv = 0;
    zmq::message_t zmq_topic;
    zmq::message_t zmq_msg;

    zmq::pollitem_t poll_item = { subscribers.at(topic), 0, ZMQ_POLLIN, 0 };
    try {
        zmq::poll(&poll_item, 1, 0);

        if (poll_item.revents & ZMQ_POLLIN) {

            recv = subscribers.at(topic).recv(&zmq_topic, ZMQ_RCVMORE);
            recv = subscribers.at(topic).recv(&zmq_msg) && recv;

            data.assign(static_cast<char*>(zmq_msg.data()), zmq_msg.size());

            if (recv < 0)
                logger.LOG_WARNING("Failed to receive data!");
        }
    } catch (zmq::error_t& e) {
        logger.LOG_ERROR_DESCRIPTION("Failed to poll sockets", e.what());
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
        logger.LOG_ERROR("Failed to serialize servo values");
        return -1;
    }

    return 0;
}

int ZmqPipeline::Serialize_Uss(std::string& output_string)
{
    UltraSonicValues_Proto proto_uss;
    proto_uss.set_distance(shared_data->uss.distance);
    if (!proto_uss.SerializeToString(&output_string)) {
        logger.LOG_ERROR("Failed to serialize servo values");
        return -1;
    }
    return 0;
}


int ZmqPipeline::Deserialize_Uss(std::string& input_string, UltraSonicValues_Proto& uss)
{
    if (Recv("USS", input_string) != 0)
        return -1;

    if (!uss.ParseFromString(input_string)) {
        logger.LOG_ERROR("Failed to deserialize ultra sonic values");
        return -1;
    }

    return 0;
}

int ZmqPipeline::Deserialize_Servos(std::string& input_string, ServoValues_Proto& servos)
{
    if (Recv("SERVOS", input_string) != 0)
        return -1;

    if (!servos.ParseFromString(input_string)) {
        logger.LOG_ERROR("Failed to deserialize servo values");
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

extern "C" Module* Create() { return new ZmqPipeline; }
extern "C" void Destroy(Module* module) { delete module; }