/**
 * @author Antoine
 * @date Start 6/03/2021
 */

//Safety Guard
#ifndef CLIENT_NETWORK_TCP_CONNECT_H
#define CLIENT_NETWORK_TCP_CONNECT_H

#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>
#include <unistd.h>

/**
 * @author Antoine
 * @date Start 6/03/2021
 * @details This function will create and init a connection,
 * however is not here where infos has read or write
 * and you need to close socket.
 * @param host pointer of char* of host
 * @param port pointer of char* of port
 * @param fd_socket pointer will be changed to the socket in case of success.
 * @return 0 in success, any other int in failed
 *      1 in no other side found (maybe no network connection)
 *      2 no sockets empty found for connection
 */
int define_connection(const char *host, const char *port, int *fd_socket);

//End safety guard
#endif