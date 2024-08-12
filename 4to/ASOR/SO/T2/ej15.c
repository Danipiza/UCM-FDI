#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

// COMPILAR: gcc ej15.c -o ej15
// EJECUTAR: ./ej15 <file_path>

// TERMINA: cuando pasan 6s (3s con el fichero bloqueado + 3s con el fichero desbloqueado)

int main(int argc, char** argv){
    if(argc!=2){
        fprintf(stderr, "Usage: %s <file_path>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    int fd=open(argv[1], O_CREAT | O_RDWR, 0666); // hay que darle permisos, y abrirlo para lectura y escritura
    if(fd==-1) { perror("open()"), exit(EXIT_FAILURE); }
    
    if(lockf(fd, F_LOCK, 0)==-1){ perror("BLOCK, lockf()"); exit(EXIT_FAILURE); }
    time_t t;
    t=time(NULL);
    printf("Hora actual %s", ctime(&t));
    printf("Fichero bloqueado\n");
    sleep(3);

    if(lockf(fd, F_ULOCK, 0)==-1){ perror("UNBLOCK, lockf()"); exit(EXIT_FAILURE); }
    printf("Fichero desbloqueado\n");
    sleep(3);
    printf("Fin de la ejecucion\n");


    return 0;
}

