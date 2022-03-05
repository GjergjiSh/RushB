#ifndef __SIGNALHANDLER_H__
#define __SIGNALHANDLER_H__

#include <stdexcept>
#include <iostream>

#include "Logger.h"

using std::runtime_error;

class SignalHandler {
protected:
    static bool received_exit_sig;

public:
    SignalHandler() = default;
    ~SignalHandler() = default;

    int Init();
    static void Exit(int);
    static bool Received_Exit_Sig();

    RBLogger::Logger logger;
};
#endif /* __SIGNALHANDLER_H__ */
