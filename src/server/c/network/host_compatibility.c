/**
 * @author Antoine
 * @date Start 18/03/2021
 * @details This part will launch listen of compatibility
 */

//Safety loop guard
#ifndef SERVER_NETWORK_HOST_COMPATIBILITY_C
#define SERVER_NETWORK_HOST_COMPATIBILITY_C

#include "host_compatibility.h"

int start_compatibility_network()
{
    int *socket = malloc(sizeof(int));
    int e = listen_connection(CHESS_MA2_NETWORK_PORT_COMPATIBILITY, socket);
    if (e != 0)
    {
        return e;
    }
    pthread_t pid;
    e = pthread_create(&pid, NULL, &compatibility_worker, (void *) socket);

    if (e != 0)
    {
        return 9;
    }
    return 0;
}

void *compatibility_worker(void* arg __attribute__((unused)))
{
    int *socket = (int*) arg;
    accept_tcp(*socket, compatibility_answer);

    return 0;
}

int compatibility_answer(int sub)
{
    dprintf(sub, "0|%i|\n", CHESS_MA2_NETWORK_VERSION);
    return 0;
}
//End safety loop guard
#endif