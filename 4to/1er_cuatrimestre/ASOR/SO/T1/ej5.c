#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/utsname.h>

// COMPILAR: gcc ej5.c -o ej5
// EJECUTAR: ./ej5

// TERMINA: normal

int main(int argc, char** argv) {
    struct utsname so_info;

    if(uname(&so_info)==-1) { perror("uname()"); exit(EXIT_FAILURE); }

    printf("Nombre dek SO: %s\n",so_info.sysname);
    printf("Nombre dentro de alguna red definida: %s\n",so_info.nodename);
    printf("Fecha de lanzamiento del SO: %s\n",so_info.release);
    printf("Version del SO: %s\n",so_info.version);
    printf("ID del Hardware: %s\n",so_info.machine);
    

    
    return 0;
}
