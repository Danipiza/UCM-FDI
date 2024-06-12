#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>

#define BUF_SIZE 500

// CUIDADO CON UTLIZAR LOS PUERTOS
// si no se puede bindear utiliza otro hasta que pase el tiempo de keepalive

// COMPILAR: gcc ej6.c -o ej6
// EJECUTAR: ./ej6 <host> <puerto>
// ejemplo: ./ej6 :: 8080 

// TERMINALES 
// nc ::1 8080
// nc 127.0.0.1 8080

// TERMINA: con SIGINT (Ctrl + C) en el servidor

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
    ssize_t nread;
    char buf[BUF_SIZE];

    memset(&hints, 0, sizeof(hints));
    hints.ai_family=AF_UNSPEC;    /* Allow IPv4 or IPv6 */
    hints.ai_socktype=SOCK_STREAM; /* Datagram socket */
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
    if (rp == NULL) {               /* No address succeeded */
        fprintf(stderr, "Could not bind\n");
        exit(EXIT_FAILURE);
    }

    if(listen(sfd,16)==-1) { perror("listen()"); exit(EXIT_FAILURE); }

    int clientsd;
    char host[NI_MAXHOST];
    char service[NI_MAXSERV];
    while(1) {
        clientsd=accept(sfd, (struct sockaddr *) &sa, &salen);
        if(clientsd==-1) { perror("accept()"); continue; }
        
        s = getnameinfo((struct sockaddr *) &sa,
                        salen, host, NI_MAXHOST,
                        service, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);
        if (s!=0) fprintf(stderr, "getnameinfo: %s\n", gai_strerror(s));
        printf("Conexion desde %s %s\n", host, service);
        
        while(1){
            nread = recv(clientsd, buf, BUF_SIZE, 0);
            if (nread<=0) break;               /* Ignore failed request */           

            // no imprime nada, es un servidor eco

            if (send(clientsd, buf, nread, 0) != nread)
                fprintf(stderr, "Error sending response\n");
        }
        printf("Conexion terminada\n");
    }

    return 0;
}