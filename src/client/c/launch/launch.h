/**
 * @author Antoine
 * @date Start 29/03/2021
 * @details This part manage launch options for client
 */

//Safety loop guard
#ifndef CLIENT_LAUNCH_LAUNCH_H
#define CLIENT_LAUNCH_LAUNCH_H

#include <stdio.h>

/**
 * @author Antoine
 * @date Start 29/03/2021
 * @details This function is to launch with right options the client.
 * @param argc number of arg of argv
 * @param argv launch options
 * Options:
 *      No arg=>General launch
 *      For details, please check "print_help()"
 * @return error code or not (0 is good)
 */
int launch_client(int argc, char **argv);

/**
 * @author Antoine
 * @date Start 29/03/2021
 * @details Print message of help args
 * @param root represent the name of the exe (argv[0])
 */
void print_help(char * root);

//End safety guard
#endif
