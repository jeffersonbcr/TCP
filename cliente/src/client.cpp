#include "client.hpp"
#include "logger.hpp"
#include "client_states.hpp"
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

Client::Client(const std::string &server_ip, int server_port)
    : server_ip(server_ip), server_port(server_port), sock(0)
{
    Logger::getInstance().log_event("Cliente criado.", ClientState::CONNECTING, ClientFunction::CLIENT_CONSTRUCTOR);
}

Client::~Client()
{
    if (sock > 0)
    {
        close(sock);
        Logger::getInstance().log_event("Socket fechado no destrutor do cliente.", ClientState::DISCONNECTED, ClientFunction::CLIENT_DESTRUCTOR);
    }
}

void Client::connect_to_server()
{
    Logger::getInstance().log_event("Tentando conectar ao servidor...", ClientState::CONNECTING, ClientFunction::CONNECT_TO_SERVER);

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        Logger::getInstance().log_event("Erro ao criar o socket.", ClientState::ERROR, ClientFunction::CONNECT_TO_SERVER);
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(server_port);

    if (inet_pton(AF_INET, server_ip.c_str(), &serv_addr.sin_addr) <= 0)
    {
        Logger::getInstance().log_event("Endereço inválido ou não suportado.", ClientState::ERROR, ClientFunction::CONNECT_TO_SERVER);
        exit(EXIT_FAILURE);
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        Logger::getInstance().log_event("Falha ao conectar ao servidor.", ClientState::ERROR, ClientFunction::CONNECT_TO_SERVER);
        exit(EXIT_FAILURE);
    }

    Logger::getInstance().log_event("Conectado ao servidor " + server_ip + " na porta " + std::to_string(server_port), ClientState::CONNECTED, ClientFunction::CONNECT_TO_SERVER);
}

void Client::send_message(const std::string &message)
{
    if (sock <= 0)
    {
        Logger::getInstance().log_event("Erro: Socket inválido ou fechado.", ClientState::ERROR, ClientFunction::SEND_MESSAGE);
        return;
    }

    Logger::getInstance().log_event("Enviando mensagem: " + message, ClientState::CONNECTED, ClientFunction::SEND_MESSAGE);
    int bytes_sent = send(sock, message.c_str(), message.length(), 0);
    if (bytes_sent < 0)
    {
        Logger::getInstance().log_event("Erro ao enviar a mensagem: " + std::string(strerror(errno)), ClientState::ERROR, ClientFunction::SEND_MESSAGE);
    }
    else
    {
        Logger::getInstance().log_event("Bytes enviados: " + std::to_string(bytes_sent) + " de " + std::to_string(message.size()), ClientState::CONNECTED, ClientFunction::SEND_MESSAGE);
    }

    if (message == "exit")
    {
        shutdown(sock, SHUT_WR);
        Logger::getInstance().log_event("Conexão encerrada pelo cliente.", ClientState::DISCONNECTED, ClientFunction::SEND_MESSAGE);
    }
}

std::string Client::receive_message()
{
    if (sock <= 0)
    {
        Logger::getInstance().log_event("Erro: Socket inválido ou fechado.", ClientState::ERROR, ClientFunction::RECEIVE_MESSAGE);
        return "";
    }

    char buffer[1024] = {0};
    int valread = read(sock, buffer, sizeof(buffer));
    if (valread > 0)
    {
        std::string received_message(buffer, valread);
        Logger::getInstance().log_event("Resposta recebida do servidor: " + received_message, ClientState::CONNECTED, ClientFunction::RECEIVE_MESSAGE);
        return received_message;
    }
    else if (valread == 0)
    {
        Logger::getInstance().log_event("Servidor desconectado.", ClientState::DISCONNECTED, ClientFunction::RECEIVE_MESSAGE);
        return "";
    }
    else
    {
        Logger::getInstance().log_event("Erro ao ler do servidor: " + std::string(strerror(errno)), ClientState::ERROR, ClientFunction::RECEIVE_MESSAGE);
        return "";
    }
}
