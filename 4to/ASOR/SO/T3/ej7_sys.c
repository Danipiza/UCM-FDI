#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>

// COMPILAR: gcc ej7_sys.c -o ej7_sys
// EJECUTAR: ./ej7_sys

// TERMINA: normal

int main(int argc, char** argv){

    int sys=system("ls"); // el hijo ejecuta el comando
    if(sys==-1){
        perror("system()");
        exit(EXIT_FAILURE);
    }
    // el padre podra imprimir la cadena
    printf("%d: El comando termino de ejecutarse\n", getpid());

    return 0;
}