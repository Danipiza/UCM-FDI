#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#include <sys/stat.h>
#include <fcntl.h>

#include <sys/select.h>

// COMPILAR: gcc ej18.c -o ej18
// EJECUTAR: ./ej18

// OTRA TERMINAL: echo <mensaje> > tub1

// TERMINA: cuando pasen 5s sin recibir un mensaje de alguna tuberia

// mkfifo tub2 // para crear la tuberia
    
#define BUFF_SIZE 256

int main(int argc, char** argv){
    // programa espera a tener datos listos para leer de dos tuberias
    // tiene que mostrar lo que lee y de donde lo lee
    int fd1, fd2, max_fds, sfd;
    char buf[BUFF_SIZE];
    ssize_t bytes_read;
    fd_set set;

    fd1=open("tub1", O_RDONLY | O_NONBLOCK);
    fd2=open("tub2", O_RDONLY | O_NONBLOCK);
    if(fd1==-1 || fd2==-1){ perror("open()"); exit(EXIT_FAILURE); }
    max_fds=(fd1>=fd2?fd1:fd2)+1;

    

    while(1){  
        // tiene que estar dentro por que sino no se resetea el temporizador
        struct timeval tm; 
        tm.tv_sec=5;
        tm.tv_usec=0;             

        FD_ZERO(&set);
        FD_SET(fd1, &set);
        FD_SET(fd2, &set);

        sfd=select(max_fds, &set, NULL, NULL, &tm);

        if(sfd==-1) { perror("select()"); exit(EXIT_FAILURE); }
        else if(sfd==0){
            printf("No recibe mensaje de ninguna tuberia en 5s. Terminando ejecucion...\n");
            break;
        }

        if(FD_ISSET(fd1, &set)){
            bytes_read=read(fd1, buf, BUFF_SIZE-1);
            if(bytes_read==-1) { perror("tub1, read()"); exit(EXIT_FAILURE); }
            buf[bytes_read]='\0'; // fin del string
            
            printf("Tuberia 1, mensaje: %s", buf);
            
            close(fd1);
            fd1=open("tub1", O_RDONLY | O_NONBLOCK);
            if(fd1==-1) { perror("tub1, open()"); exit(EXIT_FAILURE); }
        }
        if(FD_ISSET(fd2, &set)){
            bytes_read=read(fd2, buf, BUFF_SIZE-1);
            if(bytes_read==-1) { perror("tub2, read()"); exit(EXIT_FAILURE); }
            buf[bytes_read]='\0'; // fin del string
            
            printf("Tuberia 2, mensaje: %s", buf);
            
            close(fd2);
            fd2=open("tub2", O_RDONLY | O_NONBLOCK);
            if(fd2==-1) { perror("tub2, open()"); exit(EXIT_FAILURE); }
        }


    }



    return 0;
}