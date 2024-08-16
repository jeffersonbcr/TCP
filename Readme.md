# Projeto de Comunicação TCP Multithread

## Descrição Geral

Este repositório contém dois projetos principais: um **Servidor Multithread TCP** e um **Cliente TCP**. Esses dois projetos foram desenvolvidos em C++ com o objetivo de demonstrar conceitos avançados de comunicação em rede, programação multithread, e boas práticas de engenharia de software, como logging estruturado e gerenciamento seguro de recursos.

### **Servidor Multithread TCP**

O **Servidor Multithread TCP** é responsável por gerenciar múltiplas conexões simultâneas de clientes, utilizando threads para processar as mensagens de cada cliente individualmente. O servidor foi projetado para ser robusto, lidando com situações como desconexão de clientes e shutdown do servidor de maneira segura.

Principais funcionalidades:

- **Conexões Multithread**: Suporte para múltiplas conexões de clientes ao mesmo tempo.
- **Logging Estruturado**: O sistema de logging utiliza enums para registrar o estado do servidor e a função em execução, facilitando a depuração.
- **Monitoramento de Desempenho**: Monitoramento básico de CPU e memória para avaliar o desempenho do servidor.
- **Gerenciamento Seguro de Conexões**: Implementação de shutdown seguro, incluindo o envio de mensagens de encerramento para os clientes.

### **Cliente TCP**

O **Cliente TCP** se conecta ao servidor TCP, envia mensagens e recebe respostas. O cliente foi projetado para ser resiliente, com logs estruturados que permitem rastrear cada ação e a resposta do servidor.

Principais funcionalidades:

- **Conexão ao Servidor**: Estabelece uma conexão TCP com o servidor e mantém a comunicação até que o cliente solicite o encerramento.
- **Envio e Recebimento de Mensagens**: O cliente pode enviar múltiplas mensagens e receber as respostas do servidor em tempo real.
- **Logging Estruturado**: Como no servidor, o cliente também utiliza enums para registrar o estado e a função em execução em cada log.
- **Gerenciamento Seguro de Recursos**: Inclui fechamento seguro de conexões e recursos ao finalizar o cliente.

## Conceito de Desenvolvimento

O desenvolvimento deste projeto foi a implementação de funcionalidades robustas com uma base sólida em boas práticas de programação.

**Principais pontos do desenvolvimento:**

- **Separação de responsabilidades**: O código foi organizado em classes específicas para cada função, como o servidor, cliente, logging e gerenciamento de threads.
- **Boas práticas de C++**: Utilização de recursos modernos do C++, como `std::thread`, `std::mutex`, e gerenciamento automático de recursos para evitar vazamentos de memória.
- **Foco em Logging**: Todos os eventos relevantes no servidor e no cliente são registrados com detalhes, incluindo o estado do sistema e a função que gerou o evento.
- **Segurança**: O código inclui verificações e validações em todas as etapas críticas, como a conexão e o envio de mensagens, para garantir que o sistema se comporte de maneira previsível mesmo em condições adversas.

<h1 align='center'>Autor</h1>

<a href="https://github.com/jeffersonbcr">
    <img style="border-radius: 50%;" src="https://avatars.githubusercontent.com/u/58866006?v=4" width="100px;" alt=""/><br/>
    <sub><b>Jefferson Botitano Calderon Romero</b></sub></a>

<br><br/>
