#include "ModuleInterface.h"
#include "ProtoModuleInterface.pb.h"
#include <zmq.hpp>

#define LOG_INFO(msg) \
    std::cout << "[I][ZmqPipeline] " << msg << std::endl;
#define LOG_TIME_INFO(msg, time) \
    std::cerr << "[I][ZmqPipeline] " << msg << " [" << time << " ms]" << std::endl;
#define LOG_WARNING(msg) \
    std::cerr << "[W][ZmqPipeline] " << msg << std::endl;
#define LOG_ERROR_DESCRIPTION(msg, err) \
    std::cerr << "[E][ZmqPipeline] " << msg << " " << err << std::endl;
#define LOG_ERROR(msg) \
    std::cerr << "[E][ZmqPipeline] " << msg << std::endl;



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

    zmq::context_t zmq_context;
    zmq::socket_t publisher;
    std::unordered_map<std::string, zmq::socket_t> subscribers;

    std::vector<std::string> publisher_topics;
    std::vector<std::string> subscriber_topics;

    std::string input_endpoint = "tcp://";
    std::string output_endpoint = "tcp://0.0.0.0:";

    std::unordered_map<std::string, int (ZmqPipeline::*)(std::string&)> publisher_funcs;
    std::unordered_map<std::string, int (ZmqPipeline::*)()> subscriber_funcs;

};