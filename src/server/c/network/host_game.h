/**
 * @author Antoine
 * @date Start 19/03/2021
 * @details This part will launch listen of game
 */

//Safety loop guard
#ifndef SERVER_NETWORK_HOST_GAME_H
#define SERVER_NETWORK_HOST_GAME_H

#include "../../../common/c/network/network_info.h"
#include <pthread.h>

#include "tcp_server.c"

/**
 * @author Antoine
 * @date Start 19/03/2021
 * @details Main function of the file, launch listen of game
 * @return If host network has success to start return 0 else other nb.
 */
int start_game_network();

/**
 * @author Antoine
 * @date Start 19/03/2021
 * @details Worker for thread check game
 */
void *game_worker(void * arg);

/**
 * @author Antoine
 * @date Start 19/03/2021
 * @details Is job is to make game action
 * @param s1 sub socket use player 1
 * @param s2 sub socket use player 2
 * @return 0 in normal, other in case of errors
 */
int game_tcp(int s1, int s2);

//End safety loop guard
#endif