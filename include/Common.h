#ifndef COMMON_H
#define COMMON_H

#define LOG_INFO(msg) \
    std::cout << "[I] " << msg << std::endl;
#define LOG_WARNING(msg) \
    std::cerr << "[W] " << msg << std::endl;
#define LOG_ERROR_DESCRIPTION(msg, err) \
    std::cerr << "[E] " << msg << " " << err << std::endl;
#define LOG_ERROR(msg) \
    std::cerr << "[E] " << msg << std::endl;

#endif /* COMMON_H */