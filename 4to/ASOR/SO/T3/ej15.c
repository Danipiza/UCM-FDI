#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

// COMPILAR: gcc ej15.c -o ej15
// EJECUTAR: ./ej15

// TERMINA: se escribe un mensaje por la terminal, 
// el padre le envia el mensaje al hijo y espera 1s para enviar todos los mensajes y finalizar
    

int main(int argc, char** argv){
    pid_t pid;
    char buf[256]; // memoria asignada.
    int p_h[2], h_p[2];
    
    if(pipe(p_h)==-1 || pipe(h_p)==-1){
        perror("pipe()");
        exit(EXIT_FAILURE);
    }

    pid=fork();
    if(pid==0){ // Hijo
        if(close(h_p[0])==-1 || close(p_h[1])==-1) { perror("HIJO, close()"); exit(EXIT_FAILURE); }
        
        // lee la tuberia p_h        
        ssize_t bytes_read=read(p_h[0],buf,sizeof(buf)-1); // como buf ya tiene asignada memoria no hace falta poner &buf.
        if(bytes_read==-1) { perror("HIJO, read()"); exit(EXIT_FAILURE); }
        buf[bytes_read]='\0';
        printf("HIJO, mensaje recibido del padre: %s", buf);
        sleep(1);
        // escribe por la salida estandar y espera 1s        
        // envia '1' al padre, escribiendo en h_p
        if(write(h_p[1], "1", 1)==-1) { perror("HIJO, write()"); exit(EXIT_FAILURE); }
        // escribe 10 mensajes
        int i=0;
        for(;i<10;i++){
            char msg[2];
            snprintf(msg, sizeof(msg), "%d", i);
            //printf("%s\n",msg);
            if(write(h_p[1], msg, 1)==-1) { perror("HIJO, write()"); exit(EXIT_FAILURE); }
        }
        // envia 'q' al padre para que finalice, escribiendo en h_p
        if(write(h_p[1], "q", 1)==-1) { perror("HIJO, write()"); exit(EXIT_FAILURE); }
        

    }
    else if(pid>0){ // Padre
        if(close(p_h[0])==-1 || close(h_p[1])==-1) { perror("PADRE, close()"); exit(EXIT_FAILURE); }
        // Lee de la entrada estandar       
        if(read(STDIN_FILENO, buf, 256)==-1) { perror("PADRE, read()"); exit(EXIT_FAILURE); }        
        // envia el mensaje al hijo, escribiendo en p_h
        if(write(p_h[1],buf,strlen(buf))==-1) { perror("PADRE, write()"); exit(EXIT_FAILURE); }
        // bloqueado hasta confirmacion del hijo en h_p        
        
        char* c; // si fuese char c; si hay que poner &c en read()
        do {            
            if(read(h_p[0], c, 1)==-1) { perror("PADRE, read()"); exit(EXIT_FAILURE); }        
            printf("%s\n",c);
        } while (strcmp(c,"q")!=0);
        printf("PADRE, finaliza\n");
    }
    else {
        perror("fork()");
        exit(EXIT_FAILURE);
    }

    return 0;
}