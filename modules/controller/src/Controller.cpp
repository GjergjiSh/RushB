#include "Controller.h"

Controller::Controller() {
    name="Controller";
    logger.Set_Name(name);
}

int Controller::Init()
{
    m_device_path = parameters.at("DEVICE_PATH").c_str();
    if (Initialize_Device() != 0)
        return -1;

    return 0;
}

int Controller::Cycle_Step()
{
    Process_Input();

    shared_data->servos.left_servo = (int) m_state.stick_coordinates[LEFTSTICK].y;
    shared_data->servos.right_servo = (int) m_state.stick_coordinates[RIGHTSTICK].x;

    // missing stuff for top servo
    return 0;
}

int Controller::Deinit() {
    logger.Info("Deinitializing...");
    if (close(m_file_descriptor) != 0) {
        logger.Warning("Failed to close te file descriptor");
        return -1;
    }

    return 0;
}

// Open file descriptor for the controller
int Controller::Initialize_Device()
{
    logger.Info("Initializing...");
    char name[256] = "Unknown";
    if ((m_file_descriptor = open(m_device_path, O_RDONLY | O_NONBLOCK)) < 0) {
        logger.Error_Description(std::string("Cannot open ").append(m_device_path), strerror(errno));
        return -1;
    } else {
        logger.Info("Device Recognized");
        ioctl(m_file_descriptor, JSIOCGNAME(sizeof(name)), name);
        logger.Info(std::string("Device name: ").append(name));
    }
    return 0;
}

// Check if the device is still connected
bool Controller::Connected()
{
    js_event* ev = &m_event;
    ssize_t bytes;
    bytes = read(m_file_descriptor, ev, sizeof(*ev));
    if (bytes == sizeof(*ev)) {
        return true;
    }
    return false;
}

// Update the coordiantes of the thumbsticks, normalized between -100 and 100
void Controller::Handle_Thumbstick_Events()
{
    size_t thumbstick = m_event.number / 2;
    if (m_event.number % 2 == 0)
        m_state.stick_coordinates[thumbstick].x = (float) (-1 * ((m_event.value) / MAX_COORD_VAL));
    else
        m_state.stick_coordinates[thumbstick].y = (float) (-1 * ((m_event.value) / MAX_COORD_VAL));
}

// Update the m_state of the buttons
void Controller::Handle_Button_Events()
{
    m_state.buttons.at(m_event.number) = m_event.value;
}

// Read m_event if device is connected and update controller m_state
int Controller::Process_Input()
{
    if (Connected()) {
        switch (m_event.type) {
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
std::shared_ptr<Module> Create_Instance()
{
    return std::make_shared<Controller>();
}

