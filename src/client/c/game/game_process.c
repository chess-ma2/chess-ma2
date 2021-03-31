#include "../network/game.c"
#include "../../../common/c/data/process_board.c"
#include "../../../common/c/rules/rules.c"
#include <stdio.h>


void wait_game_output()
{
    char good = 1;
    while (good)
    {
        sleep(1);
        pthread_mutex_lock(&mutex_output);
        if (last_side_output == 0)
            good = 0;
        pthread_mutex_unlock(&mutex_output);
    }
}

void game_process()
{
    wait_game_output();

    pthread_mutex_lock(&mutex_output);
    last_side_output = 1;

    //Start
    if (*buf_output == '8')
    {
        printf("Hear message of start!\n");
        pthread_mutex_unlock(&mutex_output);
        struct Piece* board = init_board();

        pthread_mutex_lock(&mutex_input);
        last_side_input = 1;
        *buf_input = '1';
        strcpy((buf_input+1), board_to_char(board));
        *(buf_input+65) = 0;
        pthread_mutex_unlock(&mutex_input);
    }
    else if (*buf_output == '1')
    {
        printf("Hear message of display!\n");
        struct Piece* board = char_to_board((buf_output+1));
        pthread_mutex_unlock(&mutex_output);

        display(board);

        //Todo request action and apply move
        pthread_mutex_lock(&mutex_input);
        last_side_input = 1;
        *buf_input = '2';
        strcpy((buf_input+1), board_to_char(board));
        *(buf_input+65) = 0;
        pthread_mutex_unlock(&mutex_input);
    }

    else if (*buf_output == '2')
    {
        printf("Display!\n");
        struct Piece* board = char_to_board((buf_output+1));
        pthread_mutex_unlock(&mutex_output);

        display(board);

        return;
    }

    game_process();
}