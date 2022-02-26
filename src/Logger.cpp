#include "Logger.h"

void Logger::LOG_INFO(std::string msg)
{
    std::stringstream msg_stream;
    msg_stream << name << TAG_END << " " << msg;
    PRINT(INFO);
}
void Logger::LOG_TIME_INFO(std::string msg, int time)
{
    std::stringstream msg_stream;
    msg_stream << name << TAG_END << " " << msg << time << " [ms]";
    PRINT(INFO);
}
void Logger::LOG_WARNING(std::string msg)
{
    std::stringstream msg_stream;
    msg_stream << name << TAG_END << " " << msg;
    PRINT(WARNING);
}
void Logger::LOG_ERROR_DESCRIPTION(std::string msg, std::string err)
{
    std::stringstream msg_stream;
    msg_stream << name << TAG_END << " " << msg << err;
    PRINT(ERROR);
}
void Logger::LOG_ERROR(std::string msg)
{
    std::stringstream msg_stream;
    msg_stream << name << TAG_END << " " << msg;
    PRINT(ERROR);
}

void Logger::Set_Name(std::string name)
{
    this->name = name;
}

std::string Logger::Time_Stamp()
{
    std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::string str(30, '\0');
    std::strftime(&str[0], str.size(), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    return str;
}