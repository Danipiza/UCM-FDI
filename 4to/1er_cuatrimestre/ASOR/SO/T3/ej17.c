#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#include <sys/stat.h>
#include <fcntl.h>

// COMPILAR: gcc ej17.c -o ej17
// EJECUTAR: ./ej17 <mensaje>

// OTRA TERMINAL: cat tub1

// TERMINA: normal

// mkfifo tub1 // para crear la tuberia

    

int main(int argc, char** argv){
    if(argc!=2){
        fprintf(stderr, "Usage: %s <mensaje>\n",argv[0]);
        exit(EXIT_FAILURE);
    }
    int fd;
    char* pipe_name={"tub1"};
    // abra la tuberia en modo solo escritura
    fd=open(pipe_name, O_WRONLY);
    if(fd==-1) { perror("open()"); exit(EXIT_FAILURE); }
    // escriba en ella el primer argumento del programa
    char msg[80];
    int len=snprintf(msg,sizeof(msg),"%s\n",argv[1]);
    if(len<0) { printf("error en snprintf()\n"); exit(EXIT_FAILURE); }

    if(write(fd, msg, len)==-1) { perror("write()"); exit(EXIT_FAILURE); }
    
    close(fd);
    return 0;
}