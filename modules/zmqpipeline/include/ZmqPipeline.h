#include <zmq.hpp>

#include "IModuleInterface.h"
#include "ProtoModuleInterface.pb.h"

class ZmqPipeline : public Module {
public:
    ZmqPipeline();
    int Init(void) override;
    int Cycle_Step(void) override;
    int Deinit(void) override;

private:
    int Init_Connection();
    int Init_Endpoints();
    int Construct_Sockets();
    int Configure_Sockets();
    int Deinit_Connection();

    int Send(const std::string& topic, std::string& data);
    int Recv(const std::string& topic, std::string&data);

    int Serialize_Servos(std::string& output_string);
    int Serialize_Uss(std::string& output_string);

    int Deserialize_Uss(std::string& input_string, UltraSonicValues_Proto& uss);
    int Deserialize_Servos(std::string& input_string, ServoValues_Proto& servos);

    int Publish_Servos(std::string& serovs);
    int Publish_Uss(std::string& uss);

    int Update_Servos();
    int Update_Uss();

    zmq::context_t m_zmq_context;
    zmq::socket_t m_publisher;
    std::unordered_map<std::string, zmq::socket_t> m_subscribers;

    std::vector<std::string> m_publisher_topics;
    std::vector<std::string> m_subscriber_topics;

    std::string m_input_endpoint = "tcp://";
    std::string m_output_endpoint = "tcp://0.0.0.0:";

    std::unordered_map<std::string, int (ZmqPipeline::*)(std::string&)> m_publisher_funcs;
    std::unordered_map<std::string, int (ZmqPipeline::*)()> m_subscriber_funcs;
};