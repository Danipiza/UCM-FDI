#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

// SIMULAR: echo 1234 |  wc -c

// COMPILAR: gcc ej14.c -o ej14
// EJECUTAR: ./ej14 echo 12345 wc -c

// TERMINA: normal, ejecutando el comando
    

int main(int argc, char** argv){
    if(argc!=5){
        fprintf(stderr, "Usage: %s <comando1> <arg1> <comando2> <arg2>\n",argv[0]);
        return -1;
    }

    pid_t pid;
    int fd[2];
    if(pipe(fd)==-1){ perror("pipe()"); exit(EXIT_FAILURE); }

    pid=fork();
    if(pid==0){ // Hijo
        // Lectura
        if(close(fd[1])==-1) { perror("HIJO, close()"); exit(EXIT_FAILURE);}
        // redirigir entrada estandar -> lectura        
        if(dup2(fd[0],STDIN_FILENO)) { perror("HIJO, dup2()"); exit(EXIT_FAILURE);}
        if(close(fd[0])==-1) { perror("HIJO, close()"); exit(EXIT_FAILURE);}
        
        char *cmd2[] = {argv[3], argv[4], NULL};
        execvp(cmd2[0], cmd2);

      /*char *cmd2[] = {argv[2], argv[3], NULL};
        execvp(cmd2[0], cmd2);*/

        perror("HIJO, execvp()");
        exit(EXIT_FAILURE);
    }   
    else if(pid>0){ // Padre
        // Escritura
        if(close(fd[0])==-1) { perror("PADRE, close()"); exit(EXIT_FAILURE);}
        // reedirigir salida estandar -> escritura
        if(dup2(fd[1],STDOUT_FILENO)==-1) { perror("PADRE, dup2()"); exit(EXIT_FAILURE);}
        if(close(fd[1])==-1) { perror("PADRE, close()"); exit(EXIT_FAILURE);}
        
        char *args[] = {argv[1], argv[2], NULL};
        execvp(args[0], args);
      
      /*char *args[] = {argv[1], NULL};
        execvp(args[0], args);*/
        
        perror("PADRE, execvp");
        exit(EXIT_FAILURE);
    }
    else {
        perror("fork()");
        exit(EXIT_FAILURE);
    }

    return 0;
}