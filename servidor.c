#include "comum.h"
#include <sys/socket.h>
int main(){
    int servidor_fd = configurar_servidor();
    printf("Servidor: Socket criado com sucesso no descritor: %d\n", servidor_fd);

    close(servidor_fd);
    return 0;
}