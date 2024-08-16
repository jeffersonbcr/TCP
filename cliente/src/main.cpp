#include "client.hpp"
#include "logger.hpp"
#include "client_states.hpp"
#include <iostream>

int main()
{
    Logger::getInstance().log_event("Iniciando o cliente.", ClientState::CONNECTING, ClientFunction::CLIENT_CONSTRUCTOR);

    Client *client = new Client("127.0.0.1", 8080);
    client->connect_to_server();

    std::string message;
    while (true)
    {
        std::cout << "Digite a mensagem para enviar ao servidor: ";
        std::getline(std::cin, message);
        Logger::getInstance().log_event("Mensagem digitada: " + message, ClientState::CONNECTED, ClientFunction::SEND_MESSAGE);

        try
        {
            client->send_message(message);
            std::string response = client->receive_message();
            std::cout << "Resposta do servidor: " << response << std::endl;

            Logger::getInstance().log_event("Resposta do servidor recebida: " + response, ClientState::CONNECTED, ClientFunction::RECEIVE_MESSAGE);

            if (message == "exit")
            {
                Logger::getInstance().log_event("Mensagem de encerramento recebida. Encerrando o cliente.", ClientState::DISCONNECTED, ClientFunction::CLIENT_DESTRUCTOR);
                break;
            }
        }
        catch (const std::exception &e)
        {
            Logger::getInstance().log_event("Erro durante comunicação: " + std::string(e.what()), ClientState::ERROR, ClientFunction::RECEIVE_MESSAGE);
        }
    }

    delete client;
    client = nullptr;

    Logger::getInstance().log_event("Cliente encerrado com sucesso.", ClientState::DISCONNECTED, ClientFunction::CLIENT_DESTRUCTOR);
    return 0;
}
