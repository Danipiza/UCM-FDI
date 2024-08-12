#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>

#include <time.h>

#define BUF_SIZE 500
// CUIDADO CON UTLIZAR LOS PUERTOS
// si no se puede bindear utiliza otro hasta que pase el tiempo de keepalive

// COMPILAR: gcc ej2.c -o ej2
// EJECUTAR: ./ej2 <host> <puerto>
// ejemplo: ./ej2 :: 8080 

// TERMINAL: nc -u <host> <puerto>
// ejemplo: nc -u ::1 8080
// ejemplo: nc -u 127.0.0.1 8080

// TERMINA: cuando el cliente envia 'q'



int main(int argc, char** argv){
    if(argc!=3){
        fprintf(stderr, "Usage: %s <host> <puerto>\n",argv[0]);
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
    int fin=0;

    // direcciones de cualquier formato
    // direcciones IPv4 e IPv6
    memset(&hints, 0, sizeof(hints));
    hints.ai_family=AF_UNSPEC;    /* Allow IPv4 or IPv6 */
    hints.ai_socktype=SOCK_DGRAM; /* Datagram socket */
    hints.ai_flags=AI_PASSIVE;    /* For wildcard IP address */

    s=getaddrinfo(argv[1], argv[2], &hints, &ai);
    if (s!=0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        exit(EXIT_FAILURE);
    }

    for (rp=ai; rp!=NULL; rp=rp->ai_next) {
        sfd=socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (sfd==-1) continue;

        if (bind(sfd, rp->ai_addr, rp->ai_addrlen)==0)
            break;                  /* Success */

        close(sfd);
    }
    freeaddrinfo(ai);           /* No longer needed */

    if (rp==NULL) {               /* No address succeeded */
        fprintf(stderr, "Could not bind\n");
        exit(EXIT_FAILURE);
    }

    char host[NI_MAXHOST];
    char service[NI_MAXSERV];
    // el servidor recibe un caracter: 't': hora, 'd': fecha, 'q': termina el proceso
    // en cada mensaje el servidor tiene que imprimir el nombre y puerto del cliente
    time_t tm;
    struct tm *tiempo;
    while(1){
        salen=sizeof(sa);
        bytes_read=recvfrom(sfd, query, BUF_SIZE-1, 0, (struct sockaddr *) &sa, &salen);
        if (bytes_read == -1) continue; /* Ignore failed request */
        query[bytes_read-1]='\0';
        
        s=getnameinfo((struct sockaddr *) &sa, salen, 
                        host, NI_MAXHOST,
                        service, NI_MAXSERV, 
                        NI_NUMERICHOST | NI_NUMERICSERV);
        if (s!=0) {
            fprintf(stderr, "getnameinfo: %s\n", gai_strerror(s));
            continue;
        }
        printf("Cliente (%s:%s)\tEnvia: %s\n", host, service, query);
        
        tm=time(NULL);       
        tiempo=gmtime(&tm);
        if(strcmp(query,"t")==0){   
            snprintf(buf, sizeof(buf), "%02d:%02d:%02d\n",
                tiempo->tm_hour, tiempo->tm_min, tiempo->tm_sec);                     
        }
        else if(strcmp(query, "d")==0){ 
            snprintf(buf, sizeof(buf), "%04d-%02d-%02d\n",
                tiempo->tm_year + 1900, tiempo->tm_mon + 1, tiempo->tm_mday);
        }
        else if(strcmp(query, "q")==0){ 
            printf("Terminando la ejecucion...\n");
            snprintf(buf, sizeof(buf), "Terminando la ejecucion...\n");
            fin=1;
        }
        else snprintf(buf, sizeof(buf), "Comando no soportado\n");

        if (sendto(sfd, buf, strlen(buf), 0,
                           (struct sockaddr *) &sa,
                           salen)==-1) {
            fprintf(stderr, "Error sending response\n");
        }
        if(fin) break;
    }

}