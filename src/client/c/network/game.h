/**
 * @author Antoine & Marine
 * @date Start 30/03/2021
 * @details This part is responsible
 * to manage client/server.
 */

//Safety loop guard
#ifndef CLIENT_NETWORK_GAME_H
#define CLIENT_NETWORK_GAME_H

#include <pthread.h>
#include "tcp_connect.c"
#include <stdio.h>

/**
 * @author Antoine & Marine
 * @date Start 30/03/2021
 * @details Main function of game manage and send buff in wait
 */
void *game_network(void *arg);

void waiter_client();


//End safety loop guard
#endif