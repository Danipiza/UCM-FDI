#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>

#define BUF_SIZE 500

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <host> <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    struct addrinfo hints;
    struct addrinfo *ai, *rp;
    int sfd, s;
    struct sockaddr_storage sa;
    socklen_t salen;
    ssize_t bytes_read;
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
    
    /* getaddrinfo() returns a list of address structures.
        Try each address until we successfully bind(2).
        If socket(2) (or bind(2)) fails, we (close the socket
        and) try the next address. */

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

    if(listen(sfd, 16)==-1) { perror("listen()"); exit(EXIT_FAILURE); }

    int client_sd;
    char host[NI_MAXHOST], service[NI_MAXSERV];
    while(1) {
        client_sd=accept(sfd, (struct sockaddr *) &sa, &salen);
        s=getnameinfo((struct sockaddr *) &sa,
                        salen, host, NI_MAXHOST,
                        service, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);
        if (s!=0) fprintf(stderr, "getnameinfo: %s\n", gai_strerror(s));

        
        while(1){
            bytes_read=recv(client_sd, buf, BUF_SIZE, 0);
            if (bytes_read<=0) break;

            printf("Mensaje de: %s:%s\n", host, service);
            

            if (send(client_sd, buf, bytes_read, 0) == -1)
                fprintf(stderr, "Error sending response\n");
        }
        
        printf("Cliente desconectado\n");       
            
        
        
    }

    return 0;
}