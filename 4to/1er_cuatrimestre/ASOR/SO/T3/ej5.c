#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

#define BUFF_MAX 256

// COMPILAR: gcc ej5.c -o ej5
// EJECUTAR: ./ej5

// TERMINA: normal

int main(int argc, char** argv){
    pid_t pid, ppid, pgid, sid;
    int max_files;
    
    

    pid=getpid();
    ppid=getppid();
    pgid=getpgid(pid);
    if(sid==-1){
        perror("getpgid()");
        exit(EXIT_FAILURE);
    }
    sid=getsid(pid);
    if(sid==-1){
        perror("getsid()");
        exit(EXIT_FAILURE);
    }

    //  OPEN_MAX - _SC_OPEN_MAX
    max_files=sysconf(_SC_OPEN_MAX);
    if(errno==EINVAL){
         perror("sysconf()");
         exit(EXIT_FAILURE);
    }    

    char buffer[BUFF_MAX];
    char *dir = getcwd(buffer, sizeof(buffer));
    if(dir==NULL){
        perror("getcwd");
        exit(EXIT_FAILURE);
    }

    printf("PID: %d\tPPID: %d\tPGID: %d\tSID: %d\nMAX FILES: %d\ndir: %s\n", pid, ppid, pgid, sid, max_files, dir);


    return 0;
}