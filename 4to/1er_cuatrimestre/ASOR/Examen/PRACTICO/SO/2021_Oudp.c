#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>

// stat() lstat()
#include <sys/stat.h>
#include <stdint.h>
#include <time.h>
#include <sys/sysmacros.h>

int main(int argc, char *argv[]){

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <IPv4/IPv6 address> <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    struct addrinfo hints;
    struct addrinfo *ai, *rp;

    memset(&hints, 0, sizeof(hints));

    hints.ai_family = AF_UNSPEC;    /* IPv4 o IPv6 */
    hints.ai_socktype = SOCK_DGRAM; /* UDP */
    hints.ai_flags = AI_PASSIVE;    
    hints.ai_protocol = IPPROTO_UDP; // Protocol

    
    
    int sfd, s;
    s = getaddrinfo(argv[1], argv[2], &hints, &ai);
    if (s != 0) {
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

        if (bind(sfd, rp->ai_addr, rp->ai_addrlen) == 0)
            break;                  /* Success */

        close(sfd);
    }

    freeaddrinfo(ai);           

    if (rp == NULL) {               /* No address succeeded */
        fprintf(stderr, "Could not bind\n");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_storage sa;
    socklen_t salen;
    ssize_t bytes;
    char buf[80]; // suponemos que no se mandan mas de 80 caracteres
    char resp[80];

    while(1){
        salen = sizeof(sa);
        bytes = recvfrom(sfd, buf, 80, 0,
                (struct sockaddr *) &sa, &salen);
        if (bytes == -1) continue; /* Ignore failed request */
        
        buf[bytes-1] = '\0'; // Eliminar el salto de linea para comprobar el fichero con lstat()
        char host[NI_MAXHOST], service[NI_MAXSERV];

        s = getnameinfo((struct sockaddr *) &sa,
                        salen, host, NI_MAXHOST,
                        service, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV); // NI_NUMERICHOST tambien hay que ponerlo
        
        if (s == 0) printf("Mensaje recibido de %s:%s\n", host, service);
        else {
            fprintf(stderr, "getnameinfo: %s\n", gai_strerror(s));
            continue;
        }
        printf("Peticion del cliente: %s",buf);

        struct stat sb;
        if (lstat(buf, &sb) == -1) sprintf(resp,"No existe\n");
        else { // man 2 lstat
            switch (sb.st_mode & S_IFMT) {
            case S_IFBLK:  sprintf(resp,"block device\n");            break;
            case S_IFCHR:  sprintf(resp,"character device\n");        break;
            case S_IFDIR:  sprintf(resp,"directory\n");               break;
            case S_IFIFO:  sprintf(resp,"FIFO/pipe\n");               break;
            case S_IFLNK:  sprintf(resp,"symlink\n");                 break;
            case S_IFREG:  sprintf(resp,"regular file\n");            break;
            case S_IFSOCK: sprintf(resp,"socket\n");                  break;
            default:       sprintf(resp,"unknown?\n");                break;
            }
        }
        

        
        printf("Fichero: %s\n", resp);
        

        if (sendto(sfd, resp, strlen(resp), 0, (struct sockaddr *) 
            &sa,salen) == -1)
            fprintf(stderr, "Error sending response\n");
    }
}