#include "comum.h"
#include <netdb.h>
#include <string.h>

int main(void) {    
    int servidor_fd = configurar_servidor();

    printf("=== SERVIDOR TCP ===\n");
    printf("Porta: %d\n", PORTA);
    printf("Escutando em: 0.0.0.0 (todas as interfaces IPv4)\n");
    printf("Aguardando clientes...\n");

    while (1) {
        int conexao_fd = aceitar_cliente(servidor_fd);
        printf("Cliente conectado!\n");

        char buf[80] = {0};

        // receber mensagem do cliente
        ssize_t msg_cliente = read(conexao_fd, buf, sizeof(buf) - 1);

        if (msg_cliente < 0) {
            perror("Erro no read");
            close(conexao_fd);
            continue;
        }
        if (msg_cliente == 0) {
            printf("Cliente encerrou a conexão.\n");
            close(conexao_fd);
            continue;
        }

        buf[msg_cliente] = '\0';
        printf("Mensagem do cliente: %s\n", buf);
        
        buf[strcspn(buf, "\r\n")] = '\0';

        if (strcmp(buf, "sair") == 0) {
            printf("Comando de encerramento recebido.\n");
            close(conexao_fd);
            break;
        }
        
        close(conexao_fd);
        printf("Aguardando próximo cliente...\n");
    
    }
        

    close(servidor_fd);
    return 0;
}