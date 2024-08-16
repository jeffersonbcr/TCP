// server_states.hpp

#ifndef SERVER_STATES_HPP
#define SERVER_STATES_HPP

#include <string>

enum class ServerState
{
    STARTING,
    RUNNING,
    STOPPING,
    ERROR
};

enum class ServerFunction
{
    SIGNAL_HANDLER,
    SERVER_CONSTRUCTOR,
    SERVER_START,
    SERVER_STOP,
    ACCEPT_CONNECTIONS,
    HANDLE_CLIENT,
    THREAD_HANDLER
};

std::string to_string(ServerState state);
std::string to_string(ServerFunction function);

#endif // SERVER_STATES_HPP
