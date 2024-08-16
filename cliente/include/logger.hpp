#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>
#include <ctime>
#include <mutex>
#include "client_states.hpp"

class Logger
{
public:
    static Logger &getInstance();

    void log_event(const std::string &message, ClientState state, ClientFunction function);

private:
    Logger() {}
    Logger(const Logger &) = delete;
    Logger &operator=(const Logger &) = delete;

    std::string current_time();
    std::mutex log_mutex;
};

#endif // LOGGER_HPP
