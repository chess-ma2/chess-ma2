/**
 * @author Marine
 * @date 01/03/2021
 * @details Main file.c of common part
 */

//Safety loop guard
#ifndef COMMON_MAINC
#define COMMON_MAINC

//Rules part
#include "rules/rules.c"
#include "rules/pieces.h"
#include "rules/plate.h"
#include "data/process_board.c"

/**
 * @author Marine
 * @date 01/03/2021
 * @details Main function of common part
 */
int main(int argc, char ** argv)
{
  /*
    struct Piece * board= init_board();
    
    char * new_char = board_to_char(board);
    
    struct Piece * new_board =char_to_board(new_char);
    
    int i = 0;
    
    while (i<64 && board[i].type==new_board[i].type)
    {
        i++;
    }
    if (i<64)
    {
        printf("NOT OKAY%i\n",i);
    }
    else
    {
        printf("THE FONCTIONS board_to_char and char_to_board are WORKING !!!\n");
    }
    
    free(board);
    free(new_board);
    return 0;
  */
   return rules();
}

//End safety loop
#endif
