#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <errno.h>

// COMPILAR: gcc ej11.c -o ej11
// EJECUTAR: ./ej11

// TERMINA: al pasar 3 segundos (variable de entorno SLEEP_SEC)


int main(int argc, char** argv){
    sigset_t block_set, pending_set;
    int sigi, sigs;
    int sleep_env;
    printf("PID: %d\n",getpid());
    char *sleep_str=getenv("SLEEP_SEC");
    if (sleep_str == NULL) { // variable de entorno SLEEP_SEC no definida        
        setenv("SLEEP_SEC", "3", 1); // crear con valor "3"
        sleep_str=getenv("SLEEP_SEC");
        printf("Variable de entorno SLEEP_SEC creada.\n");
    }    
    sleep_env=atoi(sleep_str); 
    if(sleep_env==0){
        printf("Error en atoi()");
        exit(EXIT_FAILURE);
    }

    if(sigemptyset(&block_set)==-1) { perror("sigemptyset()"); exit(EXIT_FAILURE); }
    if(sigaddset(&block_set, SIGINT)==-1 ||  sigaddset(&block_set, SIGTSTP)==-1){
        perror("sigemptyset()"); 
        exit(EXIT_FAILURE); 
    }

    
    if(sigprocmask(SIG_BLOCK, &block_set, NULL)){
        perror("sigpromask(block)");
        exit(EXIT_FAILURE);
    }
    

    sleep(sleep_env);
    if(sigpending(&pending_set)==-1){
        perror("sigpending()");
        exit(EXIT_FAILURE);
    }
    
    sigi=sigismember(&pending_set,SIGINT);
    sigs=sigismember(&pending_set,SIGTSTP);
    if(sigi==-1||sigs==-1){
        perror("sigismember()");
        exit(EXIT_FAILURE);
    }
    
    if(sigi+sigs) printf("\n");
    if(sigi==1) printf("Se ha recibido SIGINT Ctrl+C\n");
    if(sigs==1) printf("Se ha recibido SIGTSTP Ctrl+Z\n");
        

    
    if(sigprocmask(SIG_BLOCK, &block_set, NULL)){
        perror("sigpromask(unblock)");
        exit(EXIT_FAILURE);
    }

    printf("Cadena al final de la ejecucion\n");

    return 0;
}