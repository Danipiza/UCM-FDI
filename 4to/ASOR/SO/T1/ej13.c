#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>

// COMPILAR: gcc ej13.c -o ej13
// EJECUTAR: ./ej13

// TERMINA: normal (cuando termina el bucle)

int main(int argc, char** argv) {        
    struct timeval tv_ini, tv_fin;
    int i=0, val=0;
    if(gettimeofday(&tv_ini,NULL)==-1) { perror("INI, gettimeofday()"), exit(EXIT_FAILURE); }
    for(;i<1000000;i++){
        val++;
    }
    if(gettimeofday(&tv_fin,NULL)==-1) { perror("FIN, gettimeofday()"), exit(EXIT_FAILURE); }

    printf("Tiempo que tarda el bucle en microsegundos: %d\n", (int) (tv_fin.tv_usec-tv_ini.tv_usec));

    return 0;
}
