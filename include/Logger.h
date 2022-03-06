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

    const std::string TAG_END = "]\033[0m";
    const std::string ERROR = "\033[1;31m[E][";
    const std::string INFO = "\033[1;32m[I][";
    const std::string WARNING = "\033[1;33m[W][";
    const std::string DEBUG = "\033[1;36m[D][";


    class Logger {

    public:
        Logger() = default;

        ~Logger() = default;

        void Set_Name(std::string name);

        void Info(const std::string &msg);

        void Time_Info(const std::string &msg, int time);

        void Warning(const std::string &msg);

        void Debug(const std::string &msg);

        void Error_Description(const std::string &msg, const std::string &err);

        void Error(const std::string &msg);

        static std::string Time_Stamp();

    private:
        std::string m_name;

        void Log(const std::string &tag, std::stringstream &msg);
    };
}

#endif /* LOGGER_H */