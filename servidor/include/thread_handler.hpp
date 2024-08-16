#ifndef THREAD_HANDLER_HPP
#define THREAD_HANDLER_HPP

class ThreadHandler
{
public:
    ThreadHandler(int client_socket);
    void process();

private:
    int client_socket;
    bool handle_request();
};

#endif // THREAD_HANDLER_HPP
