#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

// COMPILAR: gcc ej14.c -o ej14
// EJECUTAR: ./ej14

// TERMINA: normal

int main(int argc, char** argv) {            
    time_t epoch_tm;
    struct tm* tm;

    epoch_tm=time(NULL);    
    if((int) epoch_tm==-1) { perror("localtime()"); exit(EXIT_FAILURE); }
    
    tm=localtime(&epoch_tm);
    if(tm==NULL) { perror("localtime()"); exit(EXIT_FAILURE); }

    printf("Año: %d\n",1900+tm->tm_year);

    return 0;
}
