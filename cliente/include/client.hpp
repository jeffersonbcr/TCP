#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>

class Client
{
public:
    Client(const std::string &server_ip, int server_port);
    ~Client();
    void connect_to_server();
    void send_message(const std::string &message);
    std::string receive_message();

private:
    int sock;
    std::string server_ip;
    int server_port;
};

#endif // CLIENT_HPP
