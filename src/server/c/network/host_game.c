/**
 * @author Antoine
 * @date Start 19/03/2021
 * @details This part will launch listen of game
 */

//Safety loop guard
#ifndef SERVER_NETWORK_HOST_GAME_C
#define SERVER_NETWORK_HOST_GAME_C

#include "host_game.h"

int start_game_network()
{

    int *socket = malloc(sizeof(int));
    int e = listen_connection(CHESS_MA2_NETWORK_PORT_GAME, socket);
    if (e != 0)
    {
        return e;
    }
    pthread_t pid;
    e = pthread_create(&pid, NULL, &game_worker, (void *) socket);

    if (e != 0)
    {
        return 9;
    }
    return 0;
}

void *game_worker(void * arg)
{
    int *socket = (int*) arg;

    do {
        printf("Waiting for connections...\n");

        int sub_socket = accept(sfd, NULL, NULL);

        if (sub_socket == -1)
            return;

        int sub_socket2 = accept(sfd, NULL, NULL);

        if (sub_socket2 == -1)
            return;

        pid_t fid = fork();
        if (fid == -1)
            return;
        if (fid == 0)
        {
            close(sfd);
            printf("New connection (pid = %i)\n", getpid());

            int e = game_tcp(sub_socket, sub_socket2);

            close(sub_socket);
            close(sub_socket2);

            printf("Close connection (pid = %i) with output %i\n",
                   getpid(), e);

            return;
        }

        close(sub_socket);
        close(sub_socket2);

        signal(SIGCHLD, SIG_IGN);
    }
    while (1);
}

/**
 * @author Antoine
 * @date Start 19/03/2021
 * @details Is job is to make game action
 * @param sub sub socket use
 * @return 0 in normal, other in case of errors
 */
int game_tcp(int s1, s2)
{
    //todo
    sleep(15);
}

//End safety loop guard
#endif