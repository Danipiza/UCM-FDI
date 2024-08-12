#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

// COMPILAR: gcc ej12.c -o ej12
// EJECUTAR: ./ej12

// TERMINA: al mandar 10 señales SIGINT (Ctrl + C) + SIGTSTP (Ctrl + Z) 


volatile int sig_int=0;
volatile int sig_stp=0;
void handler(int sig){
    if(sig==SIGINT)sig_int++;
    if(sig==SIGTSTP) sig_stp++;
}

int main(int argc, char** argv){
    struct sigaction sa;
    
    sigemptyset(&sa.sa_mask);
    sa.sa_flags=0;
    sa.sa_handler=handler;
             

    if(sigaction(SIGINT, &sa, NULL)==-1 || sigaction(SIGTSTP, &sa, NULL)==-1){
        perror("sigaction()");
        exit(EXIT_FAILURE);
    }

    while(sig_int+sig_stp<10);
    
    printf("SIGINT: %d\tSIGTSTP: %d\n",sig_int, sig_stp);

    return 0;
}