#ifndef COMMON_H
#define COMMON_H

#define VERB true
#define NO_VERB false

#define LOG_INFO(msg) \
    std::cout << "[I][Spider] " << msg << std::endl;
#define LOG_TIME_INFO(msg, time) \
    std::cerr << "[I][Spider] " << msg << " [" << time << " ms]" << std::endl;
#define LOG_WARNING(msg) \
    std::cerr << "[W][Spider] " << msg << std::endl;
#define LOG_ERROR_DESCRIPTION(msg, err) \
    std::cerr << "[E][Spider] " << msg << " " << err << std::endl;
#define LOG_ERROR(msg) \
    std::cerr << "[E][Spider] " << msg << std::endl;

#endif /* COMMON_H */