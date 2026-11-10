#include "comum.h"
#include <netdb.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include "ordenacao.h"

int main(void) {    
    int servidor_fd = configurar_servidor();

    printf("=== SERVIDOR TCP ===\n");
    printf("Porta: %d\n", PORTA);
    printf("Escutando em: 0.0.0.0 (todas as interfaces IPv4)\n");
    printf("Aguardando clientes...\n");
    printf("====================\n");

    while (1) {
        int conexao_fd = aceitar_cliente(servidor_fd);
        printf("> Cliente conectado!\n");

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
        printf("-> Mensagem do cliente: %s\n", buf);
       	printf("ORDENANDO...");

        buf[strcspn(buf, "\r\n")] = '\0';

        if (strcmp(buf, "sair") == 0) {
            printf("Comando de encerramento recebido.\n");
            close(conexao_fd);
            break;
        }
        // converte buf (string) em um vetor de inteiros para a ordenacao
        int numeros[20];
        int qtd=0;
        char *token = strtok(buf, " \t\r\n");
        while(token!=NULL&&qtd<20){
            char *fim;
            errno = 0;
            long valor =strtol(token,&fim,10);

            if(fim==token || *fim!='\0' || errno==ERANGE || valor <INT_MIN || valor > INT_MAX){
                printf("Numero invalido: %s\n", token);
                break;
            }

            numeros[qtd] = (int)valor;
            qtd++;

            token = strtok(NULL, " \t\r\n");
        }
        quicksort(numeros, 0, qtd - 1);
	
	char resp[255];
	int off = 0;
	for (int i = 0; i < qtd; i++) off +=snprintf(resp + off, sizeof resp-off, "%d ", numeros[i]);
	resp[off++]='\n';
	write(conexao_fd, resp, off);

        printf("\n");
        close(conexao_fd);
        printf("Aguardando próximo cliente...\n");
    }
        

    close(servidor_fd);
    return 0;
}
