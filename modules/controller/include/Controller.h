#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "ModuleInterface.h"

#include <linux/joystick.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <mutex>
#include <string.h>
#include <thread>

#define LEFTSTICK 0
#define RIGHTSTICK 2
#define L1 4
#define R1 5
#define SELECT 6
#define START 7
#define L3 9
#define R3 10

#define PRESSED 1
#define RELEASED 0

#define MAX_COORD_VAL 327.67

#define LOG_INFO(msg) \
    std::cout << "[I][Controller] " << msg << std::endl;
#define LOG_TIME_INFO(msg, time) \
    std::cerr << "[I][Controller] " << msg << " [" << time << " ms]" << std::endl;
#define LOG_WARNING(msg) \
    std::cerr << "[W][Controller] " << msg << std::endl;
#define LOG_ERROR_DESCRIPTION(msg, err) \
    std::cerr << "[E][Controller] " << msg << " " << err << std::endl;
#define LOG_ERROR(msg) \
    std::cerr << "[E][Controller] " << msg << std::endl;

struct coordinates_t {
    float x, y;
};

struct state_t {
    coordinates_t stick_coordinates[3];
    std::unordered_map<int, bool> buttons = {
        std::make_pair(L1, RELEASED),
        std::make_pair(R1, RELEASED),
        std::make_pair(L3, RELEASED),
        std::make_pair(R3, RELEASED),
        std::make_pair(SELECT, RELEASED),
        std::make_pair(START, RELEASED)};
};

class Controller : public Module {

public:
    Controller();
    ~Controller() = default;
    int Init(void) override;
    int Cycle_Step(void) override;
    int Deinit(void) override;

    int Process_Input();
    int Initialize_Device();
    void Print_Driver_Wish();

private:
    void Handle_Button_Events();
    void Handle_Thumbstick_Events();
    bool Connected();

    const char* device_path;
    int file_descriptor;
    state_t state;
    js_event event;
};

#endif /* CONTROLLER_H */