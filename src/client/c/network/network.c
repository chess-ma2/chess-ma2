/**
 * @author Antoine
 * @date Start 6/03/2021
 * @details Main door of network part for init
 */

//Safety Guard
#ifndef CLIENT_NETWORK_NETWORK_C
#define CLIENT_NETWORK_NETWORK_C

#include "network.h"

int start_network(void)
{
    printf("Network starting...");
    int e =  check_compatibility();

    if (e != 0)
    {
        printf(
                "Error in network start with compatibility check, code: %i\n",
                e);
        return e;
    }

    printf("Network V%i is compatible!\n", CHESS_MA2_NETWORK_VERSION);

    //Todo add steps with hash ...
    //Here is only a proof of good work of LAYER 4 and 5


    return 0;
}

//End safety guard
#endif