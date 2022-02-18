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

    int Send(const std::string topic, std::string data);
    int Receive();

    int Serialized_Servos(std::string& output_string);

    zmq::context_t zmq_context;
    zmq::socket_t publisher;
    std::unordered_map<std::string, zmq::socket_t> subscribers;

    std::string input_endpoint = "tcp://";
    std::string output_endpoint = "tcp://0.0.0.0:";
};