#ifndef __SIGNALHANDLER_H__
#define __SIGNALHANDLER_H_
#include <stdexcept>
#include <iostream>

using std::runtime_error;

class SignalException : public runtime_error {
public:
    SignalException(const std::string& _message)
        : std::runtime_error(_message){}
};

class SignalHandler {
protected:
    static bool received_exit_sig;

public:
    SignalHandler() = default;
    ~SignalHandler() = default;

    void Init();
    static void Exit(int);
    static bool Received_Exit_Sig();
};
#endif /* __SIGNALHANDLER_H__ */
