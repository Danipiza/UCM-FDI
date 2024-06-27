#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/select.h>
#include <unistd.h>

#define BUF_SIZE 256

// COMPILACION: gcc 2021_Ofifo.c -o multi_pipe

// EJECUCION:
// TERMINAL 1: ./multi_pipe
//             Mensaje desde la terminal

// TERMINAL 2: echo Mensaje desde la tuberia: fifo1 > fifo1

int main(int argc, char** argv){
    // lee una tuberia con nombre, previamente creada "fifo1" y desde la terminal
    // multiplexacion 
    int fd1, fd_max, s_fd;
    fd_set rd_set;
    char buf[BUF_SIZE];
    ssize_t bytes_read;
    
    // abre la tuberia
    fd1=open("fifo1", O_RDONLY | O_NONBLOCK);   
    if(fd1==-1) { perror("fifo()"); exit(EXIT_FAILURE); }   
    
    // solo hay un descriptor abierto (fd1)
    fd_max=fd1+1;


    // no dice nada acerca de cerrar la conexion si no se recibe ningun mensaje
    // por lo que no es necesario poner struct timeval, para finalizar la ejecucion
    /*struct timeval tv;
    tv.tv_sec=10; // 10 segundos sin recibir mensaje, termina la ejecucion
    tv.tv_usec=0;*/
    while(1){
        FD_ZERO(&rd_set);
        FD_SET(fd1, &rd_set);
        FD_SET(STDIN_FILENO, &rd_set);
        
        s_fd=select(fd_max, &rd_set, NULL,NULL,NULL);
        if(s_fd==-1) { perror("select()"); exit(EXIT_FAILURE); }


        if(FD_ISSET(fd1,&rd_set)!=0){
            bytes_read=read(fd1,buf,BUF_SIZE);
            if(bytes_read==-1) {perror("fd1, read()"); exit(EXIT_FAILURE); }                     
            
            buf[bytes_read-1]='\0';
            printf("Leido desde la tuberia: %s\n", buf);

            printf("Fin de fichero en la tuberia. Reiniciando...\n");
            close(fd1);
            
            fd1=open("fifo1", O_RDONLY | O_NONBLOCK);  
            if (fd1==-1) { perror("open()"); exit(EXIT_FAILURE); }
        }
        if(FD_ISSET(STDIN_FILENO,&rd_set)!=0){
            bytes_read=read(STDIN_FILENO,buf,BUF_SIZE);
            if(bytes_read==-1) {perror("fd2, read()"); exit(EXIT_FAILURE); }
            buf[bytes_read-1]='\0';
            
            printf("Leido desde la terminal: %s\n", buf);
        }

    }
 
    return 0;
}