/**
 * @author Antoine
 * @date Start 29/03/2021
 * @details This part manage launch options for client
 */

//Safety loop guard
#ifndef CLIENT_LAUNCH_LAUNCH_C
#define CLIENT_LAUNCH_LAUNCH_C

#include "launch.h"

int launch_client(int argc, char **argv)
{
    if (argc < 2)//No args, default launch
    {
        print_help(argv[0]);
        return 1;
    }

    //TODO
    return 0;
}

void print_help(char* root)
{
    printf("----- [Chess-(ma)² | Help Launch] -----\n");
    printf("To launch the project Chess-(ma)²:\n");
    printf("%s  - No args launch the project with default options.\n", root);
    printf("Options:\n");
    printf("--no-gui  - Launch game in console mode.\n");
    printf("--load <file> - Launch game in LOCAL with specified game.\n");

    printf("--------------------------------------\n");
}

//End safety guard
#endif