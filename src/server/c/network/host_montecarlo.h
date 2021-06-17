/**
 * @author Antoine
 * @date Start 11/06/2021
 * @details This part will launch listen of game with montecarlo
 */

//Safety loop guard
#ifndef SERVER_NETWORK_HOST_MONTECARLO_H
#define SERVER_NETWORK_HOST_MONTECARLO_H

#include "../../../common/c/network/network_info.h"
#include "../../../common/c/rules/pieces.c"
#include "../../../common/c/rules/plate.c"
#include "../../../common/c/data/process_board.c"
#include "../../../AI/montecarlo/network/tree/mctsn_explore.c"

#include <pthread.h>

#include "tcp_server.c"

/**
 * @author Antoine
 * @date Start 11/06/2021
 * @details Main function of the file, launch listen of game
 * @return If host network has success to start return 0 else other nb.
 */
int start_game_montecarlo_network();

/**
 * @author Antoine
 * @date Start 11/06/2021
 * @details Worker for thread check game
 */
void *game_montecarlo_worker(void * arg);

/**
 * @author Antoine
 * @date Start 11/06/2021
 * @details Is job is to make game action
 * @param s1 sub socket use player 1
 * @return 0 in normal, other in case of errors
 */
int game_montecarlo_tcp(int s1);


/**
 * @author Antoine
 * @date Start 12/06/2021
 * @detailsPlay bot Montecarlo
 * @param buf1 data from player
 * @param buf2 answer will send to player
 */
void answer_montecarlo(char * buf1, char * buf2);

//End safety loop guard
#endif