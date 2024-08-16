#include "logger.hpp"
#include <iostream>

int main()
{
    Logger::getInstance().log_event("Teste de log 1");
    Logger::getInstance().log_event("Teste de log 2");
    std::cout << "Testes de logger concluídos" << std::endl;
    return 0;
}
