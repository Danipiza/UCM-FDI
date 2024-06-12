#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

#define BUF_SIZE 1024

// IMPORTANTE: si se crean otros ficheros, tener en cuenta que con open, si ya existe no cambian sus permisos

// COMPILAR: gcc ej17.c -o ej17
// EJECUTAR: ./ej17

// TERMINA: normal



int main(int argc, char** argv){ 
    char* dir_name="ej17Dir";   
    // crea un directorio con varios ficheros, si existe se controla el error EEXIST.
    char* files_names[]={"ej17Dir/file1.txt","ej17Dir/file2.txt","ej17Dir/file3.c","ej17Dir/file1_sym","ej17Dir/file2_hard", "ej17Dir/directorio"};
    if(mkdir(dir_name, 0766)==-1 && errno!=EEXIST) { perror("mkdir()"), exit(EXIT_FAILURE); }
    if(mkdir(files_names[5], 0666)==-1 && errno!=EEXIST) { perror("mkdir()"), exit(EXIT_FAILURE); }
    if(open(files_names[0], O_CREAT, 0766)==-1 || 
       open(files_names[1], O_CREAT, 0666)==-1 ||
       open(files_names[2], O_CREAT, 0766)==-1){
        perror("open()");
        exit(EXIT_FAILURE);
    }

    if(link(files_names[1],files_names[4])==-1 && errno!=EEXIST) { perror("link()"), exit(EXIT_FAILURE); }
    if(symlink(files_names[0],files_names[3])==-1 && errno!=EEXIST) { perror("symlink()"), exit(EXIT_FAILURE); }
    
    if(chdir(dir_name)==-1) { perror("chdir"); exit(EXIT_FAILURE); }
    printf("Si es un fichero regular y tiene permiso de ejecución para usuario, grupo u otros, escribirá el carácter '*' después del nombre\n");
    printf("Si es un directorio, escribirá el carácter '/' después del nombre\n");
    printf("Si es un enlace simbólico, escribirá \"->\" y el nombre del fichero enlazado obtenido con readlink(2).\n\n");
    //DIR *opendir(const char *name);
    printf("Archivos en %s/:\n",dir_name);
    DIR* dir=opendir(".");
    struct dirent* file; 
    char buf[BUF_SIZE];
    ssize_t bytes_read;
    struct stat file_stat;
    while((file=readdir(dir))!=NULL){
        printf("%s",file->d_name);
        switch (file->d_type){
        case DT_REG:            
            if(stat(file->d_name, &file_stat)==-1) perror("lstat");
            
            if(file_stat.st_mode & S_IXUSR || 
               file_stat.st_mode & S_IXGRP || 
               file_stat.st_mode & S_IXOTH){
                printf("*");
            }
            
            break;
        case DT_LNK:
            bytes_read=readlink(file->d_name, buf, BUF_SIZE);
            if(bytes_read==-1) perror("readlink()");
            buf[bytes_read]='\0';
            printf("-> %s",buf);
            break;
        case DT_DIR:
            printf("/");
            break;

        default:            
            break;
        }

        printf("\n");
        //file=readdir(dir);
    }

    return 0;
}