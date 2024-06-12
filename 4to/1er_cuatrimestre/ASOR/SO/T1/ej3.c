#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

// COMPILAR: gcc ej3.c -o ej3
// EJECUTAR: ./ej3

// TERMINA: normal

int main(int argc, char** argv) {
    
    for(int i=0;i<=255;i++){
        printf("Codigo de error %d: %s \n", i, strerror(i));
    } 
       

    
    return 0;
}
