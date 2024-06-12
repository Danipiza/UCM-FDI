#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

// COMPILAR: gcc ej15.c -o ej15
// EJECUTAR: ./ej15

// TERMINA: normal

#define BUF_SIZE 512

int main(int argc, char** argv) {            
    char date[BUF_SIZE];
    time_t epoch_tm;
    struct tm* tm;        
    
    epoch_tm=time(NULL);    
    if((int) epoch_tm==-1) { perror("localtime()"); exit(EXIT_FAILURE); }
    
    tm=localtime(&epoch_tm);
    if(tm==NULL) { perror("localtime()"); exit(EXIT_FAILURE); }

    // %a: dia de la semana %a
    // %d: dia numerico (0-31)
    // %T: <horas>:<minutos>:<segundos>
    // %Y: año
    


    ssize_t s=strftime(date, BUF_SIZE, "%a\t%d %T CET %Y", tm);
    if(s==0) { perror("strftime()"); exit(EXIT_FAILURE); }
    printf("%s\n",date);
    

    return 0;
}
