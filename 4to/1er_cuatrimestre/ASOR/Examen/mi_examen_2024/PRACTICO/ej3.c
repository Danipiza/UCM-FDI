// PIZARRO GALLEGO, DANIEL
// 11869584C

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <time.h>
#include <sys/select.h>

#define BUF_SIZE 512

// COMPILAR: gcc ej3.c -o ej3
// EJECUTAR: 
// ejemplo tcp: ./ej3 :: 8080
// ejemplo udp: ./ej3 127.0.0.1 8080

// POR TERMINAL DEL EJECUTABLE: se puede escribir y devuelve la hora

// EN OTRA TERMINAL, y con ejecutable activo
// nc -u ::1 8080
// nc -u 0.0.0.0 8080


int main(int argc, char *argv[]) {
    if (argc!=3) {
        fprintf(stderr, "Usage: %s <host> <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    struct addrinfo hints;
    struct addrinfo *ai, *rp;
    int sfd, s;
    struct sockaddr_storage sa;
    socklen_t salen;
    ssize_t bytes_read;
    char query[BUF_SIZE];
    char buf[BUF_SIZE];
    

    // datos del socket
    memset(&hints, 0, sizeof(hints));
    hints.ai_family=AF_UNSPEC;    // IPv4 o IPv6
    hints.ai_socktype=SOCK_DGRAM; // UDP 
    hints.ai_flags=AI_PASSIVE;    /* For wildcard IP address */
    hints.ai_protocol=0;          /* Any protocol */

    // direccion del cliente, junto con el puerto
    s=getaddrinfo(argv[1], argv[2], &hints, &ai);
    if (s!=0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        exit(EXIT_FAILURE);
    }

    /* getaddrinfo() returns a list of address structures.
        Try each address until we successfully bind(2).
        If socket(2) (or bind(2)) fails, we (close the socket
        and) try the next address. */    
    for (rp=ai; rp!=NULL; rp=rp->ai_next) {
        // lee el socket
        sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        
        if (sfd==-1) continue;

        // intenta enlazar
        if (bind(sfd, rp->ai_addr, rp->ai_addrlen)==0)
            break; // exito al enlazar, termina el bucle

        close(sfd);
    }

    freeaddrinfo(ai); // ya no se necesita, se puede liberar

    if (rp==NULL) {  // la direcion no ha tenido exito, se termina la ejecucion
        fprintf(stderr, "No se puedo enlazar\n");
        exit(EXIT_FAILURE);
    }
    
    // datos del cliente
    char host[NI_MAXHOST]; // direccion
    char service[NI_MAXSERV]; // puerto

    int fd_max, sel;  // descriptores, junto con la variable para select  
    fd_set set;
    fd_max=(STDIN_FILENO>sfd?STDIN_FILENO:sfd)+1;
    // se tiene que escoger el descriptor de fichero mas grande y sumar 1
    // no hace falta, porque siempre va a ser sfd, debido a que la entrada estandar es 0.
    
    // no hace falta poner cuanto tiempo puede estar sin recibir datos
    //struct timeval *timeout;
    //timeout->tv_sec=10; // 10segundos sin recibir, se termina
    //timeout->tv_usec=0;

    // variables para el calculo del tiempo actual
    time_t t_epoch;
    struct tm* act_time;
    while(1) {
        // en cada iteracion se reinicia el conjunto
        FD_ZERO(&set); // elimina todos los descriptores del conjutno
        FD_SET(STDIN_FILENO, &set); // añade la entrada estandar
        FD_SET(sfd, &set); // añade el socket
        
        // solo es de lectura.
        // escritura, excepciones y tiempo se instancian como NULL
        sel=select(fd_max, &set, NULL, NULL, NULL);
        if(sel==-1){ perror("select()"); exit(EXIT_FAILURE); }

        // lee por multiplexacion usando select y cuando detecta un descriptor se desbloquea 
        // y sigue la ejecucion

        // calcula el tiempo actual, usando time() para calcular el tiempo en epoch
        // para luego calcular el tiempo UTC usando gmtime()
        if(time(&t_epoch)==-1) { perror("time()"); exit(EXIT_FAILURE); }
        act_time=gmtime(&t_epoch);
        if((time_t) act_time==-1) { perror("gmtime()"); exit(EXIT_FAILURE); }
                
        // si select ha leido por la terminal, imprime el tiempo actual por la salida estandar
        if(FD_ISSET(STDIN_FILENO, &set)){
            // lee de la entrada estandar
            if(read(STDIN_FILENO, buf, BUF_SIZE)==-1) { perror("read()"); exit(EXIT_FAILURE); }
            // imprime por la salida estandar
            printf("%d:%d:%d\n", act_time->tm_hour, act_time->tm_min, act_time->tm_sec);
        }
        
        // si select ha leido un mensaje del socket, imprime la direccion del cliente
        // y le envia el tiempo actual
        if(FD_ISSET(sfd, &set)){
            salen=sizeof(sa);
            bytes_read=recvfrom(sfd, query, BUF_SIZE, 0, (struct sockaddr *) &sa, &salen);
            if (bytes_read==-1) {
                perror("recvfrom()");
                continue; // solicitud ignorada por fallo
            }
            // no hace falta porque no se escribe el mensaje del cliente
            // query[bytes_read-1]='\0';
            // funcion de biblioteca, no registra errno
            s=getnameinfo((struct sockaddr *) &sa,
                            salen, host, NI_MAXHOST,
                            service, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);
            // NI_NUMERICHOST | NI_NUMERICSERV. 
            // sirve para traducr y tener almacenados la direccion y puerto correctamente
            
            if (s!=0) fprintf(stderr, "getnameinfo: %s\n", gai_strerror(s));
            
            
            printf("Mensaje de %s:%s\n", host, service);            
            // guarda en el char[] la fecha actual para enviarsela al cliente
            snprintf(buf, BUF_SIZE, "%d:%d:%d\n", act_time->tm_hour, act_time->tm_min, act_time->tm_sec);
                    
            // envia el tiempo actual al cliente    
            if (sendto(sfd, buf, strlen(buf), 0,
                        (struct sockaddr *) &sa,
                        salen) == -1){ // errno
                perror("sendto()");
                exit(EXIT_FAILURE);
            }
        }
            
        
    }

    return 0;
}