#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>

#define BUF_SIZE 500


int main(int argc, char **argv) {
    struct addrinfo hints;
    struct addrinfo *ai, *rp;
    int sfd, s;

    struct sockaddr_storage sa;
    socklen_t salen;
    ssize_t bytes_read;
    char buf[BUF_SIZE];

    if (argc!=3) {
        fprintf(stderr, "Usage: %s <host> <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

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

    if (rp==NULL) {               /* No address succeeded */
        fprintf(stderr, "Could not bind\n");
        exit(EXIT_FAILURE);
    }

    if(listen(sfd, 16)==-1) { perror("listen()"); exit(EXIT_FAILURE); }

    int client_sd;
    char host[NI_MAXHOST], service[NI_MAXSERV];
    while(1) {
        client_sd=accept(sfd, (struct sockaddr *) &sa, &salen);
        if(client_sd==-1) { perror("accept()"); continue; }

        s=getnameinfo((struct sockaddr *) &sa,
                            salen, host, NI_MAXHOST,
                            service, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);
        if (s!=0) fprintf(stderr, "getnameinfo: %s\n", gai_strerror(s));
        printf("Se ha conectado %s:%s\n", host, service);
        //host[strlen(host)]='\n';
        while(1){
            bytes_read=recv(client_sd, buf, BUF_SIZE, 0);
        
            if (bytes_read<=0) break;
            
            printf("Received %zd bytes from %s:%s\n", bytes_read, host, service);            
            

            if (send(client_sd, host, strlen(host), 0) == -1)
                fprintf(stderr, "Error sending response\n");
        }


        
    }
    
    return 0;
}