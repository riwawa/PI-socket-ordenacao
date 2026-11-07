#include "comum.h"

int main(void) {
    char buf[80]={0};
    
    int servidor_fd = configurar_servidor();
    printf("Servidor aguardando clientes...\n");
    int conexao_fd = aceitar_cliente(servidor_fd);
    printf("Cliente conectado!\n");

    ssize_t msg_cliente = read(conexao_fd, buf, sizeof(buf) - 1);
    if (msg_cliente < 0) {
        perror("Erro no read");
        close(conexao_fd);
        close(servidor_fd);
        return EXIT_FAILURE;
    }

    if (msg_cliente == 0) {
        printf("Cliente encerrou a conexão.\n");
    } else {
        buf[msg_cliente] = '\0';
        printf("Mensagem do cliente: %s\n", buf);
    }
    close(conexao_fd);
    close(servidor_fd);
    return 0;
}