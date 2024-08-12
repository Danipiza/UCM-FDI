#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() {
    // Especifica la terminal a la que deseas escribir
    const char *terminal = "a.txt";

    // Abre la terminal en modo escritura
    int fd;

    // Duplica el descriptor de archivo para que stdout (descriptor de archivo 1) apunte a la terminal
    if (dup2(STDOUT_FILENO, fd) == -1) {
        perror("dup2");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Cierra el descriptor de archivo original ya que no lo necesitamos más
    //close(fd);

    // Mensaje a escribir en la terminal
    const char *message = "Este mensaje se muestra en la terminal /dev/pts/1\n";

    // Usar write para enviar el mensaje a la terminal
    if (write(fd, message, strlen(message)) == -1) {
        perror("write");
        exit(EXIT_FAILURE);
    }

    return 0;
}
