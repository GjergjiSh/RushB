#include "Logger.h"

#include <utility>

void RBLogger::Logger::Info(const std::string &msg) {
    std::stringstream msg_stream;
    LOG_PREFIX << msg;

    Log(RBLogger::INFO, msg_stream);
}

void RBLogger::Logger::Time_Info(const std::string &msg, int time) {
    std::stringstream msg_stream;
    LOG_PREFIX << msg << " " << time << " [ms]";

    Log(RBLogger::INFO, msg_stream);
}

void RBLogger::Logger::Warning(const std::string &msg) {
    std::stringstream msg_stream;
    LOG_PREFIX << msg;

    Log(RBLogger::WARNING, msg_stream);
}

void RBLogger::Logger::Error_Description(const std::string &msg, const std::string &err) {
    std::stringstream msg_stream;
    LOG_PREFIX << msg << " " << err;

    Log(RBLogger::ERROR, msg_stream);
}

void RBLogger::Logger::Error(const std::string &msg) {
    std::stringstream msg_stream;
    LOG_PREFIX << msg;

    Log(RBLogger::ERROR, msg_stream);
}

void RBLogger::Logger::Set_Name(std::string name) {
    m_name = std::move(name);
}

void RBLogger::Logger::Debug(const std::string &msg) {
    std::stringstream msg_stream;
    LOG_PREFIX << msg;

    Log(RBLogger::DEBUG, msg_stream);
}

std::string RBLogger::Logger::Time_Stamp() {
    // get a precise timestamp as a string
    const auto now = std::chrono::system_clock::now();
    const auto now_as_time_t = std::chrono::system_clock::to_time_t(now);
    const auto now_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            now.time_since_epoch()) % 1000;

    // Format the timestamp
    std::stringstream timestamp;
    timestamp << std::put_time(std::localtime(&now_as_time_t), "%T")
              << '.'
              << std::setfill('0')
              << std::setw(3)
              << now_ms.count();

    return timestamp.str();
}

void RBLogger::Logger::Log(const std::string &tag, std::stringstream &msg) {
    std::cout << "[" << Time_Stamp() << "] "
              << tag << msg.str() << std::endl;
}
