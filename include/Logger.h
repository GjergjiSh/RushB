#ifndef LOGGER_H
#define LOGGER_H

#define VERB true
#define NO_VERB false

#include <iostream>
#include <sstream>
#include <chrono>
#include <ctime>
#include <iomanip>

namespace RBLogger {

#define LOG_PREFIX msg_stream << m_name << TAG_END << " "

static const std::string TAG_END = "]\033[0m";
static const std::string ERROR = "\033[1;31m[E][";
static const std::string INFO = "\033[1;32m[I][";
static const std::string WARNING = "\033[1;33m[W][";

class Logger {

public:
    Logger() = default;
    ~Logger() = default;

    void Set_Name(std::string name);

    void Info(std::string msg);
    void Time_Info(std::string msg, int time);
    void Warning(std::string msg);
    void Error_Description(std::string msg, std::string err);
    void Error(std::string msg);

    std::string Time_Stamp();

private:
    std::string m_name;
    void Log(std::string tag, std::stringstream& msg);
};
}

#endif /* LOGGER_H */