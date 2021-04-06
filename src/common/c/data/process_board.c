/**
 * @author Marine
 * @date 29/03/2021
 * @details convertions between board and char
 */

#include <string.h>
#include <err.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../rules/pieces.h"
#include "process_board.h"

//safety loop
#ifndef PROCESS_BOARD_C
#define PROCESS_BOARD_C

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
            trans = -1;
        }
        else
        {
            trans = 1;
        }
        switch (board[i].type)
        {
            case NONE:
                board_char[i]=(char)(7+48);
                break;
            case PAWN:
                board_char[i]=(char)(trans*1+48);
                break;
            case ROOK:
                board_char[i]=(char)(trans*2+48);
                break;
            case BISHOP:
                board_char[i]=(char)(trans*3+48);
                break;
            case KNIGHT:
                board_char[i]=(char)(trans*4+48);
                break;
            case QUEEN:
                board_char[i]=(char)(trans*5+48);
                break;
            case KING:
                board_char[i]=(char)(trans*6+48);
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
        //board_char= board_char - 48;
        if (board_char[i] !='7')
        {
            if (board_char[i]>'0')
            {
                (board+i)->color = BLACK;
            }
            else
            {
                (board+i)->color = WHITE;
                board_char[i]=((int)'0'- board_char[i])*(2)+board_char[i];
            }
        }
        
        switch (board_char[i])
        {
            case '1':
                (board+i)->type=PAWN;
                break;
            case '2':
                (board+i)->type=ROOK;
                break;
            case '3':
                (board+i)->type=BISHOP;
                break;
            case '4':
                (board+i)->type=KNIGHT;
                break;
            case '5':
                (board+i)->type=QUEEN;
                break;
            case '6':
                (board+i)->type=KING;
                break;
            default:
                (board+i)->type=NONE;
                break;
        }
    }
    
    return board;
}

//End safety loop guard
#endif
