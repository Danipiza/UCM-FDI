#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>

#include <sys/wait.h>

#define BUF_SIZE 500

// CUIDADO CON UTLIZAR LOS PUERTOS
// si no se puede bindear utiliza otro hasta que pase el tiempo de keepalive

// COMPILAR: gcc ej8.c -o ej8
// EJECUTAR: ./ej8 <host> <puerto>
// ejemplo: ./ej8 :: 8080 

// TERMINAL: nc u <host> <puerto>
// ejemplo: nc u ::1 8080
// ejemplo: nc u 127.0.0.1 8080
// ejemplo: ./ej7 127.0.0.1 8080

// TERMINA: cuando el se cierra el servidor con Ctrl + C

void acc_fork(int clientsd, struct sockaddr_storage sa, socklen_t salen){
    ssize_t bytes_read;
    char buf[BUF_SIZE];
    char host[NI_MAXHOST];
    char service[NI_MAXSERV];
    int s=getnameinfo((struct sockaddr *) &sa,
                        salen, host, NI_MAXHOST,
                        service, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);
    if (s!=0) fprintf(stderr, "getnameinfo: %s\n", gai_strerror(s));
    printf("Conexion desde %s %s\n", host, service);
    
    while(1){
        bytes_read = recv(clientsd, buf, BUF_SIZE, 0);
        if (bytes_read<=0) break;               /* Ignore failed request */           

        // no imprime nada, es un servidor eco

        if (send(clientsd, buf, bytes_read, 0) != bytes_read)
            fprintf(stderr, "Error sending response\n");
    }
    printf("Conexion terminada\n");
}

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
    pid_t pid;
    while(1) {
        clientsd=accept(sfd, (struct sockaddr *) &sa, &salen);
        if(clientsd==-1) { perror("accept()"); continue; }
        
        pid=fork();
        if(pid==0) acc_fork(clientsd, sa, salen);
        else if(pid<0) { perror("fork()"); exit(EXIT_FAILURE); }
        else { 
            waitpid(-1, NULL, WNOHANG); // espera a que cualquier proceso hijo termine, pero sin bloquearse
        }
    }

    return 0;
}