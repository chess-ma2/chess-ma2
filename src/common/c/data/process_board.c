/**
 * @author Marine
 * @date 29/03/2021
 * @details part made to process treat make the board into a char
 */

#include <string.h>
#include <err.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../rules/pieces.h"
#include "process_board.h"


//get the board and converts it the char
//the color white is -
//the color black is +
//each piece has a code:
/*  NONE = 0
    PAWN =1
    ROOK= 2,
    BISHOP=3,
    KNIGHT=4,
    QUEEN=5,
    KING=6
 */

char *board_to_char(struct Piece * board)
{
    //intitialising the char
    char * board_char= malloc(64* sizeof(int));
    int trans;
    for(int i=0;i<64;i++)
    {
        if (board[i].color ==WHITE)
        {
            trans = (-1);
        }
        else
        {
            trans = 1;
        }
        switch (board[i].type)
        {
            case NONE:
                board_char[i]=(7);
                break;
            case PAWN:
                board_char[i]=(trans*1);
                break;
            case ROOK:
                board_char[i]=(trans*2);
                break;
            case BISHOP:
                board_char[i]=(trans*3);
                break;
            case KNIGHT:
                board_char[i]=(trans*4);
                break;
            case QUEEN:
                board_char[i]=(trans*5);
                break;
            case KING:
                board_char[i]=(trans*6);
                break;
            default:
                printf("ERROR TYPE DOESN'T EXISTS %i\n",i);
        }
    }
    return board_char;
}

struct Piece *char_to_board(char * board_char)
{
    struct Piece * board = calloc(8*8, sizeof(struct Piece));
    
    for(int i=0;i<64;i++)
    {
        if (board_char[i]!=7)
        {
            if (board_char[i]>0)
            {
                (board+i)->color = BLACK;
            }
            else
            {
                (board+i)->color = WHITE;
                board_char[i]=-1*board_char[i];
            }
        }
        
        switch (board_char[i])
        {
            case 7:
                (board+i)->type=NONE;
                break;
            case 1:
                (board+i)->type=PAWN;
                break;
            case 2:
                (board+i)->type=ROOK;
                break;
            case 3:
                (board+i)->type=BISHOP;
                break;
            case 4:
                (board+i)->type=KNIGHT;
                break;
            case 5:
                (board+i)->type=QUEEN;
                break;
            case 6:
                (board+i)->type=KING;
                break;
            default:
                printf("char was not encoded right %i\n",i);
        }
    }
    
    return board;
}
