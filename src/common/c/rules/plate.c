#include "plate.h"
#include "pieces.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>


/*

File .c containing all the functions relating to the chess plate and init this last.
By Marie Maturana & Antoine
Start the 2021-03-04

*/


/**
 * @author Antoine with help of Marie
 * @date Start 04/03/2021
 * @details Generate start of chess game
 * @return board of 64 of size with good pieces position at start
 */
struct Piece *init_board()
{
    //create the board and initialise this to 0
    struct Piece * board = calloc(8*8, sizeof(struct Piece));

    //Color Setup
    for (int i = 0; i < 16; ++i)
    {
        (board+i)->color = BLACK;
    }
    for (int i = 64-16; i < 64; ++i)
    {
        (board+i)->color = WHITE;
    }

    //Type Init
    (board + 0)->type = ROOK;
    (board + 7)->type = ROOK;
    (board + 63-7)->type = ROOK;
    (board + 63)->type = ROOK;
    (board + 1)->type = KNIGHT;
    (board + 6)->type = KNIGHT;
    (board + 63-6)->type = KNIGHT;
    (board + 63-1)->type = KNIGHT;

    (board + 2)->type = BISHOP;
    (board + 5)->type = BISHOP;
    (board + 63-5)->type = BISHOP;
    (board + 63-2)->type = BISHOP;

    (board + 3)->type = QUEEN;
    (board + 4)->type = KING;

    (board + 63 - 4)->type = QUEEN;
    (board + 63 - 3)->type = KING;

    for (int i = 8; i < 16; ++i)
    {
        (board + i)->type = PAWN;
    }

    for (int i = 63-15; i < 63-7; ++i)
    {
        (board + i)->type = PAWN;
    }

    return board;
}


