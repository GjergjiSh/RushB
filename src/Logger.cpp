#include "Logger.h"


void RBLogger::Logger::LOG_INFO(std::string msg)
{
    std::stringstream msg_stream;
    msg_stream << name << TAG_END << " " << msg;
    PRINT(RBLogger::INFO);
}
void RBLogger::Logger::LOG_TIME_INFO(std::string msg, int time)
{
    std::stringstream msg_stream;
    msg_stream << name << TAG_END << " " << msg << time << " [ms]";
    PRINT(RBLogger::INFO);
}
void RBLogger::Logger::LOG_WARNING(std::string msg)
{
    std::stringstream msg_stream;
    msg_stream << name << TAG_END << " " << msg;
    PRINT(RBLogger::WARNING);
}
void RBLogger::Logger::LOG_ERROR_DESCRIPTION(std::string msg, std::string err)
{
    std::stringstream msg_stream;
    msg_stream << name << TAG_END << " " << msg << " " << err;
    PRINT(RBLogger::ERROR);
}
void RBLogger::Logger::LOG_ERROR(std::string msg)
{
    std::stringstream msg_stream;
    msg_stream << name << TAG_END << " " << msg;
    PRINT(RBLogger::ERROR);
}

void RBLogger::Logger::Set_Name(std::string name)
{
    this->name = name;
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