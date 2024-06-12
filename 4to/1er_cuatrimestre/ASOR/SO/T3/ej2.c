
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <unistd.h>
#include <sched.h>

// COMPILAR: gcc ej2.c -o ej2
// EJECUTAR: ./ej2

// TERMINA: normal

int main(int argc, char *argv[]) {
    pid_t pid;
    int sched_int;
    int max_prior, min_prior;
    
    
    pid=getpid(); // no da nunca error
  
  /*printf("%d\n",pid);
    sleep(10);*/

    sched_int=sched_getscheduler(pid); // tambien se puede usar 0
    if(sched_int==-1){
        perror("sched_getscheduler");
        exit(EXIT_FAILURE);
    }

    max_prior=sched_get_priority_max(sched_int);
    if(max_prior==-1){
        perror("sched_get_priority_max()");
        exit(EXIT_FAILURE);
    }
    min_prior=sched_get_priority_min(sched_int);
    if(min_prior==-1){
        perror("sched_get_priority_min()");
        exit(EXIT_FAILURE);
    }

    switch (sched_int) {
    case SCHED_OTHER:
        printf("the standard round-robin time-sharing policy\n");
        break;
    case SCHED_RR:
        printf("a round-robin policy\n");
    case SCHED_FIFO:
        printf("a first-in, first-out policy\n");
    default:
        break;
    }

    printf("Prioridades para la politica de planificacion.\n +\
            Maximo: %d\n +\
            Minimo: %d\n", max_prior, min_prior);

    return 0;
}