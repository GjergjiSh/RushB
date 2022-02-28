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

#define PRINT(tag) std::cout << "["              \
                             << Time_Stamp()     \
                             << "] "             \
                             << tag              \
                             << msg_stream.str() \
                             << std::endl


const std::string TAG_END = "]\033[0m";
const std::string ERROR = "\033[1;31m[E][";
const std::string INFO = "\033[1;36m[I][";
const std::string WARNING = "\033[1;33m[W][";

class Logger {

public:
    Logger() = default;
    ~Logger() = default;

    void Set_Name(std::string name);

    void LOG_INFO(std::string msg);
    void LOG_TIME_INFO(std::string msg, int time);
    void LOG_WARNING(std::string msg);
    void LOG_ERROR_DESCRIPTION(std::string msg, std::string err);
    void LOG_ERROR(std::string msg);

    std::string Time_Stamp();

private:
    std::string m_name;
};
}

#endif /* LOGGER_H */