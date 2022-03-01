#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "IModuleInterface.h"

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

private:
    void Handle_Button_Events();
    void Handle_Thumbstick_Events();
    bool Connected();

    const char* m_device_path;
    int m_file_descriptor;
    state_t m_state;
    js_event m_event;


};

#endif /* CONTROLLER_H */