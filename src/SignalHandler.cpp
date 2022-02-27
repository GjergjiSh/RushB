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

    received_exit_sig = true;
}

// Set up the signal handlers for CTRL-C.
int SignalHandler::Init()
{
    logger.Set_Name("SignalHandler");
    if (signal((int)SIGINT, SignalHandler::Exit) == SIG_ERR) {
        logger.LOG_ERROR("Failed to set up signal handler");
        return -1;
    }
    return 0;
}