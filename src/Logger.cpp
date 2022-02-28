#include "Logger.h"

void RBLogger::Logger::Info(std::string msg)
{
    std::stringstream msg_stream;
    LOG_PREFIX << msg;

    Log(RBLogger::INFO, msg_stream);
}

void RBLogger::Logger::Time_Info(std::string msg, int time)
{
    std::stringstream msg_stream;
    LOG_PREFIX << msg << " " << time << " [ms]";

    Log(RBLogger::INFO, msg_stream);
}

void RBLogger::Logger::Warning(std::string msg)
{
    std::stringstream msg_stream;
    LOG_PREFIX << msg;

    Log(RBLogger::WARNING, msg_stream);
}

void RBLogger::Logger::Error_Description(std::string msg, std::string err)
{
    std::stringstream msg_stream;
    LOG_PREFIX << msg << " " << err;

    Log(RBLogger::ERROR, msg_stream);
}

void RBLogger::Logger::Error(std::string msg)
{
    std::stringstream msg_stream;
    LOG_PREFIX << msg;

    Log(RBLogger::ERROR, msg_stream);
}

void RBLogger::Logger::Set_Name(std::string name)
{
    m_name = name;
}

std::string RBLogger::Logger::Time_Stamp()
{
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

void RBLogger::Logger::Log(std::string tag, std::stringstream& msg)
{
    std::cout << "[" << Time_Stamp() << "] "
              << tag << msg.str() << std::endl;
}
