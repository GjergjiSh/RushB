#include <errno.h>
#include <signal.h>

#include "SignalHandler.h"

bool SignalHandler::received_exit_sig = false;

// Returns the bool flag indicating whether we received an exit signal
bool SignalHandler::Received_Exit_Sig()
{
    return received_exit_sig;
}

// Set exit signal to true.
void SignalHandler::Exit(int)
{
    std::cout << "[I][SignalHandler] Received Interrput Signal" << std::endl;
    received_exit_sig = true;
}

// Set up the signal handlers for CTRL-C.
void SignalHandler::Init()
{
    if (signal((int)SIGINT, SignalHandler::Exit) == SIG_ERR) {
        throw SignalException("[E][SignalHandler] Failed to set up signal handlers");
    }
}