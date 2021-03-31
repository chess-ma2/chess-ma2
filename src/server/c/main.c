/**
 * @author Marine
 * @date 01/03/2021
 * @details Main file.c of server part
 */

//Safety loop guard
#ifndef SERVER_MAINC
#define SERVER_MAINC

#include "network/host_network.c"
/**
 * @author Marine
 * @date 01/03/2021
 * @details Main function of server part
 */
int main(int argc, char ** argv)
{
    start_host_network();

    while (1)
        sleep(1);
    return 0;
}

//End safety loop
#endif
