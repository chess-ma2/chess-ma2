/**
 * @author Antoine
 * @date Start 6/03/2021
 * @details Main door of network part for init
 */

//Safety Guard
#ifndef CLIENT_NETWORK_NETWORK_H
#define CLIENT_NETWORK_NETWORK_H

//For common parts
#include "../../../common/c/network/network_info.h"

#include "compatibility.c"
#include <stdio.h>

/**
 * @author Antoine
 * @date Start 6/03/2021
 * @details This function will the main door for network with start and init
 * No Params
 * @return 0 in success any other NB in error,
 * be care full if is not 0,
 * network is not boot and do no use network functions.
 */
int start_network(void);

//End safety guard
#endif