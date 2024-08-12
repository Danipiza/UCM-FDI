#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#include <unistd.h>

// COMPILAR: gcc ej6.c -o ej6
// EJECUTAR: ./ej6

// TERMINA: normal

int main(int argc, char** argv) {    
    long arg_max, chld_max, file_max;
    
    arg_max=sysconf(_SC_ARG_MAX);
    if(arg_max==-1) { perror("sysconf(_SC_ARG_MAX)"), exit(EXIT_FAILURE); }
    chld_max=sysconf(_SC_CHILD_MAX);
    if(chld_max==-1) { perror("sysconf(_SC_CHILD_MAX)"), exit(EXIT_FAILURE); }
    file_max=sysconf(_SC_OPEN_MAX);
    if(file_max==-1) { perror("sysconf(_SC_OPEN_MAX)"), exit(EXIT_FAILURE); }

    //la longitud máxima de los argumentos, el número máximo de hijos y el número máximo de ficheros abiertos.
    printf("Longitud maxima de los argumentos: %ld\n", arg_max);
    printf("Numero maximo de hijos: %ld\n", chld_max);
    printf("Numero maximo de ficheros abiertos: %ld\n", file_max);
    

    
    return 0;
}
