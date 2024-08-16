#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>
#include <mutex>
#include "server_states.hpp"

class Logger
{
public:
    static Logger &getInstance();
    void log_event(const std::string &message, ServerState state, ServerFunction function);

private:
    Logger() = default;
    std::mutex log_mutex;
    std::string current_time();
};

#endif // LOGGER_HPP
