#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

// COMPILAR: gcc ej2.c -o ej2
// EJECUTAR: ./ej2

// TERMINA: normal

int main(int argc, char** argv) {
    int r_uid=setuid(-1);
    if(r_uid!=0){
        printf("Codigo de error %d: %s \n", errno, strerror(errno));
        exit(EXIT_FAILURE);
    }   

    
    return 0;
}
