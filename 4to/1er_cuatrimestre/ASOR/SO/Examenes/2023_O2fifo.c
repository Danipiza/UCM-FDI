#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/select.h>
#include <unistd.h>

#define BUF_SIZE 256

int main(int argc, char** argv){
    // lee dos tuberias con nombre, previamente creadas "fifo1" y "fifo2"
    // multiplexacion 
    int fd1, fd2, fd_max, s_fd;
    fd_set rd_set;
    char buf[BUF_SIZE];
    ssize_t bytes_read;
    
    fd1=open("fifo1", O_RDONLY | O_NONBLOCK); 
    fd2=open("fifo2", O_RDONLY | O_NONBLOCK); 
    if(fd1==-1 | fd2==-1) { perror("fifo()"); exit(EXIT_FAILURE); }   
    
    fd_max=(fd1>fd2?fd1:fd2)+1;



    // no dice nada acerca de cerrar la conexion si no se recibe ningun mensaje
    // por lo que no es necesario poner struct timeval    
    while(1){
        FD_ZERO(&rd_set);
        FD_SET(fd1, &rd_set);
        FD_SET(fd2, &rd_set);
        
        s_fd=select(fd_max, &rd_set, NULL,NULL,NULL);
        if(s_fd==-1) { perror("select()"); exit(EXIT_FAILURE); }


        if(FD_ISSET(fd1,&rd_set)!=0){
            bytes_read=read(fd1,buf,BUF_SIZE);
            if(bytes_read==-1) {perror("fd1, read()"); exit(EXIT_FAILURE); }
            buf[bytes_read-1]='\0';
            printf("Leido desde fifo1: %s\n", buf);

            // abre de nuevo para el correcto funcionamiento
            /*if(close(fd1)==-1){ perror("close()"); exit(EXIT_FAILURE); }            
            fd1=open("fifo1", O_RDWR);    
            if(fd1==-1) { perror("fifo(fd1)"); exit(EXIT_FAILURE); }
            // no hace falta porque siempre da el descriptor de fichero con menor valor
            // por lo que al cerrar y abrir da el mismo
            fd_max=(fd1>fd2?fd1:fd2)+1; */
        }
        if(FD_ISSET(fd2,&rd_set)!=0){
            bytes_read=read(fd2,buf,BUF_SIZE);
            if(bytes_read==-1) {perror("fd2, read()"); exit(EXIT_FAILURE); }
            buf[bytes_read-1]='\0';
            printf("Leido desde fifo2: %s\n", buf);

            // abre de nuevo para el correcto funcionamiento
            /*if(close(fd2)==-1){ perror("close()"); exit(EXIT_FAILURE); }
            fd2=open("fifo2", O_RDWR);
            if(fd2==-1) { perror("fifo(fd2)"); exit(EXIT_FAILURE); }
            // no hace falta porque siempre da el descriptor de fichero con menor valor
            // por lo que al cerrar y abrir da el mismo
            fd_max=(fd1>fd2?fd1:fd2)+1;*/
        }

    }
 
    return 0;
}