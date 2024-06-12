#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>

// COMPILAR: gcc ej10.c -o ej10
// EJECUTAR: ./ej10

// TERMINA: normal

int main(int argc, char** argv) {        
    struct passwd *pswd=getpwuid(getuid());
    if(pswd==NULL){ perror("getpwuid()"); exit(EXIT_FAILURE); }
    
    printf("uid=%d\t euid=%d\tusuario=%s\thome dir:%s\nDescripcion de usuario: %s\n",(int)getuid(),(int)geteuid(), pswd->pw_name,pswd->pw_dir,pswd->pw_gecos);    


    return 0;
}
