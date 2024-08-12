#include <sys/types.h>
#include <sys/stat.h>
#include <stdint.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sysmacros.h>
#include <unistd.h>

// COMPILAR: gcc ej11.c -o ej11
// EJECUTAR: ./ej11 <file_path>

// TERMINA: normal

#define BUF_SIZE 80
int main(int argc, char **argv){  
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file_path>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    struct stat file_stat;
    if (stat(argv[1], &file_stat)==-1) { perror("lstat"); exit(EXIT_FAILURE); }

    char symfile[BUF_SIZE]; 
    char hardfile[BUF_SIZE];

   
    if(snprintf(symfile,BUF_SIZE, "%s.sym",argv[1])<0) { fprintf(stderr, "SYM, snprintf()"); exit(EXIT_FAILURE); }
    if(snprintf(hardfile,BUF_SIZE, "%s.hard",argv[1])<0) { fprintf(stderr, "HARD, snprintf()"); exit(EXIT_FAILURE); }
    // si es un fichero regular crea enlace simbolico y rigido
    if ((file_stat.st_mode & S_IFMT)==S_IFREG){
        printf("ENTRA\n");
        if(link(argv[1], hardfile)==-1) { perror("link()"); exit(EXIT_FAILURE); }
        if(symlink(argv[1], symfile)==-1) { perror("symlink()"); exit(EXIT_FAILURE); }
    }    

    return 0;
}