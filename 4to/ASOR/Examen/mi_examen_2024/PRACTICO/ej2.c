// PIZARRO GALLEGO, DANIEL
// 11869584C

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

// COMPILAR: gcc ej2.c -o ej2
// EJECUTAR: 
// ejemplo tcp: ./ej2

// TERMINA cuando recibe 10 señales (SIGINT o SIGSTP)
// se puede enviar con combinaciones de teclas en la terminal usando Ctrl + C o Ctrl + Z
// o en otra terminal mandar con el comando kill las señales
    // kill -SIGINT <pid>
    // kill -SIGTSTP <pid>

// datos volatiles para el uso correcto del handler
volatile int sig_int=0;
volatile int sig_stp=0;

// funcion handler, para capturar las señales
// int sig: para saber que señal se ha capturado e incrementar 
// el correspondiente contador
void handler(int sig){
    if(sig==SIGINT) sig_int++;
    if(sig==SIGTSTP) sig_stp++;
}

int main(int argc, char** argv){

    // para poder usar kill desde otra terminal
    printf("PID: %d\n", (int) getpid());

    // señales bloquedas
    sigset_t block_set;
    // struct sigaction para capturas las señales SIGINT y SIGSTP
    struct sigaction sa;
    
    // crea un set vacio
    if(sigemptyset(&block_set)==-1) { perror("sigemptyset()"); exit(EXIT_FAILURE); }
    // añade la señal SIGINT Ctrl + C
    if(sigaddset(&block_set, SIGINT)==-1) { perror("sigaddset(SIGINT)"); exit(EXIT_FAILURE); }
    // añade la señal SIGTSTP Ctrl + Z
    if(sigaddset(&block_set, SIGTSTP)==-1) { perror("sigaddset(SIGTSTP)"); exit(EXIT_FAILURE); }
    
    // añardir la funcion
    sa.sa_handler=handler;
    sa.sa_mask=block_set;

   

    // añade la captura a las señales deseadas
    if(sigaction(SIGINT, &sa, NULL)==-1) { perror("sigaction(SIGINT)"); exit(EXIT_FAILURE); }
    if(sigaction(SIGTSTP, &sa, NULL)==-1) { perror("sigaction(SIGTSTP)"); exit(EXIT_FAILURE); }

    // bucle esperando a recibir las 10 señales
    while(sig_int+sig_stp<10);
    
    printf("\n10 señales recibidas: %d SIGINT y %d SIGTSTP\n",sig_int, sig_stp);


    

    return 0;
}