#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// COMPILAR: gcc ej12.c -o ej12
// EJECUTAR: ./ej12 <file_path>

// TERMINA: normal

int main(int argc, char** argv){
    if(argc!=2){
        fprintf(stderr, "Usage: %s <file_path>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int fd=open(argv[1], O_WRONLY | O_CREAT | O_TRUNC);
    if(fd==-1) {perror("open()"); exit(EXIT_FAILURE); }

    

    if(dup2(fd, STDOUT_FILENO)==-1) { 
        perror("dup2()"); 
        close(fd);
        exit(EXIT_FAILURE); 
    }
    close(fd);

    printf("Hola desde printf\n");

    return 0;
}