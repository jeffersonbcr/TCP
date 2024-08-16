#include "server.hpp"
#include "performance.hpp"
#include <thread>
#include <signal.h>

void ignore_sigpipe()
{
    struct sigaction sa;
    sa.sa_handler = SIG_IGN;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGPIPE, &sa, 0);
}

int main()
{
    ignore_sigpipe();
    Server *server = new Server(8080);
    // std::thread *perf_thread = new std::thread(PerformanceMonitor::monitor);

    server->start();

    // if (perf_thread && perf_thread->joinable())
    // {
    //     perf_thread->join();
    // }

    delete server;
    // delete perf_thread;

    return 0;
}
