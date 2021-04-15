
#include "../rules/pieces.c"
#include "../rules/plate.c"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "ANSI-color-codes.h"
#include "../../../database/create_db.c"
#include <string.h>
#include <err.h>
#include <unistd.h>
#include <sqlite3.h>
#include <stdlib.h>
#include "../../../database/functions_db.c"
#include "version1.c"

#ifndef GAME1_C
#define GAME1_C

int main()
{

    //_________________ Welcome message ________________________________

    printf("__________________________________________________________________________________________________\n\n");
    printf(BRED "                                 Welcome to Chess ma² \n\n" reset);
    printf("This is the first version of the project. \n");
    printf("In this version, you can play with a friend (or your sworn chess enemy) on a same computer.\n");
    printf(URED "You must both have (or create) an account to play.\n\n" reset);

    printf("__________________________________________________________________________________________________\n\n");
    //_________________ Connecting to database _________________________
    creatingTables();

    //______ Get or create players
    struct Player *player1 = Player1();
    printf("\n \n");

    struct Player *player2 = Player2();

    //___________________   Start Game   ________________________________
    struct Piece *board = init_board();
    display_board_special(board);
    int res = play(board, player1, player2);

    //___________________   Free memory_   ________________________________

    free(player1->name);
    free(player1->email);
    free(player1);
    free(player2->name);
    free(player2->email);
    free(player2);
    free(board);

    return res;
}

#endif
