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

// COMPILAR: gcc ej5.c -o ej5
// EJECUTAR: ./ej5 <host> <puerto>
// ejemplo: ./ej5 :: 8080 

// TERMINALES (hay 2 procesos manejando el servidor)
// nc -u ::1 8080
// nc -u 127.0.0.1 8080

// TERMINA: con SIGINT (Ctrl + C) en el servidor


void proc_hijo(int sfd, int s, 
                struct sockaddr_storage sa, socklen_t salen){
    
    ssize_t bytes_read;
    char buf[BUF_SIZE];
    char host[NI_MAXHOST];
    char service[NI_MAXSERV];
    pid_t pid=getpid();
    printf("Proceso hijo creado, PID: %d\n", pid);
    while(1){
        salen=sizeof(sa);
        bytes_read=recvfrom(sfd, buf, BUF_SIZE, 0,
                (struct sockaddr *) &sa, &salen);
        if (bytes_read==-1) continue;               /* Ignore failed request */
        buf[bytes_read]='\0';
        

        s=getnameinfo((struct sockaddr *) &sa,
                        salen, host, NI_MAXHOST,
                        service, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);
        if (s!=0) fprintf(stderr, "getnameinfo: %s\n", gai_strerror(s));
        
        printf("(PID:%d) El cliente %s:%s\tEnvia: %s", pid, host, service, buf);

        if (sendto(sfd, buf, bytes_read, 0,
                    (struct sockaddr *) &sa,
                    salen) != bytes_read)
            fprintf(stderr, "Error sending response\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc!=3) {
        fprintf(stderr, "Usage: %s <host> <puerto>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    struct addrinfo hints;
    struct addrinfo *ai, *rp;
    int sfd, s;
    struct sockaddr_storage sa;
    socklen_t salen;
    
    

    memset(&hints, 0, sizeof(hints));
    hints.ai_family=AF_UNSPEC;    /* Allow IPv4 or IPv6 */
    hints.ai_socktype=SOCK_DGRAM; /* Datagram socket */
    hints.ai_flags=AI_PASSIVE;    /* For wildcard IP address */

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
        sfd=socket(rp->ai_family, rp->ai_socktype,
                rp->ai_protocol);
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

    printf("PID del padre: %d\n",getpid());
    pid_t pid;
    int i=0;
    for(;i<2;i++){
        pid=fork();
        if(pid==0) proc_hijo(sfd,s, sa,salen);
        else if(pid<0){ perror("fork()"); exit(EXIT_FAILURE); }
    }

    int status;
    for(i=0;i<2;i++){
        wait(&status);
    }
    


    return 0;
}   