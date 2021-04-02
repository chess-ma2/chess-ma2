/**
 * @author Antoine & Marine
 * @date Start 30/03/2021
 * @details This part is responsible
 * to manage client/server.
 */

//Safety loop guard
#ifndef CLIENT_NETWORK_GAME_C
#define CLIENT_NETWORK_GAME_C

//Includes
#include "game.h"

pthread_mutex_t mutex_input = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_output = PTHREAD_MUTEX_INITIALIZER;

char color = 0;
//maybe should we create a winner and looser variable to know if finsihes by winning

//0 waiting for the client to edit, 1 waiting for the server to edit
char last_side_input = 0;
char last_side_output = 1;

char buf_input[1024];
char buf_output[1024];

void *game_network(void *arg)
{
    int fd = 1;
    int e = define_connection(CHESS_MA2_NETWORK_ADDRESS, CHESS_MA2_NETWORK_PORT_GAME, &fd);
    if (e != 0)
        return NULL;

    char buf[1024];
    while (1)
    {
        //Keep Alive
        pthread_mutex_lock(&mutex_input);
        if (last_side_input == 0)
            write(fd, "0", 2);
        else
        {
            printf("As message to server: %s\n", buf_input);
            dprintf(fd, "%s", buf_input);
            last_side_input = 0;
        }
        pthread_mutex_unlock(&mutex_input);

        read(fd, buf, 1024);
        //Try to set cache
        if (*buf != '0')
        {
                pthread_mutex_lock(&mutex_output);
                if (last_side_output == 0)
                {
                    pthread_mutex_unlock(&mutex_output);
                    waiter_client();
                }
                else
                    pthread_mutex_unlock(&mutex_output);

                //last_side_output == 1 here
                pthread_mutex_lock(&mutex_output);
                last_side_output = 0;
                strcpy(buf_output, buf);
                pthread_mutex_unlock(&mutex_output);
                printf("Send packet, answer from server: %s\n", buf);

        }


    }

    return NULL;
}

void waiter_client()
{
    printf("Wait client unbuff!");
    sleep(1);

    pthread_mutex_lock(&mutex_output);
    if (last_side_output == 0)
    {
        pthread_mutex_unlock(&mutex_output);
        waiter_client();
    }
    else
        pthread_mutex_unlock(&mutex_output);
}
//End safety loop guard
#endif
