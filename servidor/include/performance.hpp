class PerformanceMonitor
{
public:
    static void monitor();
    static void log_cpu_usage();
    static void log_memory_usage();
    static void stop(); // Adicione uma função para parar o monitoramento
private:
    static bool running; // Flag para controlar o loop de monitoramento
};
