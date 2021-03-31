/**
 * @author Antoine
 * @date Start 17/03/2021
 * @details This part will contain main part of network L4&5 Start
 */

//Safety loop guard
#ifndef SERVER_NETWORK_HOST_NETWORK_H
#define SERVER_NETWORK_HOST_NETWORK_H

#include "host_compatibility.c"
#include "host_game.c"

/**
 * @author Antoine
 * @date Start 17/03/2021
 * @details Main function of network in server, launch process.
 * @return If host network has success to start return 0 else other nb.
 */
int start_host_network();

//End safety loop guard
#endif