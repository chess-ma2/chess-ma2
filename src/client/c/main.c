/**
 * @author Marine
 * @date 01/03/2021
 * @details Main file.c of client part
 */

//Safety loop guard
#ifndef CLIENT_MAINC
#define CLIENT_MAINC

#include "launch/launch.c"
#include "network/network.c"
#include "game/game_process.c"
#include "../../common/c/data/file_io.c"
/**
 * @author Marine
 * @date 01/03/2021
 * @details Main function of client part
 */
int main(int argc, char ** argv)
{
    /*printf("return code: %i\n", save_io("bonjour.txt", "Hello World!"));
    char * str = load_io("bonjour.txt");
    printf("Found with code: %s\n", str);
    free(str);*/
    start_network();
    game_process();
    while (1)
        sleep(1);
    return launch_client(argc, argv);


}

//End safety loop
#endif