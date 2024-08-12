#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

// COMPILAR: gcc ej12.c -o ej12
// EJECUTAR: ./ej12

// TERMINA: normal

int main(int argc, char** argv) {        
    time_t tm;
    
    tm=time(NULL); // equivalente a usar time(&tm);
    if((int) tm==-1) { perror("time()"), exit(EXIT_FAILURE); }

    printf("%ds (Epoch)\n",tm);

    return 0;
}
