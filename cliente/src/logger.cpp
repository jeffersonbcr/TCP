#include "logger.hpp"
#include <fstream>
#include <ctime>
#include <cstring>

Logger &Logger::getInstance()
{
    static Logger instance;
    return instance;
}

void Logger::log_event(const std::string &message, ClientState state, ClientFunction function)
{
    std::lock_guard<std::mutex> guard(log_mutex);
    std::ofstream log_file("logs/client.log", std::ios_base::app);

    log_file << current_time() << " [" << to_string(state) << "] [" << to_string(function) << "] " << message << std::endl;
}

std::string Logger::current_time()
{
    char buffer[20];
    std::time_t now = std::time(nullptr);
    std::tm *tm_info = std::localtime(&now);
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", tm_info);
    return std::string(buffer);
}
