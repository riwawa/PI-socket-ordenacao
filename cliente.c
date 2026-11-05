#include "comum.h"
#include <sys/socket.h>

int main(){
    int cliente_fd = criar_socket_tcp();
    printf("Cliente: Socket criado com sucesso no descritor: %d\n", cliente_fd);

    close(cliente_fd);
    return 0;
}