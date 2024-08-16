
#include "server_states.hpp"
#include <string>

std::string to_string(ServerState state)
{
    switch (state)
    {
    case ServerState::STARTING:
        return "STARTING";
    case ServerState::RUNNING:
        return "RUNNING";
    case ServerState::STOPPING:
        return "STOPPING";
    case ServerState::ERROR:
        return "ERROR";
    default:
        return "UNKNOWN";
    }
}

std::string to_string(ServerFunction function)
{
    switch (function)
    {
    case ServerFunction::SIGNAL_HANDLER:
        return "SIGNAL_HANDLER";
    case ServerFunction::SERVER_CONSTRUCTOR:
        return "SERVER_CONSTRUCTOR";
    case ServerFunction::SERVER_START:
        return "SERVER_START";
    case ServerFunction::SERVER_STOP:
        return "SERVER_STOP";
    case ServerFunction::ACCEPT_CONNECTIONS:
        return "ACCEPT_CONNECTIONS";
    case ServerFunction::HANDLE_CLIENT:
        return "HANDLE_CLIENT";
    case ServerFunction::THREAD_HANDLER:
        return "THREAD_HANDLER";
    default:
        return "UNKNOWN";
    }
}
