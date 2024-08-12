#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

// COMPILAR: gcc ej13.c -o ej13
// EJECUTAR: ./ej13 <int:tiempo>

// TERMINAL
// kill -SIGUSR1 <pid>

// TERMINA: al pasar "tiempo" segundos

int main(int argc, char** argv){
    if(argc!=2){        
        fprintf(stderr, "Usage: %s <int:tiempo>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    sigset_t block_set, sig_set;
    int tsleep=atoi(argv[1]);
    int del=1;
    if(tsleep==0){
        printf("error en atoi()\n");
        exit(EXIT_FAILURE);
    }

    printf("PID: %d\n",getpid());

    if(sigemptyset(&block_set)==-1) { // init
        perror("sigemptyset()");
        exit(EXIT_FAILURE);
    }
    if(sigaddset(&block_set,SIGUSR1)){ // añade SIGUSR1
        perror("sigaddset()");
        exit(EXIT_FAILURE);
    }
    
    if(sigprocmask(SIG_BLOCK, &block_set, NULL)){
        perror("sigprocmask()");
        exit(EXIT_FAILURE);
    }

    sleep(tsleep);
    sigpending(&sig_set);
    if(sigismember(&sig_set, SIGUSR1)){
        del=0;
        printf("Se recibe SIGUSR1, no se borra el ejecutable.\n");
    }

    if(sigprocmask(SIG_UNBLOCK, &block_set, NULL)){
        perror("sigprocmask()");
        exit(EXIT_FAILURE);
    }

    if(del){    
        if(remove(argv[0])==-1){ // tambien se puede hacer con unlink(argv[1])
            perror("remove()");
            exit(EXIT_FAILURE);
        }

        printf("Ejecutable eliminado correctamente.\n");
    }

    return 0;
}
