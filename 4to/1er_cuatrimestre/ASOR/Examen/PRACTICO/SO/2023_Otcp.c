#include <stdio.h>
#include <sys/types.h>         
#include <sys/socket.h>
#include <netdb.h>

#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include <sys/time.h>
#include <sys/resource.h>

// Compilar
// gcc 2023_O2tcp.c -o 23Ej3
// Ejecutar
// ./23Ej3 0.0.0.0 8080 // ipv4
// ./23Ej3 :: 8080      // ipv6

// Cliente usando nc
// nc 127.0.0.1 8080    // ipv4
// nc ::1 8080          // ipv6


int main(int argc, char** argv){
    struct addrinfo hints;
    struct addrinfo *ai, *rp;
    memset(&hints, 0, sizeof(hints));
    
    hints.ai_flags = AI_PASSIVE;
    hints.ai_family = AF_UNSPEC; // IPv4 o IPv6
    hints.ai_socktype = SOCK_STREAM; // TCP
    int rc=getaddrinfo(argv[1], argv[2], &hints, &ai);
    if(rc!=0){
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rc));
        exit(EXIT_FAILURE);
    }


    int sd;
    /* getaddrinfo() returns a list of address structures.
        Try each address until we successfully bind(2).
        If socket(2) (or bind(2)) fails, we (close the socket
        and) try the next address. */

    for (rp = ai; rp != NULL; rp = rp->ai_next) {
        sd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (sd == -1) continue;

        if (bind(sd, rp->ai_addr, rp->ai_addrlen) == 0)
            break;                  /* Success */

        close(sd);
    }
    
    freeaddrinfo(ai);
    if (rp == NULL) {               /* No address succeeded */
        fprintf(stderr, "Could not bind\n");
        exit(EXIT_FAILURE);
    }

    rc = listen(sd, 16);
    if(rc==-1){
        perror("Error en listern");
        close(sd);
        exit(EXIT_FAILURE);
    }

    struct sockaddr_storage sa;
    socklen_t salen = sizeof(sa);
    
    int bytes;    
    char buf[100];
    char host[NI_MAXHOST];
    char serv[NI_MAXSERV];

    long pidRecv;
    int niceSend;
    while(1){
        int clientsd=accept(sd, (struct sockaddr *) &sa,&salen);
        if(clientsd == -1){
            perror("Error en accept");
            continue;
        }
        getnameinfo((struct sockaddr *) &sa, salen, host, NI_MAXHOST, serv, NI_MAXSERV, 
                            NI_NUMERICHOST | NI_NUMERICSERV);
        printf("Connexion desde [%s], %s\n", host, serv);
        
        while(1){
            bytes=recv(clientsd, buf, 79*sizeof(char), 0);
            if(bytes<=0) break;
            buf[bytes]='\0';
            printf("Valor recibido: %s", buf);
            pidRecv=strtol(buf, NULL, 10);

            errno=0;            
            
            niceSend= getpriority(PRIO_PROCESS, pidRecv);
            char a[50];
            if(niceSend==-1 && (errno==ESRCH)) sprintf(a, "Proceso %d no encontrado\n", pidRecv);
            else { 
                sprintf(a, "%d\n", niceSend);
                printf("PID[%d]: %d\n", pidRecv, niceSend);
            }
            
            
                      
            send(clientsd, a, strlen(a),0);
        }
    }


    return 0;
}