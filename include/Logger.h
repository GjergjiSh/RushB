#ifndef LOGGER_H
#define LOGGER_H

#define VERB true
#define NO_VERB false

#include <iostream>
#include <sstream>
#include <chrono>
#include <ctime>
#include <iomanip>


#define TAG_END "]\033[0m"
#define ERROR "\033[1;31m[E]["
#define INFO "\033[1;36m[I]["
#define WARNING "\033[1;33m[W]["

#define PRINT(tag) std::cout << "[" \
                        << Time_Stamp() \
                        << "] " \
                        << tag \
                        << msg_stream.str() \
                        << std::endl

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
    std::string name;
};

#endif /* LOGGER_H */