#ifndef SERVER_HPP
#define SERVER_HPP

#include <vector>
#include <thread>
#include <mutex>

class Server
{
public:
    Server(int port);
    ~Server();
    void start();
    void stop();

private:
    int server_socket;
    int port;
    bool running;
    std::vector<std::thread> threads;
    std::mutex connection_mutex;

    void accept_connections();
    void handle_client(int client_socket);
};

#endif // SERVER_HPP
