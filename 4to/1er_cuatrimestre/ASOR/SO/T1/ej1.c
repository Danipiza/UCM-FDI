#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

// COMPILAR: gcc ej1.c -o ej1
// EJECUTAR: ./ej1

// TERMINA: normal

int main(int argc, char** argv) {
    if(setuid(0)==-1){
        perror("setuid()");
        exit(EXIT_FAILURE);
    }
    
    return 0;
}
