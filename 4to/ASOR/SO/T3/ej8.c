#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

// COMPILAR: gcc ej8.c -o ej8
// EJECUTAR: ./ej8 <comando>

// TERMINA: normal

int main(int argc, char** argv) {
    if(argc<2){
        fprintf(stderr, "Usage: %s argv[0]+1\n", argv[0]);
        exit(EXIT_FAILURE);
    } 
    pid_t pid=fork();
    if(pid==0){ // Hijo
        printf("Ejecutando el proceso hijo...\n");
        int chd=chdir("/tmp");
        if(chd==-1){
            perror("chdir()");
            exit(EXIT_FAILURE);    
        }

        int fd0=open("/dev/daemon.out", O_CREAT | O_RDWR, 00666);
        int fd1=open("/dev/daemon.err", O_CREAT | O_RDWR, 00666);
        int fd2=open("/dev/null", O_CREAT | O_RDWR, 00666);
        if (fd0==-1||fd1==-1||fd2==-1) {
            perror("open()");
            exit(EXIT_FAILURE);
        }
        int dp0=dup2(fd0, STDOUT_FILENO); // La salida estandar al fichero /tmp/daemon.out.
        int dp1=dup2(fd1, STDERR_FILENO); // La salida de error estándar al fichero /tmp/daemon.err.
        int dp2=dup2(fd2, STDIN_FILENO); // La entrada estandar a /dev/null
        if (dp0==-1||dp1==-1||dp2==-1){
            perror("dup2()");
            exit(EXIT_FAILURE);
        }
        int exc=execvp(argv[1], argv+1);
        if(exc==-1){
            perror("execvp()");
            exit(EXIT_FAILURE);
        }




    }
    else if(pid>0){ // Padre
        printf("Ejecutando el proceso padre...\n");
    }
    else {
        perror("fork()");
        exit(EXIT_FAILURE);
    }
}
