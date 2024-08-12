#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>


int main(int argc, char** argv){
    if(argc!=3){
        fprintf(stderr,"Usage: %s <comando1> <comando2>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    pid_t pid;
    int fd[2];

    if(pipe(fd)==-1) { perror("pipe()"); exit(EXIT_FAILURE); }
    
    
    pid=fork();
    if(pid==0){ // Hijo - nuevo proceso
        printf("Hijo: %d\n", getpid());

        // 1er comando
        // escribe
        // conecta salida estandar con la entrada estandar del padre

        // se cierra el descriptor de fichero de lectura (no lo va a usar)
        if(close(fd[0])==-1) { perror("HIJO, close(fd[0])"); exit(EXIT_FAILURE); }
        // se redirige la salida estandar a la tuberia de escritura
        if(dup2(fd[1], STDOUT_FILENO)==-1) { perror("HIJO, dup2()"); exit(EXIT_FAILURE); }
        // ya no hace falta el descriptor de fichero
        if(close(fd[1])==-1) { perror("HIJO, close(fd[0])"); exit(EXIT_FAILURE); }

        char *args[] = {argv[1], NULL};
        execvp(args[0], args);

        // no se ha ejecutado correctamente
        perror("execvp()");
        exit(EXIT_FAILURE);
    }
    else if(pid>0) { // Padre - proceso principal
        printf("Padre: %d\n", getpid());

        // 2do comando
        // lee
        
        // se cierra el descriptor de fichero de escritura (no lo va a usar)
        if(close(fd[1])==-1) { perror("PADRE, close(fd[1])"); exit(EXIT_FAILURE); }
        // se redirige la entrada estandar a la tuberia de lectura
        if(dup2(fd[0], STDIN_FILENO)==-1) { perror("PADRE, dup2()"); exit(EXIT_FAILURE); }
        // ya no hace falta el descriptor de fichero
        if(close(fd[0])==-1) { perror("PADRE, close(fd[0])"); exit(EXIT_FAILURE); }

        char *args[] = {argv[2], NULL};
        execvp(args[0], args);     
        // no se ha ejecutado correctamente
        perror("execvp()");
        exit(EXIT_FAILURE);
    }
    else { // error
        perror("fork()");
        exit(EXIT_FAILURE);
    }

    return 0;
}