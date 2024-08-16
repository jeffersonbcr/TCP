// client_states.hpp

#ifndef CLIENT_STATES_HPP
#define CLIENT_STATES_HPP

#include <string>

enum class ClientState
{
    CONNECTING,
    CONNECTED,
    DISCONNECTED,
    ERROR
};

enum class ClientFunction
{
    CONNECT_TO_SERVER,
    SEND_MESSAGE,
    RECEIVE_MESSAGE,
    CLIENT_CONSTRUCTOR,
    CLIENT_DESTRUCTOR
};

std::string to_string(ClientState state);
std::string to_string(ClientFunction function);

#endif // CLIENT_STATES_HPP
