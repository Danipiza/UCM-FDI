#include <sys/types.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#include <unistd.h>

// COMPILAR: gcc ej7.c -o ej7
// EJECUTAR: ./ej7

// TERMINA: normal

int main(int argc, char** argv) {    
    long link_max, path_max, file_max;
    
    link_max=pathconf("/",_PC_LINK_MAX);
    if(link_max==-1) { perror("pathconf(_PC_LINK_MAX)"), exit(EXIT_FAILURE); }
    path_max=pathconf("/",_PC_PATH_MAX);
    if(path_max==-1) { perror("pathconf(_PC_PATH_MAX)"), exit(EXIT_FAILURE); }
    file_max=pathconf("/",_PC_NAME_MAX);
    if(file_max==-1) { perror("pathconf(_PC_NAME_MAX)"), exit(EXIT_FAILURE); }
    
    
    printf("Numero maximo de enlaces: %ld\n", link_max);
    printf("Tam maximo de una ruta: %ld\n", path_max);
    printf("Longitud maxima de nombre de fichero: %ld\n", file_max);

    
    return 0;
}
