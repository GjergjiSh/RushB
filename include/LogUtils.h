#ifndef COMMON_H
#define COMMON_H

#define VERB true
#define NO_VERB false

#define LOG_INFO(msg) \
    std::cout << "[I][ModuleHandler] " << msg << std::endl;
#define LOG_TIME_INFO(msg, time) \
    std::cerr << "[I][ModuleHandler] " << msg << " [" << time << " ms]" << std::endl;
#define LOG_WARNING(msg) \
    std::cerr << "[W][ModuleHandler] " << msg << std::endl;
#define LOG_ERROR_DESCRIPTION(msg, err) \
    std::cerr << "[E][ModuleHandler] " << msg << " " << err << std::endl;
#define LOG_ERROR(msg) \
    std::cerr << "[E][ModuleHandler] " << msg << std::endl;

#endif /* COMMON_H */