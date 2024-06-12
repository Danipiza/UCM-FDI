#include <sys/types.h>
#include <sys/stat.h>
#include <stdint.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sysmacros.h>

// COMPILAR: gcc ej9.c -o ej9
// EJECUTAR: ./ej9 <file_path>

// TERMINA: normal


int main(int argc, char** argv){
    if(argc!=2){
        fprintf(stderr, "Usage: %s <file_path>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    struct stat file_stat;
    if(stat(argv[1], &file_stat)==-1){ perror("stat()"); exit(EXIT_FAILURE); }


    // major minor 
    printf("major, minor: [%jx,%jx] asociado al dispositivo\n",
                   (uintmax_t) major(file_stat.st_dev),
                   (uintmax_t) minor(file_stat.st_dev));
    // numero de inodo
    printf("Numero de Inodo: %d\n", file_stat.st_ino);
    // tipo de fichero
    printf("Tipo de fichero: ");
    switch (file_stat.st_mode & S_IFMT) {
        case S_IFBLK:  printf("block device\n");            break;
        case S_IFCHR:  printf("character device\n");        break;
        case S_IFDIR:  printf("directory\n");               break;
        case S_IFIFO:  printf("FIFO/pipe\n");               break;
        case S_IFLNK:  printf("symlink\n");                 break;
        case S_IFREG:  printf("regular file\n");            break;
        case S_IFSOCK: printf("socket\n");                  break;
        default:       printf("unknown?\n");                break;
    }
    // la hora en la que se accdeio al fichero por ultima vez
    printf("Ultimo acceso al fichero: %s", ctime(&file_stat.st_atime));


    return 0;
}