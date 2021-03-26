/**
 * @author Antoine
 * @date Start 6/03/2021
 * @details Base of server side
 */

//Safety Guard
#ifndef SERVER_NETWORK_TCP_SERVER_C
#define SERVER_NETWORK_TCP_SERVER_C

#include "tcp_server.h"

int listen_connection(const char *port, int *fd)
{
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    int sfd, s;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;    /* Allow IPv4 & IPV6 */
    hints.ai_socktype = SOCK_STREAM; /* Datagram socket */
    hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
    hints.ai_protocol = 0;          /* Any protocol */
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;
    s = getaddrinfo(NULL, port, &hints, &result);

    if (s != 0)
        return 1;

    for (rp = result; rp != NULL; rp = rp->ai_next) {
        sfd = socket(rp->ai_family, rp->ai_socktype,
                     rp->ai_protocol);
        if (sfd == -1)
            continue;

        if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) < 0)
            return 2;

        if (bind(sfd, rp->ai_addr, rp->ai_addrlen) == 0)
            break;                  /* Success */
        close(sfd);
    }
    freeaddrinfo(result);           /* No longer needed */

    if (rp == NULL) {               /* No address succeeded */
        return 3;
    }

    int errno = listen(sfd, 5);

    if (errno == -1)
        return 4;

    *fd = sfd;
    return 0;
}

void accept_tcp(int sfd, int (*f)(int))
{
    do {
        printf("Waiting for connections...\n");

        int sub_socket = accept(sfd, NULL, NULL);

        if (sub_socket == -1)
            return;

        pid_t fid = fork();
        if (fid == -1)
            return;
        if (fid == 0)
        {
            close(sfd);
            printf("New connection (pid = %i)\n", getpid());

            int e = (*f)(sub_socket);

            close(sub_socket);
            printf("Close connection (pid = %i) with output %i\n",
                   getpid(), e);

            return;
        }

        close(sub_socket);
        signal(SIGCHLD, SIG_IGN);
    }
    while (1);
}

//End safety guard
#endif