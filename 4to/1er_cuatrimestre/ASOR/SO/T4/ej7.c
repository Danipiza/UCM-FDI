#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUF_SIZE 500

// CUIDADO CON UTLIZAR LOS PUERTOS
// si no se puede bindear utiliza otro hasta que pase el tiempo de keepalive

// COMPILAR: gcc ej7.c -o ej7
// EJECUTAR: ./ej7 <host> <puerto>
// ejemplo: ./ej7 ::1 8080 = nc ::1 8080
// ejemplo: ./ej7 127.0.0.1 8080 = nc 127.0.0.1 8080


// TERMINA: con SIGINT (Ctrl + C), o al mandar 'Q'

int main(int argc, char **argv) {
    if (argc!=3) {
        fprintf(stderr, "Usage: %s <host> <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    struct addrinfo hints;
    struct addrinfo *ai, *rp;
    int sfd, s;
    size_t len;
    ssize_t bytes_read;
    char buf[BUF_SIZE];
    char query[BUF_SIZE];

    memset(&hints, 0, sizeof(hints));
    hints.ai_family=AF_UNSPEC;    /* Allow IPv4 or IPv6 */
    hints.ai_socktype=SOCK_STREAM; /* TCP */
    hints.ai_flags=0;
    

    s=getaddrinfo(argv[1], argv[2], &hints, &ai);
    if (s!=0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        exit(EXIT_FAILURE);
    }

    /* getaddrinfo() returns a list of address structures.
        Try each address until we successfully connect(2).
        If socket(2) (or connect(2)) fails, we (close the socket
        and) try the next address. */
    for (rp=ai; rp!=NULL; rp=rp->ai_next) {
        sfd=socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (sfd==-1) continue;

        if (connect(sfd, rp->ai_addr, rp->ai_addrlen) != -1)
            break;                  /* Success */

        close(sfd);
    }
    freeaddrinfo(ai);           /* No longer needed */

    if (rp==NULL) {               /* No address succeeded */
        fprintf(stderr, "Could not connect\n");
        exit(EXIT_FAILURE);
    }

    
    
    char host[NI_MAXHOST];
    char service[NI_MAXSERV];
    s = getnameinfo((struct sockaddr *) rp->ai_addr,
                        rp->ai_addrlen, host, NI_MAXHOST,
                        service, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);
    if (s!=0) fprintf(stderr, "getnameinfo: %s\n", gai_strerror(s));
    
    
    while(1) { 
        bytes_read=read(STDIN_FILENO, query, BUF_SIZE);
        if(bytes_read==-1) { perror("read()"); exit(EXIT_FAILURE); }
        query[bytes_read-1]='\0';
        if(send(sfd, query, BUF_SIZE, 0)==-1){
            fprintf(stderr, "Error sending response\n");
            continue;
        }

        bytes_read=recv(sfd, buf, BUF_SIZE, 0);
        buf[bytes_read-1]='\0';
        if (bytes_read<=0) break;         
        else if(strcmp("Q",buf)==0) break;
        printf("%s\n",buf);                  
    }
    
    return 0;
}