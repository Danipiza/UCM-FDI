#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>

// COMPILAR: gcc ej7_exc.c -o ej7_exc
// EJECUTAR: ./ej7_exc <comando>

// TERMINA: normal, ejecutando el comando

int main(int argc, char** argv){
    if(argc<2){
        fprintf(stderr, "Usage: %s argv[0]+1\n", argv[0]);
        exit(EXIT_FAILURE);
    }    
    int exc=execvp(argv[1], argv+1);
    if(exc==-1){
        perror("execvp()");
        exit(EXIT_FAILURE);
    }
    // no se imprime porque exec termina el proceso por el comando shell, 
    // hay que controlarlo con un fork() y ejecutarlo en el hijo
    printf("%d: El comando termino de ejecutarse\n", getpid());

    return 0;
}