#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

// COMPILAR: gcc ej7.c -o ej7
// EJECUTAR: ./ej7

// TERMINA: normal

int main(int argc, char** argv){
    char* file="ej7.txt";

    umask(0027); // nunca falla

    int fd=open(file, O_CREAT, 0645);
    if(fd==-1) { perror("open()"); exit(EXIT_FAILURE); }

    struct stat file_stat;

    if (fstat(fd, &file_stat)==-1) { perror("stat"); exit(EXIT_FAILURE); }

    printf("File permissions for %s: ", file);
    printf("-");    
    printf((file_stat.st_mode & S_IRUSR) ? "r":"-");
    printf((file_stat.st_mode & S_IWUSR) ? "w":"-");
    printf((file_stat.st_mode & S_IXUSR) ? "x":"-");
    printf((file_stat.st_mode & S_IRGRP) ? "r":"-");
    printf((file_stat.st_mode & S_IWGRP) ? "w":"-");
    printf((file_stat.st_mode & S_IXGRP) ? "x":"-");
    printf((file_stat.st_mode & S_IROTH) ? "r":"-");
    printf((file_stat.st_mode & S_IWOTH) ? "w":"-");
    printf((file_stat.st_mode & S_IXOTH) ? "x":"-");
    printf("\n");


    return 0;
}