/**
 * @author Antoine
 * @date Start 11/06/2021
 * @details This part will launch listen of game montecarlo
 */

//Safety loop guard
#ifndef SERVER_NETWORK_HOST_MONTECARLO_C
#define SERVER_NETWORK_HOST_MONTECARLO_C

#include "host_montecarlo.h"

int start_game_montecarlo_network()
{

    int *socket = malloc(sizeof(int));
    int e = listen_connection(CHESS_MA2_NETWORK_PORT_GAME_MONTECARLO, socket);
    if (e != 0)
    {
        return e;
    }
    pthread_t pid;
    e = pthread_create(&pid, NULL, &game_montecarlo_worker, (void *) socket);

    if (e != 0)
    {
        return 9;
    }
    return 0;
}

void *game_montecarlo_worker(void * arg)
{
    int *socket = (int*) arg;

    do {
        printf("Waiting for connections...\n");

        int sub_socket = accept(*socket, NULL, NULL);

        if (sub_socket == -1)
            return NULL;

        pid_t fid = fork();
        if (fid == -1)
            return NULL;
        if (fid == 0)
        {
            close(*socket);
            printf("New connection (pid = %i)\n", getpid());

            int e = game_montecarlo_tcp(sub_socket);

            close(sub_socket);

            printf("Close connection (pid = %i) with output %i\n",
                   getpid(), e);

            return NULL;
        }

        close(sub_socket);

        signal(SIGCHLD, SIG_IGN);
    }
    while (1);
}

int game_montecarlo_tcp(int s1)
{
    char buf1[1024];
    char buf2[1024];
    ssize_t r1 = 1;

    //First msg
    write(s1, "1", 2);
    
    //write(s2, "0",2);

    do
    {
        sleep(1);
        printf("Read for %i\n", s1);
        r1 = read(s1, buf1, 1024);
        printf("Go to answer with\n%s\n", buf1);
        if (*buf1 != '2')
            answer_montecarlo(buf1, buf2);
        printf("Found:\n%s\n%s\n", buf1, buf2);

        dprintf(s1, "%s", buf2);
    }
    while (r1 > 0);
    printf("End listen %i\n", s1);

    return 0;
}

void answer_montecarlo(char * buf1, char * buf2)
{
    //Case 3
    struct Piece * board = char_to_board((buf1+1));

    display(board);
    board = network_mctsn_choice(board, NULL,0);

    display(board);
    *buf2 = '3';
    strcpy((buf2+1), board_to_char(board));
    *(buf2+65) = 0;

}

//End safety loop guard
#endif
