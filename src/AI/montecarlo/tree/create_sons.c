/**
 * @author Marie
 * @date Start 15/04/2021
 * @details optimate functions to create list of son
 */


#ifndef CREATE_SONS_H
#define CREATE_SONS_H


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../../../common/c/rules/pieces.h"
#include "../../../common/c/rules/check_and_plate.h"


/**
 * @author Marie
 * @date Start 17/04/2021
 * @details find all the possible moves for the list of sons of a node
 */

struct coordonates_moves *possible_moves(Piece *board, int color_team)
{
  struct coordonates_move list_of_moves[200];
  int index = 0;

  struct tab struct_list_of_moves = malloc(sizeof(struct tab));
  struct_list_of_moves->index = index ;
  struct_list_of_moves->list_of_moves = list_of_moves ; 
    
  for(int x = 0; i < 8; i++)
    {
      for( int y = 0; y < 8; y++)
	{
	  if(board[y*8+x].color == color_team && board[y*8+x].type != 0)
	    {
	      switch(board[y*8+x].type)
		{
		case PAWN: struct_list_of_moves = possible_moves_pawn(board,color_team, x, y, struct_list_of_moves); break;
		case ROOK: struct_list_of_moves = possible_moves_rook(board,color_team, x, y, struct_list_of_moves); break;
		case BISHOP: struct_list_of_moves = possible_moves_bishop(board,color_team, x, y, struct_list_of_moves); break;
		case KNIGHT: struct_list_of_moves = possible_moves_knight(board,color_team, x, y, struct_list_of_moves); break;
		case QUEEN: struct_list_of_moves = possible_moves_queen(board,color_team, x, y, struct_list_of_moves); break;
		case KING: struct_list_of_moves = possible_moves_king(board,color_team, x, y, struct_list_of_moves); break;
		  
		}
	    }	  
	}
    }

  return struct_list_of_moves->list_of_moves; 
}
