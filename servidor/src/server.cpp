#include "server.hpp"
#include "thread_handler.hpp"
#include "logger.hpp"
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <csignal>
#include "server_states.hpp"

Server *global_server = nullptr;

void signal_handler(int signum)
{
    Logger::getInstance().log_event("Sinal recebido: " + std::to_string(signum) + ". Encerrando o servidor de forma segura...", ServerState::STOPPING, ServerFunction::SIGNAL_HANDLER);
    if (global_server)
    {
        global_server->stop();
        delete global_server;
        global_server = nullptr;
    }
    exit(signum);
}

Server::Server(int port) : port(port), running(false)
{
    Logger::getInstance().log_event("Inicializando o servidor...", ServerState::STARTING, ServerFunction::SERVER_CONSTRUCTOR);
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == 0)
    {
        Logger::getInstance().log_event("Falha ao criar socket.", ServerState::ERROR, ServerFunction::SERVER_CONSTRUCTOR);
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(server_socket, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        Logger::getInstance().log_event("Falha ao vincular o socket.", ServerState::ERROR, ServerFunction::SERVER_CONSTRUCTOR);
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, 3) < 0)
    {
        Logger::getInstance().log_event("Falha ao escutar no socket.", ServerState::ERROR, ServerFunction::SERVER_CONSTRUCTOR);
        exit(EXIT_FAILURE);
    }

    Logger::getInstance().log_event("Servidor iniciado com sucesso.", ServerState::RUNNING, ServerFunction::SERVER_CONSTRUCTOR);
}

Server::~Server()
{
    Logger::getInstance().log_event("Destruindo o servidor...", ServerState::STOPPING, ServerFunction::SERVER_CONSTRUCTOR);
    stop();
}

void Server::start()
{
    Logger::getInstance().log_event("Servidor iniciado. Aceitando conexões...", ServerState::RUNNING, ServerFunction::SERVER_START);
    running = true;
    accept_connections();
}

void Server::stop()
{
    Logger::getInstance().log_event("Encerrando o servidor...", ServerState::STOPPING, ServerFunction::SERVER_STOP);
    if (running)
    {
        running = false;
        if (server_socket > 0)
        {
            close(server_socket);
            Logger::getInstance().log_event("Socket do servidor fechado.", ServerState::STOPPING, ServerFunction::SERVER_STOP);
        }
        for (auto &t : threads)
        {
            if (t.joinable())
            {
                t.join();
            }
        }
        Logger::getInstance().log_event("Servidor parado.", ServerState::STOPPING, ServerFunction::SERVER_STOP);
    }
}

void Server::accept_connections()
{
    Logger::getInstance().log_event("Aceitando conexões...", ServerState::RUNNING, ServerFunction::ACCEPT_CONNECTIONS);
    while (running)
    {
        int client_socket;
        struct sockaddr_in client_address;
        socklen_t client_len = sizeof(client_address);

        client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_len);
        if (client_socket < 0)
        {
            Logger::getInstance().log_event("Falha ao aceitar conexão.", ServerState::ERROR, ServerFunction::ACCEPT_CONNECTIONS);
            continue;
        }

        Logger::getInstance().log_event("Nova conexão aceita.", ServerState::RUNNING, ServerFunction::ACCEPT_CONNECTIONS);
        std::thread client_thread(&Server::handle_client, this, client_socket);
        std::lock_guard<std::mutex> guard(connection_mutex);
        threads.push_back(std::move(client_thread));
    }
}

void Server::handle_client(int client_socket)
{
    Logger::getInstance().log_event("Iniciando processamento de cliente...", ServerState::RUNNING, ServerFunction::HANDLE_CLIENT);
    try
    {
        ThreadHandler handler(client_socket);
        handler.process();
    }
    catch (const std::exception &e)
    {
        Logger::getInstance().log_event("Erro ao processar cliente: " + std::string(e.what()), ServerState::ERROR, ServerFunction::HANDLE_CLIENT);
    }
    Logger::getInstance().log_event("Processamento de cliente concluído.", ServerState::RUNNING, ServerFunction::HANDLE_CLIENT);
}
