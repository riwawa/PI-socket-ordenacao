#include "comum.h"
#include <string.h>
#include <arpa/inet.h>

int main(void) {
    char ip[64];
    printf("=== CLIENTE TCP ===\n");
    printf("Digite o IP do servidor: ");

    if (fgets(ip, sizeof(ip), stdin) == NULL) {
        fprintf(stderr, "Erro ao ler IP\n");
        return EXIT_FAILURE;
    }

    ip[strcspn(ip, "\n")] = '\0';

    while (1) {
        // ler entrada do usuário
        char mensagem[80] = {0};
        printf("\nDigite os numeros separados por espaco (ou 'sair'): ");

        if (fgets(mensagem, sizeof(mensagem), stdin) == NULL) {
            if (feof(stdin)) {
                break;
            }
            perror("Erro ao ler mensagem");
            return EXIT_FAILURE;
        }

        if (strcmp(mensagem, "sair\n") == 0 ||
            strcmp(mensagem, "sair") == 0) {
            printf("Encerrando cliente...\n");
            break;
        }

        //conectar ao servidor e enviar msg
        int cliente_fd = configurar_cliente(ip, PORTA);
        printf("Conexao estabelecida! FD: %d\n", cliente_fd);

        size_t total = strlen(mensagem);
        size_t enviado = 0;

        while (enviado < total) {
            ssize_t n = send(
                cliente_fd,
                mensagem + enviado,
                total - enviado,
                0
            );

            if (n <= 0) {
                if (n < 0) {
                    perror("Erro ao enviar mensagem");
                } else {
                    fprintf(stderr, "Nenhum byte enviado.\n");
                }

                close(cliente_fd);
                return EXIT_FAILURE;
            }

            enviado += (size_t)n;
        }

        printf("Bytes enviados: %zu\n", enviado);

        // receber resposta do servidor
        char strData[255] = {0};

        ssize_t recebidos = recv(
            cliente_fd,
            strData,
            sizeof(strData) - 1,
            0
        );

        if (recebidos < 0) {
            perror("Erro no recv");
            close(cliente_fd);
            return EXIT_FAILURE;
        } else if (recebidos == 0) {
            printf("Servidor encerrou a conexao sem resposta.\n");
        } else {
            strData[recebidos] = '\0';
            printf("Mensagem recebida: %s\n", strData);
        }
        close(cliente_fd);
    }

    return 0;
}
