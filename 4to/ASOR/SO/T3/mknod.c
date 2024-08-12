#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main() {
    const char *path = "./myfifo";
    mode_t mode = 0666; // Permisos: rw-rw-rw-

    // Crear la tubería con nombre
    if (mknod(path, S_IFIFO | mode, 0) < 0 && errno != EEXIST) {
        perror("mknod");
        exit(EXIT_FAILURE);
    }

    // Abrir la tubería en modo escritura
    int fd = open(path, O_WRONLY);
    if (fd < 0) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Mensaje a escribir en la tubería
    const char *message = "Hola, mundo\n";
    
    // Escribir el mensaje en la tubería
    if (write(fd, message, sizeof(message)) < 0) {
        perror("write");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("Mensaje escrito en la tubería: %s\n", message);

    // Cerrar la tubería
    close(fd);

    return 0;
}
