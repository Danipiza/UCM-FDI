#include <sys/types.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#include <unistd.h>

// COMPILAR: gcc ej9.c -o ej9
// EJECUTAR: ./ej9

// TERMINA: normal

int main(int argc, char** argv) {        
    printf("uid=%d\t euid=%d\n",getuid(),geteuid());    

    return 0;
}
