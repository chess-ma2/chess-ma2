/**
 * @author Antoine
 * @date Start 6/03/2021
 * @details Base of server side
 */

//Safety Guard
#ifndef SERVER_NETWORK_TCP_SERVER_H
#define SERVER_NETWORK_TCP_SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include <signal.h>

/**
 * @author Antoine
 * @date Start 6/03/2021
 * @details This function will wait on specific port a connection
 * @param port pointer of char* of port
 * @return 0 in success, any other int in failed
 *      1 in case on failure on launch
 *      2 error on free socket for reuse
 *      3 no sockets found!
 *      4 impossible to listen on this port
 */
int listen_connection(const char *port, int *fd);

/**
 * @author Antoine
 * @date Start 18/03/2021
 * @details Function who accept incoming connection
 * @param sfd fd of port
 * @param f a function who is execute with a sub socket in input
 * @warning This function is stopped by program kill
 */
void accept_tcp(int sfd, int (*f)(int));

//End safety guard
#endif