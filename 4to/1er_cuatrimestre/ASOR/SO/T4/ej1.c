#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

// CUIDADO CON UTLIZAR LOS PUERTOS
// si no se puede bindear utiliza otro hasta que pase el tiempo de keepalive

// COMPILAR: gcc ej1.c -o ej1 
// EJECUTAR: ./ej1 <host>

// TERMINA: normal

int main(int argc, char** argv){
    if (argc!=2){
        fprintf(stderr, "Usage: %s <host>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    struct addrinfo hints;
    struct addrinfo *result, *rp;
    int sfd, s;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
    hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */

    s = getaddrinfo(argv[1], NULL, &hints, &result);
    if (s != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        exit(EXIT_FAILURE);
    }

    /* getaddrinfo() returns a list of address structures.
        Try each address until we successfully bind(2).
        If socket(2) (or bind(2)) fails, we (close the socket
        and) try the next address. */
    for (rp = result; rp != NULL; rp = rp->ai_next) {
        void *addr;
        char ipstr[INET6_ADDRSTRLEN];
        const char *family;
        const char *socktype;

        if (rp->ai_family==AF_INET) { // IPv4
            struct sockaddr_in *ipv4=(struct sockaddr_in *)rp->ai_addr;
            addr=&(ipv4->sin_addr);
            family="IPv4 (2:AF_INET)";
        } 
        else { // IPv6
            struct sockaddr_in6 *ipv6=(struct sockaddr_in6 *)rp->ai_addr;
            addr=&(ipv6->sin6_addr);
            family="IPv6 (10:AF_INET6)";
        }

        if (rp->ai_socktype==SOCK_STREAM) socktype="TCP (1:SOCK_STREAM)";
        else if (rp->ai_socktype==SOCK_DGRAM) socktype="UDP (2:SOCK_DGRAM)";
        else socktype="Desconocido";

        // convierte la dirección a una cadena IP numerica
        inet_ntop(rp->ai_family, addr, ipstr, sizeof(ipstr));

        printf("IP: %s\nFamilia: %s\nTipo de socket: %s\n\n", ipstr, family, socktype);
    }

    freeaddrinfo(result); // libera


    return 0;
}