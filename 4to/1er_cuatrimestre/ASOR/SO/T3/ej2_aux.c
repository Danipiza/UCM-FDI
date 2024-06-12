
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <unistd.h>
#include <sched.h>
#include <sys/wait.h>

// COMPILAR: gcc ej2_aux.c -o ej2_aux
// EJECUTAR: ./ej2_aux

// TERMINA: normal

int main(int argc, char *argv[]) {
    pid_t pid;
    int sched_int;
    int max_prior, min_prior;

    pid=fork();
    if (pid==0){ // Hijo
        struct sched_param params;
        params.sched_priority=12;
        
        // cambia la politica del padre a FIFO, con prioridad 12
        int s_sched=sched_setscheduler(getppid(), SCHED_FIFO, &params);
        if(s_sched==-1){
            perror("sched_setscheduler()");
            exit(EXIT_FAILURE);
        }
        printf("El hijo modifico correctamente la politica de su padre.\n");
        exit(EXIT_SUCCESS);
    }
    else if(pid>0) { // Padre
        int wstatus;
        waitpid(pid, &wstatus, 0); // espera a que termine su hijo hijo    
     // SIMILARES
     // waitpid(-1,&wstatus,0); 
     // wait(&wstatus);    
        sched_int=sched_getscheduler(getpid()); // tambien se puede usar 0
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
    }
    else { // Error
        perror("fork()");
        exit(EXIT_FAILURE);
    }
       

    return 0;
}