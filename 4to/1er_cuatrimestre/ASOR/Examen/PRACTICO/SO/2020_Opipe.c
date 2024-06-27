#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>   
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>

// COMPILAR gcc 2020_Opipe.c -o conecta
// EJECUCION ./conecta comando1 comando2 arg2_1 arg2_2 ...

#define BUF_SIZE 256

int main(int argc, char** argv){
    if(argc<3){
        fprintf(stderr, "Usage: %s <cmd1> <cmd2> [args_cmd2]\n",argv[0]);
        exit(EXIT_FAILURE);
    }

    pid_t pid1, pid2;
    int fd[2];

    if(pipe(fd)==-1) { perror("pipe()"); exit(EXIT_FAILURE); }
    
    // salida estandar del primero con la entrada estandar del segundo
    pid1=fork();
    if(pid1==-1) { perror("fork()"); exit(EXIT_FAILURE); }
    else if(pid1==0){ // Hijo 1
        printf("HIJO 1, PID: %d\n", (int) getpid());
        // escribe el primer comando para que lo reciba el segundo
        if(close(fd[0])==-1) { perror("close()"); exit(EXIT_FAILURE); }
        if(dup2(fd[1], STDOUT_FILENO)==-1) { perror("dup()"); exit(EXIT_FAILURE); }
        if(close(fd[1])==-1) { perror("close()"); exit(EXIT_FAILURE); }
        
        char *args[]={argv[1],NULL};
        execvp(args[0], args);
        perror("exec()"); 
        exit(EXIT_FAILURE);
    }
    pid2=fork();
    if(pid2==-1) { perror("fork()"); exit(EXIT_FAILURE); }
    else if(pid2==0){ // Hijo 2
        printf("HIJO 2, PID: %d\n", (int) getpid());
        // lee la salida del primer comando
        if(close(fd[1])==-1) { perror("close()"); exit(EXIT_FAILURE); }
        if(dup2(fd[0], STDIN_FILENO)==-1) { perror("dup()"); exit(EXIT_FAILURE); }
        if(close(fd[0])==-1) { perror("close()"); exit(EXIT_FAILURE); }
        
        /*char *args[argc-1];
        for(int i=0;i<argc-2;i++){
            args[i]=argv[i+2];
        }
        args[argc-2]=NULL;
        execvp(args[0], args);
        perror("exec()"); 
        exit(EXIT_FAILURE);*/
        char *args[]={argv[2],NULL};
        execvp(args[0], args);
        perror("exec()"); 
        exit(EXIT_FAILURE);
    }
    
    // hay que cerrarlo si no se cierra, no finaliza correctamente
    close(fd[0]);
    close(fd[1]);

    // padre espera
    /*waitpid(pid1, &wstatus, 0);
    waitpid(pid2, &wstatus, 0);*/
    int wstatus;
    for(int i=0;i<2;i++) wait(&wstatus);
    

    return 0;
}