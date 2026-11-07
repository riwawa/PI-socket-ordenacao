#include "comum.h"
#include <string.h>

int main(void) {
    printf("1. Iniciando cliente...\n");
    int cliente_fd = configurar_cliente("127.0.0.1", PORTA);

    printf("2. Conexão estabelecida! FD: %d\n", cliente_fd);

    char mensagem[80] = "45 12 78 34 5";
    ssize_t enviado = send(cliente_fd, mensagem, strlen(mensagem), 0);

    if(enviado<0){
        perror("ERRO AO ENVIAR MENSAGEM.");
        close(cliente_fd);
        exit(EXIT_FAILURE); 
    }
    printf("Bytes enviados: %zd\n", enviado);

    close(cliente_fd);
    return 0;
}