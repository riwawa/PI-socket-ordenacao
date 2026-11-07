#ifndef COMUM_H
#define COMUM_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdint.h>  
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORTA 9002
#define BACKLOG 10

/*
    pedido pro kernel abrir um socket (um canal de comunicacao de rede)
    retornando um numero inteiro. vai ser usado tanto no cliente quanto no servidor
    https://man7.org/linux/man-pages/man2/socket.2.html (man 2 socket)
*/
int criar_socket_tcp() {
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd<0) {
        perror("ERRO AO CRIAR O CANAL DE COMUNICAÇÃO.");
        exit(EXIT_FAILURE);
    }

    return socketfd;
}
/*
    funcao geral do servidor
*/
int configurar_servidor(){
    int servidor_fd = criar_socket_tcp();

    struct sockaddr_in endereco;
    socklen_t tamanho = sizeof(endereco);
    endereco.sin_family = AF_INET;
    endereco.sin_addr.s_addr = INADDR_ANY; 
    endereco.sin_port = htons(PORTA);

    if (bind(servidor_fd, (struct sockaddr *)&endereco, sizeof(endereco)) < 0) {
        perror("ERRO NO BIND DO SERVIDOR.");
        close(servidor_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(servidor_fd, BACKLOG) < 0) {
        perror("ERRO AO ATIVAR O MODO LISTEN.");
        close(servidor_fd);
        exit(EXIT_FAILURE);
    }

    return servidor_fd;
}

int configurar_cliente(const char *ip, uint16_t porta){
    int cliente_fd = criar_socket_tcp();
    printf("Socket criado: %d\n", cliente_fd);
    struct sockaddr_in endereco = {0};

    endereco.sin_family = AF_INET;
    endereco.sin_port = htons(porta);

    int resultado = inet_pton(AF_INET, ip, &endereco.sin_addr);
    printf("Retorno do inet_pton: %d\n", resultado);

    if (resultado != 1) {
        fprintf(stderr, "IP inválido ou erro na conversão\n");
        close(cliente_fd);
        exit(EXIT_FAILURE);
    }
    printf("Tentando conectar...\n");

    if (connect(cliente_fd, (struct sockaddr *)&endereco, sizeof(endereco))<0){
        perror("ERRO AO CONECTAR.");
        close(cliente_fd);
        exit(EXIT_FAILURE); 
    }


    return cliente_fd;
}
int aceitar_cliente(int servidor_fd) {
    int conexao_fd = accept(servidor_fd, NULL, NULL);

    if (conexao_fd < 0) {
        perror("Erro ao aceitar cliente");
        return -1;
    }
    return conexao_fd;
}
#endif
