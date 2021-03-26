/**
 * @author Antoine
 * @date Start 18/03/2021
 * @details This part will launch listen of compatibility
 */

//Safety loop guard
#ifndef SERVER_NETWORK_HOST_COMPATIBILITY_H
#define SERVER_NETWORK_HOST_COMPATIBILITY_H

#include "../../../common/c/network/network_info.h"
#include <pthread.h>

#include "tcp_server.c"

/**
 * @author Antoine
 * @date Start 18/03/2021
 * @details Main function of the file, launch listen of compatibility
 * @return If host network has success to start return 0 else other nb.
 */
int start_compatibility_network();

/**
 * @author Antoine
 * @date Start 18/03/2021
 * @details Worker for thread check compatibility
 */
void *compatibility_worker(void * arg);

/**
 * @author Antoine
 * @date Start 19/03/2021
 * @details Is job is to answer the request of clients
 * @param sub sub socket use
 * @return 0 in normal, other in case of errors
 */
int compatibility_answer(int sub);

//End safety loop guard
#endif