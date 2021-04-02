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

        int sub_socket = accept(*socket, NULL, NULL);

        if (sub_socket == -1)
            return NULL;

        int sub_socket2 = accept(*socket, NULL, NULL);

        if (sub_socket2 == -1)
            return NULL;

        pid_t fid = fork();
        if (fid == -1)
            return NULL;
        if (fid == 0)
        {
            close(*socket);
            printf("New connection (pid = %i)\n", getpid());

            int e = game_tcp(sub_socket, sub_socket2);

            close(sub_socket);
            close(sub_socket2);

            printf("Close connection (pid = %i) with output %i\n",
                   getpid(), e);

            return NULL;
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
int game_tcp(int s1, int s2)
{
    char buf1[1024];
    char buf2[1024];
    ssize_t r1 = 1;
    ssize_t r2 = 1;

    //First msg
    write(s1, "1", 2);
    //added that don't know
    write(s2, "0",2);

    do
    {
        sleep(1);
        printf("Read for %i&%i\n", s1,s2);
        r1 = read(s1, buf1, 1024);
        r2 = read(s2, buf2, 1024);
        printf("Found:\n%s\n%s\n", buf1, buf2);

        dprintf(s1, "%s", buf2);
        dprintf(s2, "%s", buf1);
    }
    
    //q pour antoin pour couper il faut donc renvoyer une negative ?
    while (r1 > 0 && r2 > 0);
    printf("End listen %i&%i\n", s1, s2);

    return 0;
}

//End safety loop guard
#endif
