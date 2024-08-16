#include "performance.hpp"
#include "logger.hpp"
#include <thread>
#include <chrono>
#include <sys/resource.h>
#include <fstream>
#include <string>
#include <iostream>
#include <unistd.h>

bool PerformanceMonitor::running = true;

void PerformanceMonitor::monitor()
{
    while (running)
    {
        log_cpu_usage();
        log_memory_usage();
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}

void PerformanceMonitor::log_cpu_usage()
{
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    long user_cpu_time = usage.ru_utime.tv_sec + usage.ru_utime.tv_usec / 1e6;
    long sys_cpu_time = usage.ru_stime.tv_sec + usage.ru_stime.tv_usec / 1e6;

    Logger::getInstance().log_event("Uso de CPU - Usuário: " + std::to_string(user_cpu_time) + "s, Sistema: " + std::to_string(sys_cpu_time) + "s");
}

void PerformanceMonitor::log_memory_usage()
{
    std::ifstream statm("/proc/self/statm");
    if (statm.is_open())
    {
        long size, resident, shared, text, lib, data, dt;
        statm >> size >> resident >> shared >> text >> lib >> data >> dt;
        statm.close();

        Logger::getInstance().log_event("Uso de Memória - Total: " + std::to_string(size * getpagesize() / 1024) + " KB, Resident: " + std::to_string(resident * getpagesize() / 1024) + " KB");
    }
    else
    {
        Logger::getInstance().log_event("Falha ao ler o uso de memória.");
    }
}

void PerformanceMonitor::stop()
{
    running = false;
}
