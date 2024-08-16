#include "client_states.hpp"

std::string to_string(ClientState state)
{
    switch (state)
    {
    case ClientState::CONNECTING:
        return "CONNECTING";
    case ClientState::CONNECTED:
        return "CONNECTED";
    case ClientState::DISCONNECTED:
        return "DISCONNECTED";
    case ClientState::ERROR:
        return "ERROR";
    default:
        return "UNKNOWN";
    }
}

std::string to_string(ClientFunction function)
{
    switch (function)
    {
    case ClientFunction::CONNECT_TO_SERVER:
        return "CONNECT_TO_SERVER";
    case ClientFunction::SEND_MESSAGE:
        return "SEND_MESSAGE";
    case ClientFunction::RECEIVE_MESSAGE:
        return "RECEIVE_MESSAGE";
    case ClientFunction::CLIENT_CONSTRUCTOR:
        return "CLIENT_CONSTRUCTOR";
    case ClientFunction::CLIENT_DESTRUCTOR:
        return "CLIENT_DESTRUCTOR";
    default:
        return "UNKNOWN";
    }
}
