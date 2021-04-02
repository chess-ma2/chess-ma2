/**
 * @author Antoine
 * @date Start 6/03/2021
 */

//Safety Guard
#ifndef CLIENT_NETWORK_TCP_CONNECT_C
#define CLIENT_NETWORK_TCP_CONNECT_C

#include "tcp_connect.h"

int define_connection(const char *host, const char *port, int *fd_socket)
{
    struct addrinfo hints;
    struct addrinfo *result;
    int addrinfo_error;

    memset(&hints,0,sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_STREAM; // TCP
    // Get your info
    addrinfo_error = getaddrinfo(host, port ,&hints,&result);

    // Error management, no ip/port found, maybe no network ?
    if(addrinfo_error !=0)
        return 1;

    struct addrinfo *rp;
    int cnx;
    // result points to a linked list
    // try to connect for each result
    for(rp = result; rp !=NULL; rp = rp->ai_next)
    {
        cnx = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if(cnx ==-1)
            continue;
        if(connect(cnx, rp->ai_addr, rp->ai_addrlen)!=-1)
            break;
        close(cnx);
    }
    freeaddrinfo(result);

    //No sockets found at final
    if(rp == NULL)
        return 2;

    //Now launch request
    //...
    //In final, close socket:
    //close(cnx);
    *fd_socket = cnx;
    return 0;
}

//End safety guard
#endif
