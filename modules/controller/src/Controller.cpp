#include "Controller.h"

Controller::Controller() {
    name="Controller";
    logger.Set_Name(name);
}

int Controller::Init()
{
    device_path = parameters.at("DEVICE_PATH").c_str();
    if (Initialize_Device() != 0)
        return -1;

    return 0;
}

int Controller::Cycle_Step()
{
    Process_Input();

    shared_data->servos.left_servo = state.stick_coordinates[LEFTSTICK].y;
    shared_data->servos.right_servo = state.stick_coordinates[RIGHTSTICK].x;

    // missing stuff for top servo
    return 0;
}

int Controller::Deinit()
{
    logger.LOG_INFO("Deinitializing...");
    if (close(file_descriptor) != 0)
        return -1;

    return 0;
}

// Open file descriptor for the controller
int Controller::Initialize_Device()
{
    logger.LOG_INFO("Initializing...");
    char name[256] = "Unknown";
    if ((file_descriptor = open(device_path, O_RDONLY | O_NONBLOCK)) < 0) {
        logger.LOG_ERROR_DESCRIPTION(std::string("Cannot open ").append(device_path), strerror(errno));
        return -1;
    } else {
        logger.LOG_INFO("Device Recognized");
        ioctl(file_descriptor, JSIOCGNAME(sizeof(name)), name);
        logger.LOG_INFO(std::string("Device name: ").append(name));
    }
    return 0;
}

// Check if the device is still connected
bool Controller::Connected()
{
    js_event* ev = &event;
    ssize_t bytes;
    bytes = read(file_descriptor, ev, sizeof(*ev));
    if (bytes == sizeof(*ev)) {
        return true;
    }
    return false;
}

// Update the coordiantes of the thumbsticks, normalized between -100 and 100
void Controller::Handle_Thumbstick_Events()
{
    size_t thumbstick = event.number / 2;
    if (event.number % 2 == 0)
        state.stick_coordinates[thumbstick].x = -1 * ((event.value) / MAX_COORD_VAL);
    else
        state.stick_coordinates[thumbstick].y = -1 * ((event.value) / MAX_COORD_VAL);
}

// Update the state of the buttons
void Controller::Handle_Button_Events()
{
    state.buttons.at(event.number) = event.value;
}

// Read event if device is connected and update controller state
int Controller::Process_Input()
{
    if (Connected()) {
        switch (event.type) {
        case JS_EVENT_BUTTON:
            Handle_Button_Events();
        case JS_EVENT_AXIS:
            Handle_Thumbstick_Events();
        default:
            break;
        }
    } else {
        return -1;
    }
    return 0;
}

// Factory Method
extern "C" std::shared_ptr<Module> Create_Instance()
{
    return std::make_shared<Controller>();
}

