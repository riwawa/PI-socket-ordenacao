#ifndef COMUM_H
#define COMUM_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define PORTA 9002
#define BACKLOG 10

/*
    1. pedido pro kernel abrir um socket (um canal de comunicacao de rede)
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

int configurar_servidor(){
    int servidor_fd = criar_socket_tcp();

    struct sockaddr_in endereco;
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

#endif
