#include "thread_handler.hpp"
#include "logger.hpp"
#include "server_states.hpp"
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <cstring>

ThreadHandler::ThreadHandler(int client_socket) : client_socket(client_socket)
{
    Logger::getInstance().log_event("ThreadHandler criado para o cliente.", ServerState::RUNNING, ServerFunction::THREAD_HANDLER);
}

void ThreadHandler::process()
{
    bool continue_processing = true;
    Logger::getInstance().log_event("Iniciando processamento de mensagens para o cliente.", ServerState::RUNNING, ServerFunction::THREAD_HANDLER);
    while (continue_processing)
    {
        continue_processing = handle_request();
    }
    Logger::getInstance().log_event("Processamento de mensagens concluído para o cliente.", ServerState::RUNNING, ServerFunction::THREAD_HANDLER);
}

bool ThreadHandler::handle_request()
{
    Logger::getInstance().log_event("Aguardando mensagem do cliente...", ServerState::RUNNING, ServerFunction::THREAD_HANDLER);
    char buffer[1024] = {0};
    int valread = read(client_socket, buffer, sizeof(buffer));
    if (valread > 0)
    {
        Logger::getInstance().log_event("Bytes recebidos do cliente: " + std::to_string(valread) + " bytes.", ServerState::RUNNING, ServerFunction::THREAD_HANDLER);

        std::string received_message(buffer, valread);
        if (received_message == "exit")
        {
            Logger::getInstance().log_event("Cliente solicitou encerrar a conexão.", ServerState::RUNNING, ServerFunction::THREAD_HANDLER);

            std::string response = "Conexão encerrada pelo servidor.";
            Logger::getInstance().log_event("Enviando mensagem de encerramento ao cliente: " + response, ServerState::RUNNING, ServerFunction::THREAD_HANDLER);

            int bytes_sent = send(client_socket, response.c_str(), response.size(), 0);
            if (bytes_sent < 0)
            {
                Logger::getInstance().log_event("Erro ao enviar mensagem de encerramento: " + std::string(strerror(errno)), ServerState::ERROR, ServerFunction::THREAD_HANDLER);
            }
            else if (bytes_sent < response.size())
            {
                Logger::getInstance().log_event("Aviso: Mensagem de encerramento enviada parcialmente: " + std::to_string(bytes_sent) + " de " + std::to_string(response.size()) + " bytes.", ServerState::RUNNING, ServerFunction::THREAD_HANDLER);
            }
            else
            {
                Logger::getInstance().log_event("Mensagem de encerramento enviada com sucesso.", ServerState::RUNNING, ServerFunction::THREAD_HANDLER);
            }

            shutdown(client_socket, SHUT_RDWR);
            close(client_socket);
            return false;
        }

        Logger::getInstance().log_event("Mensagem recebida do cliente: " + received_message, ServerState::RUNNING, ServerFunction::THREAD_HANDLER);

        std::string response = "Mensagem recebida: " + received_message;
        int total_sent = 0;
        while (total_sent < response.size())
        {
            int sent = send(client_socket, response.c_str() + total_sent, response.size() - total_sent, 0);
            if (sent < 0)
            {
                Logger::getInstance().log_event("Erro ao enviar dados ao cliente: " + std::string(strerror(errno)), ServerState::ERROR, ServerFunction::THREAD_HANDLER);
                return false;
            }
            total_sent += sent;
        }

        Logger::getInstance().log_event("Resposta enviada ao cliente: " + response, ServerState::RUNNING, ServerFunction::THREAD_HANDLER);
        return true;
    }
    else if (valread == 0)
    {
        Logger::getInstance().log_event("Cliente desconectado.", ServerState::RUNNING, ServerFunction::THREAD_HANDLER);
        close(client_socket);
        return false;
    }
    else
    {
        Logger::getInstance().log_event("Erro ao ler do cliente: " + std::string(strerror(errno)), ServerState::ERROR, ServerFunction::THREAD_HANDLER);
        close(client_socket);
        return false;
    }
}
