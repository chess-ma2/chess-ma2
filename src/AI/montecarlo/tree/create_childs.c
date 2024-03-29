/**
 * @author Marie
 * @date Start 15/04/2021
 * @details optimate functions to create list of son
 */


#ifndef CREATE_CHILDS_C
#define CREATE_CHILDS_C


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "create_childs.h"
#include "check_and_pat_for_AI.c"
#include "mcts.c"



/**
 * @author Marie
 * @date Start 16/04/2021
 * @details find the king's position
 */

struct coordonates_king *king_positionm(Piece *board, int color_team, struct coordonates_king *kingplace)
{
  kingplace->x_king = 0;
  kingplace->y_king = 0;
  
  for(int y = 0; y < 8; y++)
    {
      for( int x = 0; x < 8; x++)
	{
	  if((int)board[y*8+x].color == color_team && board[y*8+x].type == KING)
	    {
	      kingplace->x_king = x;
	      kingplace->y_king = y;
	    }
	}
    }
  return kingplace; 
}

/**
 * @author Marie
 * @date Start 16/04/2021
 * @details test if the king is in check if a move is possible
 */

int isInCheck(Piece *board, int color_team, int x, int y, int x_des, int y_des)
{
  struct Piece * board2 = calloc(8*8, sizeof(struct Piece));

  for( int i = 0; i < 64; i++)
    {
      board2[i].type = board[i].type;
      board2[i].color = board[i].color;
    }

  board2 = pieceMove_AI(x, y, x_des, y_des, board2);

  struct coordonates_king *kingplace = malloc(sizeof(struct coordonates_king));
  kingplace = king_positionm( board2, color_team, kingplace);

  int res = piece_to_place_AI(kingplace->x_king, kingplace->y_king, board2);

  free(board2);

  return res; 
}

/**
 * @author Marie
 * @date Start 17/04/2021
 * @details find all the possible moves for the list of childs of a node
 */


struct tabm *possible_moves(Piece *board, int color_team)
{
  struct coordonates_moves list_of_moves[1000];
  int index = 0;

  struct tabm *struct_list_of_moves = malloc(sizeof(struct tabm));
  struct_list_of_moves->index = index ;
  struct_list_of_moves->list_of_moves = list_of_moves ; 
    
  for(int y = 0; y < 8; y++)
    {
      for( int x = 0; x < 8; x++)
	{
	  if((int)board[y*8+x].color == color_team && board[y*8+x].type != NONE)
	    {
	      switch(board[y*8+x].type)
		{
		case NONE: ; break; 
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

  return struct_list_of_moves; 
}


/**
 * @author Marie
 * @date Start 16/04/2021
 * @details create the new board
 */

struct Piece *new_board(Piece *board, int x, int y, int x_des, int y_des)
{
  struct Piece * board2 = calloc(8*8, sizeof(struct Piece));

  for( int i = 0; i < 64; i++)
    {
      board2[i].type = board[i].type;
      board2[i].color = board[i].color;
    }

  board2 = pieceMove_AI(x , y , x_des  , y_des , board2);

  return board2; 
}  

/**
 * @author Marie
 * @date Start 16/04/2021
 * @details find all the possible moves for a pawn
 */

struct tabm *possible_moves_pawn(Piece *board, int color_team, int x, int y, struct tabm *tab_struct)
{
  int index  = tab_struct->index;
  struct coordonates_moves *list_of_moves = tab_struct->list_of_moves;

  if(color_team == 1)
    {
      int x_des = x;
      int y_des = y-1 ;

      if( isValidMove( x, y, x_des, y_des, board) == 1)
	{
	  if(isInCheck(board, color_team, x, y, x_des, y_des) == 0)
	    { 
	      struct coordonates_moves *move = malloc(sizeof(struct coordonates_moves));
	      move->x = x;
	      move->y = y;
	      move->x_des = x_des; 
	      move->y_des = y_des;
	      move->board = new_board(board, x,y, x_des, y_des);
	      list_of_moves[index] = *move;
	      index += 1; 

	      if(y_des == 0 )
		{
		  struct coordonates_moves *move1 = malloc(sizeof(struct coordonates_moves));
		  move1->x = x;
		  move1->y = y;
		  move1->x_des = x_des; 
		  move1->y_des = y_des;
		  Piece *board2 = new_board(board, x,y, x_des, y_des);
		  board2[y_des*8 + x_des].type = 5;
		  move1->board = board2;
		  list_of_moves[index] = *move1;
		  index += 1;

		  struct coordonates_moves *move2 = malloc(sizeof(struct coordonates_moves));
		  move2->x = x;
		  move2->y = y;
		  move2->x_des = x_des; 
		  move2->y_des = y_des;
		  Piece *board3 = new_board(board, x,y, x_des, y_des);
		  board3[y_des*8 + x_des].type = 4;
		  move2->board = board3;
		  list_of_moves[index] = *move2;
		  index += 1;

		  struct coordonates_moves *move3 = malloc(sizeof(struct coordonates_moves));
		  move3->x = x;
		  move3->y = y;
		  move3->x_des = x_des; 
		  move3->y_des = y_des;
		  Piece *board4 = new_board(board, x,y, x_des, y_des);
		  board4[y_des*8 + x_des].type = 3;
		  move3->board = board4;
		  list_of_moves[index] = *move3;
		  index += 1;

		  struct coordonates_moves *move4 = malloc(sizeof(struct coordonates_moves));
		  move4->x = x;
		  move4->y = y;
		  move4->x_des = x_des; 
		  move4->y_des = y_des;
		  Piece *board5 = new_board(board, x,y, x_des, y_des);
		  board5[y_des*8 + x_des].type = 2;
		  move4->board = board5;
		  list_of_moves[index] = *move4;
		  index += 1; 
		  
		}
  
	    }
	}
	 
      x_des = x ;
      y_des = y-2 ;

      if( isValidMove( x, y, x_des, y_des, board) == 1)
	{
	  if(isInCheck(board, color_team, x, y, x_des, y_des) == 0)
	    { 
	      struct coordonates_moves *move = malloc(sizeof(struct coordonates_moves));
	      move->x = x;
	      move->y = y;
	      move->x_des = x_des; 
	      move->y_des = y_des;
	      move->board = new_board(board, x,y, x_des, y_des);
      
	      list_of_moves[index] = *move;
	      index += 1;

	      
	      if(y_des == 0 )
		{
		  struct coordonates_moves *move1 = malloc(sizeof(struct coordonates_moves));
		  move1->x = x;
		  move1->y = y;
		  move1->x_des = x_des; 
		  move1->y_des = y_des;
		  Piece *board2 = new_board(board, x,y, x_des, y_des);
		  board2[y_des*8 + x_des].type = 5;
		  move1->board = board2;
		  list_of_moves[index] = *move1;
		  index += 1;

		  struct coordonates_moves *move2 = malloc(sizeof(struct coordonates_moves));
		  move2->x = x;
		  move2->y = y;
		  move2->x_des = x_des; 
		  move2->y_des = y_des;
		  Piece *board3 = new_board(board, x,y, x_des, y_des);
		  board3[y_des*8 + x_des].type = 4;
		  move2->board = board3;
		  list_of_moves[index] = *move2;
		  index += 1;

		  struct coordonates_moves *move3 = malloc(sizeof(struct coordonates_moves));
		  move3->x = x;
		  move3->y = y;
		  move3->x_des = x_des; 
		  move3->y_des = y_des;
		  Piece *board4 = new_board(board, x,y, x_des, y_des);
		  board4[y_des*8 + x_des].type = 3;
		  move3->board = board4;
		  list_of_moves[index] = *move3;
		  index += 1;

		  struct coordonates_moves *move4 = malloc(sizeof(struct coordonates_moves));
		  move4->x = x;
		  move4->y = y;
		  move4->x_des = x_des; 
		  move4->y_des = y_des;
		  Piece *board5 = new_board(board, x,y, x_des, y_des);
		  board5[y_des*8 + x_des].type = 2;
		  move4->board = board5;
		  list_of_moves[index] = *move4;
		  index += 1; 
		  
		}
	    } 
	}
      x_des = x-1 ;
      y_des = y-1 ;

      if( isValidMove( x, y, x_des, y_des, board) == 1)
	{
	  if(isInCheck(board, color_team, x, y, x_des, y_des) == 0)
	    { 
	      struct coordonates_moves *move = malloc(sizeof(struct coordonates_moves));
	      move->x = x;
	      move->y = y;
	      move->x_des = x_des; 
	      move->y_des = y_des;
	      move->board = new_board(board, x,y, x_des, y_des);
      
	      list_of_moves[index] = *move;
	      index += 1;

	      
	      if(y_des == 0 )
		{
		  struct coordonates_moves *move1 = malloc(sizeof(struct coordonates_moves));
		  move1->x = x;
		  move1->y = y;
		  move1->x_des = x_des; 
		  move1->y_des = y_des;
		  Piece *board2 = new_board(board, x,y, x_des, y_des);
		  board2[y_des*8 + x_des].type = 5;
		  move1->board = board2;
		  list_of_moves[index] = *move1;
		  index += 1;

		  struct coordonates_moves *move2 = malloc(sizeof(struct coordonates_moves));
		  move2->x = x;
		  move2->y = y;
		  move2->x_des = x_des; 
		  move2->y_des = y_des;
		  Piece *board3 = new_board(board, x,y, x_des, y_des);
		  board3[y_des*8 + x_des].type = 4;
		  move2->board = board3;
		  list_of_moves[index] = *move2;
		  index += 1;

		  struct coordonates_moves *move3 = malloc(sizeof(struct coordonates_moves));
		  move3->x = x;
		  move3->y = y;
		  move3->x_des = x_des; 
		  move3->y_des = y_des;
		  Piece *board4 = new_board(board, x,y, x_des, y_des);
		  board4[y_des*8 + x_des].type = 3;
		  move3->board = board4;
		  list_of_moves[index] = *move3;
		  index += 1;

		  struct coordonates_moves *move4 = malloc(sizeof(struct coordonates_moves));
		  move4->x = x;
		  move4->y = y;
		  move4->x_des = x_des; 
		  move4->y_des = y_des;
		  Piece *board5 = new_board(board, x,y, x_des, y_des);
		  board5[y_des*8 + x_des].type = 2;
		  move4->board = board5;
		  list_of_moves[index] = *move4;
		  index += 1; 
		  
		}
	    }
	}
      x_des = x+1 ;
      y_des = y-1 ;

      if( isValidMove( x, y, x_des, y_des, board) == 1)
	{
	  if(isInCheck(board, color_team, x, y, x_des, y_des) == 0)
	    { 
	      struct coordonates_moves *move = malloc(sizeof(struct coordonates_moves));
	      move->x = x;
	      move->y = y;
	      move->x_des = x_des; 
	      move->y_des = y_des;
	      move->board = new_board(board, x,y, x_des, y_des);
      
	      list_of_moves[index] = *move;
	      index += 1;

	      
	      if(y_des == 0 )
		{
		  struct coordonates_moves *move1 = malloc(sizeof(struct coordonates_moves));
		  move1->x = x;
		  move1->y = y;
		  move1->x_des = x_des; 
		  move1->y_des = y_des;
		  Piece *board2 = new_board(board, x,y, x_des, y_des);
		  board2[y_des*8 + x_des].type = 5;
		  move1->board = board2;
		  list_of_moves[index] = *move1;
		  index += 1;

		  struct coordonates_moves *move2 = malloc(sizeof(struct coordonates_moves));
		  move2->x = x;
		  move2->y = y;
		  move2->x_des = x_des; 
		  move2->y_des = y_des;
		  Piece *board3 = new_board(board, x,y, x_des, y_des);
		  board3[y_des*8 + x_des].type = 4;
		  move2->board = board3;
		  list_of_moves[index] = *move2;
		  index += 1;

		  struct coordonates_moves *move3 = malloc(sizeof(struct coordonates_moves));
		  move3->x = x;
		  move3->y = y;
		  move3->x_des = x_des; 
		  move3->y_des = y_des;
		  Piece *board4 = new_board(board, x,y, x_des, y_des);
		  board4[y_des*8 + x_des].type = 3;
		  move3->board = board4;
		  list_of_moves[index] = *move3;
		  index += 1;

		  struct coordonates_moves *move4 = malloc(sizeof(struct coordonates_moves));
		  move4->x = x;
		  move4->y = y;
		  move4->x_des = x_des; 
		  move4->y_des = y_des;
		  Piece *board5 = new_board(board, x,y, x_des, y_des);
		  board5[y_des*8 + x_des].type = 2;
		  move4->board = board5;
		  list_of_moves[index] = *move4;
		  index += 1; 
		  
		}
	    }
	}
    }

  else if(color_team == 0)
    {
      int x_des = x;
      int y_des = y+1 ;

      if( isValidMove( x, y, x_des, y_des, board) == 1)
	{
	  if(isInCheck(board, color_team, x, y, x_des, y_des) == 0)
	    { 
	      struct coordonates_moves *move = malloc(sizeof(struct coordonates_moves));
	      move->x = x;
	      move->y = y;
	      move->x_des = x_des; 
	      move->y_des = y_des;
	      move->board = new_board(board, x,y, x_des, y_des);
      
	      list_of_moves[index] = *move;
	      index += 1;

	      
	      if(y_des == 7 )
		{
		  struct coordonates_moves *move1 = malloc(sizeof(struct coordonates_moves));
		  move1->x = x;
		  move1->y = y;
		  move1->x_des = x_des; 
		  move1->y_des = y_des;
		  Piece *board2 = new_board(board, x,y, x_des, y_des);
		  board2[y_des*8 + x_des].type = 5;
		  move1->board = board2;
		  list_of_moves[index] = *move1;
		  index += 1;

		  struct coordonates_moves *move2 = malloc(sizeof(struct coordonates_moves));
		  move2->x = x;
		  move2->y = y;
		  move2->x_des = x_des; 
		  move2->y_des = y_des;
		  Piece *board3 = new_board(board, x,y, x_des, y_des);
		  board3[y_des*8 + x_des].type = 4;
		  move2->board = board3;
		  list_of_moves[index] = *move2;
		  index += 1;

		  struct coordonates_moves *move3 = malloc(sizeof(struct coordonates_moves));
		  move3->x = x;
		  move3->y = y;
		  move3->x_des = x_des; 
		  move3->y_des = y_des;
		  Piece *board4 = new_board(board, x,y, x_des, y_des);
		  board4[y_des*8 + x_des].type = 3;
		  move3->board = board4;
		  list_of_moves[index] = *move3;
		  index += 1;

		  struct coordonates_moves *move4 = malloc(sizeof(struct coordonates_moves));
		  move4->x = x;
		  move4->y = y;
		  move4->x_des = x_des; 
		  move4->y_des = y_des;
		  Piece *board5 = new_board(board, x,y, x_des, y_des);
		  board5[y_des*8 + x_des].type = 2;
		  move4->board = board5;
		  list_of_moves[index] = *move4;
		  index += 1; 
		  
		}
	    }
	}
      x_des = x ;
      y_des = y+2 ;

      if( isValidMove( x, y, x_des, y_des, board) == 1)
	{
	  if(isInCheck(board, color_team, x, y, x_des, y_des) == 0)
	    { 
	      struct coordonates_moves *move = malloc(sizeof(struct coordonates_moves));
	      move->x = x;
	      move->y = y;
	      move->x_des = x_des; 
	      move->y_des = y_des;
	      move->board = new_board(board, x,y, x_des, y_des);
      
	      list_of_moves[index] = *move;
	      index += 1;

	      
	       if(y_des == 7 )
		{
		  struct coordonates_moves *move1 = malloc(sizeof(struct coordonates_moves));
		  move1->x = x;
		  move1->y = y;
		  move1->x_des = x_des; 
		  move1->y_des = y_des;
		  Piece *board2 = new_board(board, x,y, x_des, y_des);
		  board2[y_des*8 + x_des].type = 5;
		  move1->board = board2;
		  list_of_moves[index] = *move1;
		  index += 1;

		  struct coordonates_moves *move2 = malloc(sizeof(struct coordonates_moves));
		  move2->x = x;
		  move2->y = y;
		  move2->x_des = x_des; 
		  move2->y_des = y_des;
		  Piece *board3 = new_board(board, x,y, x_des, y_des);
		  board3[y_des*8 + x_des].type = 4;
		  move2->board = board3;
		  list_of_moves[index] = *move2;
		  index += 1;

		  struct coordonates_moves *move3 = malloc(sizeof(struct coordonates_moves));
		  move3->x = x;
		  move3->y = y;
		  move3->x_des = x_des; 
		  move3->y_des = y_des;
		  Piece *board4 = new_board(board, x,y, x_des, y_des);
		  board4[y_des*8 + x_des].type = 3;
		  move3->board = board4;
		  list_of_moves[index] = *move3;
		  index += 1;

		  struct coordonates_moves *move4 = malloc(sizeof(struct coordonates_moves));
		  move4->x = x;
		  move4->y = y;
		  move4->x_des = x_des; 
		  move4->y_des = y_des;
		  Piece *board5 = new_board(board, x,y, x_des, y_des);
		  board5[y_des*8 + x_des].type = 2;
		  move4->board = board5;
		  list_of_moves[index] = *move4;
		  index += 1; 
		  
		}
	    } 
	}
      x_des = x-1 ;
      y_des = y+1 ;

      if( isValidMove( x, y, x_des, y_des, board) == 1)
	{
	  if(isInCheck(board, color_team, x, y, x_des, y_des) == 0)
	    { 
	      struct coordonates_moves *move = malloc(sizeof(struct coordonates_moves));
	      move->x = x;
	      move->y = y;
	      move->x_des = x_des; 
	      move->y_des = y_des;
	      move->board = new_board(board, x,y, x_des, y_des);
      
	      list_of_moves[index] = *move;
	      index += 1;

	      
	       if(y_des == 7 )
		{
		  struct coordonates_moves *move1 = malloc(sizeof(struct coordonates_moves));
		  move1->x = x;
		  move1->y = y;
		  move1->x_des = x_des; 
		  move1->y_des = y_des;
		  Piece *board2 = new_board(board, x,y, x_des, y_des);
		  board2[y_des*8 + x_des].type = 5;
		  move1->board = board2;
		  list_of_moves[index] = *move1;
		  index += 1;

		  struct coordonates_moves *move2 = malloc(sizeof(struct coordonates_moves));
		  move2->x = x;
		  move2->y = y;
		  move2->x_des = x_des; 
		  move2->y_des = y_des;
		  Piece *board3 = new_board(board, x,y, x_des, y_des);
		  board3[y_des*8 + x_des].type = 4;
		  move2->board = board3;
		  list_of_moves[index] = *move2;
		  index += 1;

		  struct coordonates_moves *move3 = malloc(sizeof(struct coordonates_moves));
		  move3->x = x;
		  move3->y = y;
		  move3->x_des = x_des; 
		  move3->y_des = y_des;
		  Piece *board4 = new_board(board, x,y, x_des, y_des);
		  board4[y_des*8 + x_des].type = 3;
		  move3->board = board4;
		  list_of_moves[index] = *move3;
		  index += 1;

		  struct coordonates_moves *move4 = malloc(sizeof(struct coordonates_moves));
		  move4->x = x;
		  move4->y = y;
		  move4->x_des = x_des; 
		  move4->y_des = y_des;
		  Piece *board5 = new_board(board, x,y, x_des, y_des);
		  board5[y_des*8 + x_des].type = 2;
		  move4->board = board5;
		  list_of_moves[index] = *move4;
		  index += 1; 
		  
		}
	    } 
	}
      x_des = x+1 ;
      y_des = y+1 ;

      if( isValidMove( x, y, x_des, y_des, board) == 1)
	{
	  if(isInCheck(board, color_team, x, y, x_des, y_des) == 0)
	    { 
	      struct coordonates_moves *move = malloc(sizeof(struct coordonates_moves));
	      move->x = x;
	      move->y = y;
	      move->x_des = x_des; 
	      move->y_des = y_des;
	      move->board = new_board(board, x,y, x_des, y_des);
      
	      list_of_moves[index] = *move;
	      index += 1;

	      
	       if(y_des == 7 )
		{
		  struct coordonates_moves *move1 = malloc(sizeof(struct coordonates_moves));
		  move1->x = x;
		  move1->y = y;
		  move1->x_des = x_des; 
		  move1->y_des = y_des;
		  Piece *board2 = new_board(board, x,y, x_des, y_des);
		  board2[y_des*8 + x_des].type = 5;
		  move1->board = board2;
		  list_of_moves[index] = *move1;
		  index += 1;

		  struct coordonates_moves *move2 = malloc(sizeof(struct coordonates_moves));
		  move2->x = x;
		  move2->y = y;
		  move2->x_des = x_des; 
		  move2->y_des = y_des;
		  Piece *board3 = new_board(board, x,y, x_des, y_des);
		  board3[y_des*8 + x_des].type = 4;
		  move2->board = board3;
		  list_of_moves[index] = *move2;
		  index += 1;

		  struct coordonates_moves *move3 = malloc(sizeof(struct coordonates_moves));
		  move3->x = x;
		  move3->y = y;
		  move3->x_des = x_des; 
		  move3->y_des = y_des;
		  Piece *board4 = new_board(board, x,y, x_des, y_des);
		  board4[y_des*8 + x_des].type = 3;
		  move3->board = board4;
		  list_of_moves[index] = *move3;
		  index += 1;

		  struct coordonates_moves *move4 = malloc(sizeof(struct coordonates_moves));
		  move4->x = x;
		  move4->y = y;
		  move4->x_des = x_des; 
		  move4->y_des = y_des;
		  Piece *board5 = new_board(board, x,y, x_des, y_des);
		  board5[y_des*8 + x_des].type = 2;
		  move4->board = board5;
		  list_of_moves[index] = *move4;
		  index += 1; 
		  
		}
	    }
	}
    }

  tab_struct->index = index;
  tab_struct->list_of_moves = list_of_moves;

  return tab_struct; 
  
}

/**
 * @author Marie
 * @date Start 16/04/2021
 * @details find all the possible moves for a queen
 */

struct tabm *possible_moves_queen(Piece *board, int color_team,int x, int y, struct tabm *tab_struct)
{
  struct tabm *tab_inter = malloc(sizeof(struct tabm));
  tab_inter = possible_moves_bishop(board, color_team, x, y, tab_struct);

  struct tabm *tab_inter1 = malloc(sizeof(struct tabm));
  tab_inter1 = possible_moves_rook(board, color_team, x, y, tab_inter);

  return tab_inter1; 
  
}

/**
 * @author Marie
 * @date Start 16/04/2021
 * @details find all the possible moves for a king
 */

struct tabm *possible_moves_king(Piece *board, int color_team,int x, int y, struct tabm *tab_struct)
{
  int index  = tab_struct->index;
  struct coordonates_moves *list_of_moves = tab_struct->list_of_moves;

   int x_des = x-1 ;
  int y_des = y-1 ;

  if( isValidMove( x, y, x_des, y_des, board) == 1)
    {
      if(isInCheck(board, color_team, x, y, x_des, y_des) == 0)
	{ 
	  struct coordonates_moves *move = malloc(sizeof(struct coordonates_moves));
	  move->x = x;
	  move->y = y;
	  move->x_des = x_des; 
	  move->y_des = y_des;
	  move->board = new_board(board, x,y, x_des, y_des);
      
	  list_of_moves[index] = *move;
	  index += 1; 
	}
    }

  x_des = x ;
  y_des = y-1 ;

  if( isValidMove( x, y, x_des, y_des, board) == 1)
    {
      if(isInCheck(board, color_team, x, y, x_des, y_des) == 0)
	{ 
	  struct coordonates_moves *move = malloc(sizeof(struct coordonates_moves));
	  move->x = x;
	  move->y = y;
	  move->x_des = x_des; 
	  move->y_des = y_des;
	  move->board = new_board(board, x,y, x_des, y_des);
      
	  list_of_moves[index] = *move;
	  index += 1; 
	}
    }

  x_des = x+1 ;
  y_des = y-1 ;

  if( isValidMove( x, y, x_des, y_des, board) == 1)
    {
      if(isInCheck(board, color_team, x, y, x_des, y_des) == 0)
	{ 
	  struct coordonates_moves *move = malloc(sizeof(struct coordonates_moves));
	  move->x = x;
	  move->y = y;
	  move->x_des = x_des; 
	  move->y_des = y_des;
	  move->board = new_board(board, x,y, x_des, y_des);
      
	  list_of_moves[index] = *move;
	  index += 1; 
	} 
    }

  x_des = x+1 ;
  y_des = y ;

  if( isValidMove( x, y, x_des, y_des, board) == 1)
    {
      if(isInCheck(board, color_team, x, y, x_des, y_des) == 0)
	{ 
	  struct coordonates_moves *move = malloc(sizeof(struct coordonates_moves));
	  move->x = x;
	  move->y = y;
	  move->x_des = x_des; 
	  move->y_des = y_des;
	  move->board = new_board(board, x,y, x_des, y_des);
      
	  list_of_moves[index] = *move;
	  index += 1; 
	}
    }

  x_des = x-1 ;
  y_des = y ;

  if( isValidMove( x, y, x_des, y_des, board) == 1)
    {   
      if(isInCheck(board, color_team, x, y, x_des, y_des) == 0)
	{
	  struct coordonates_moves *move = malloc(sizeof(struct coordonates_moves));
	  move->x = x;
	  move->y = y;
	  move->x_des = x_des; 
	  move->y_des = y_des;
	  move->board = new_board(board, x,y, x_des, y_des);
      
	  list_of_moves[index] = *move;
	  index += 1; 
	}
    }

  x_des = x-1 ;
  y_des = y+1 ;

  if( isValidMove( x, y, x_des, y_des, board) == 1)
    {
      if(isInCheck(board, color_team, x, y, x_des, y_des) == 0)
	{ 
	  struct coordonates_moves *move = malloc(sizeof(struct coordonates_moves));
	  move->x = x;
	  move->y = y;
	  move->x_des = x_des; 
	  move->y_des = y_des;
	  move->board = new_board(board, x,y, x_des, y_des);
      
	  list_of_moves[index] = *move;
	  index += 1; 
	} 
    }

  x_des = x ;
  y_des = y+1 ;

  if( isValidMove( x, y, x_des, y_des, board) == 1)
    {
      struct coordonates_moves *move = malloc(sizeof(struct coordonates_moves));
      move->x = x;
      move->y = y;
      move->x_des = x_des; 
      move->y_des = y_des;
      move->board = new_board(board, x,y, x_des, y_des);
      
      list_of_moves[index] = *move;
      index += 1; 
    }

  x_des = x+1 ;
  y_des = y+1 ;

  if( isValidMove( x, y, x_des, y_des, board) == 1)
    {
      if(isInCheck(board, color_team, x, y, x_des, y_des) == 0)
	{ 
	  struct coordonates_moves *move = malloc(sizeof(struct coordonates_moves));
	  move->x = x;
	  move->y = y;
	  move->x_des = x_des; 
	  move->y_des = y_des;
	  move->board = new_board(board, x,y, x_des, y_des);
      
	  list_of_moves[index] = *move;
	  index += 1; 
	} 
    }

  
  tab_struct->index = index;
  tab_struct->list_of_moves = list_of_moves;

  return tab_struct; 
  
}

/**
 * @author Marie
 * @date Start 16/04/2021
 * @details find all the possible moves for a knight
 */

struct tabm *possible_moves_knight(Piece *board, int color_team,int x, int y, struct tabm *tab_struct)
{
  int index  = tab_struct->index;
  struct coordonates_moves *list_of_moves = tab_struct->list_of_moves;

  int x_des = x-2 ;
  int y_des = y-1 ;

  if( isValidMove( x, y, x_des, y_des, board) == 1)
    {
      if(isInCheck(board, color_team, x, y, x_des, y_des) == 0)
	{ 
	  struct coordonates_moves *move = malloc(sizeof(struct coordonates_moves));
	  move->x = x;
	  move->y = y;
	  move->x_des = x_des; 
	  move->y_des = y_des;
	  move->board = new_board(board, x,y, x_des, y_des);
      
	  list_of_moves[index] = *move;
	  index += 1; 
	} 
    }

  x_des = x-2 ;
  y_des = y+1 ;

  if( isValidMove( x, y, x_des, y_des, board) == 1)
    {
      if(isInCheck(board, color_team, x, y, x_des, y_des) == 0)
	{ 
	  struct coordonates_moves *move = malloc(sizeof(struct coordonates_moves));
	  move->x = x;
	  move->y = y;
	  move->x_des = x_des; 
	  move->y_des = y_des;
	  move->board = new_board(board, x,y, x_des, y_des);
      
	  list_of_moves[index] = *move;
	  index += 1; 
	} 
    }

  x_des = x+2 ;
  y_des = y+1 ;

  if( isValidMove( x, y, x_des, y_des, board) == 1)
    {
      if(isInCheck(board, color_team, x, y, x_des, y_des) == 0)
	{ 
	  struct coordonates_moves *move = malloc(sizeof(struct coordonates_moves));
	  move->x = x;
	  move->y = y;
	  move->x_des = x_des; 
	  move->y_des = y_des;
	  move->board = new_board(board, x,y, x_des, y_des);
      
	  list_of_moves[index] = *move;
	  index += 1; 
	}
    }

  x_des = x+2 ;
  y_des = y-1 ;

  if( isValidMove( x, y, x_des, y_des, board) == 1)
    {
      if(isInCheck(board, color_team, x, y, x_des, y_des) == 0)
	{ 
	  struct coordonates_moves *move = malloc(sizeof(struct coordonates_moves));
	  move->x = x;
	  move->y = y;
	  move->x_des = x_des; 
	  move->y_des = y_des;
	  move->board = new_board(board, x,y, x_des, y_des);
      
	  list_of_moves[index] = *move;
	  index += 1; 
	}
    }

  x_des = x+1 ;
  y_des = y+2 ;

  if( isValidMove( x, y, x_des, y_des, board) == 1)
    {
      if(isInCheck(board, color_team, x, y, x_des, y_des) == 0)
	{ 
	  struct coordonates_moves *move = malloc(sizeof(struct coordonates_moves));
	  move->x = x;
	  move->y = y;
	  move->x_des = x_des; 
	  move->y_des = y_des;
	  move->board = new_board(board, x,y, x_des, y_des);
      
	  list_of_moves[index] = *move;
	  index += 1; 
	} 
    }

  x_des = x-1 ;
  y_des = y+2 ;

  if( isValidMove( x, y, x_des, y_des, board) == 1)
    {
      if(isInCheck(board, color_team, x, y, x_des, y_des) == 0)
	{ 
	  struct coordonates_moves *move = malloc(sizeof(struct coordonates_moves));
	  move->x = x;
	  move->y = y;
	  move->x_des = x_des; 
	  move->y_des = y_des;
	  move->board = new_board(board, x,y, x_des, y_des);
      
	  list_of_moves[index] = *move;
	  index += 1; 
	} 
    }

  x_des = x-1 ;
  y_des = y-2 ;

  if( isValidMove( x, y, x_des, y_des, board) == 1)
    {
      if(isInCheck(board, color_team, x, y, x_des, y_des) == 0)
	{ 
	  struct coordonates_moves *move = malloc(sizeof(struct coordonates_moves));
	  move->x = x;
	  move->y = y;
	  move->x_des = x_des; 
	  move->y_des = y_des;
	  move->board = new_board(board, x,y, x_des, y_des);
      
	  list_of_moves[index] = *move;
	  index += 1; 
	}
    }

  x_des = x+1 ;
  y_des = y-2 ;

  if( isValidMove( x, y, x_des, y_des, board) == 1)
    {
      if(isInCheck(board, color_team, x, y, x_des, y_des) == 0)
	{ 
	  struct coordonates_moves *move = malloc(sizeof(struct coordonates_moves));
	  move->x = x;
	  move->y = y;
	  move->x_des = x_des; 
	  move->y_des = y_des;
	  move->board = new_board(board, x,y, x_des, y_des);
      
	  list_of_moves[index] = *move;
	  index += 1; 
	}
    }

  tab_struct->index = index;
  tab_struct->list_of_moves = list_of_moves;

  return tab_struct; 
}

/**
 * @author Marie
 * @date Start 16/04/2021
 * @details find all the possible moves for a rook
 */

struct tabm *possible_moves_rook(Piece *board, int color_team,int x, int y, struct tabm *tab_struct)
{
  int index  = tab_struct->index;
  struct coordonates_moves *list_of_moves = tab_struct->list_of_moves;

  int continue_par = 1;
  int par_y = y + 1; 
  int par_x = x; 
  
  while(continue_par && par_y <= 7)
    {
      if( board[par_y*8+par_x].type == NONE )
	{
	  if(isInCheck(board, color_team, x, y, par_x, par_y) == 0)
	    { 
	      struct coordonates_moves *move = malloc(sizeof(struct coordonates_moves));
	      move->x = x;
	      move->y = y;
	      move->x_des = par_x; 
	      move->y_des = par_y;
	      move->board = new_board(board, x,y, par_x, par_y);
      
	      list_of_moves[index] = *move;
	      index += 1;
	    }
	}

      else if( board[par_y*8+par_x].type != NONE )
	{
	  if(board[par_y*8+par_x].color != color_team) 
	    {
	      if(isInCheck(board, color_team, x, y, par_x, par_y) == 0)
		{ 
		  struct coordonates_moves *move = malloc(sizeof(struct coordonates_moves));
		  move->x = x;
		  move->y = y;
		  move->x_des = par_x; 
		  move->y_des = par_y;
		  move->board = new_board(board, x,y, par_x, par_y);
      
		  list_of_moves[index] = *move;
		  index += 1;
		}
	    }

	  continue_par = 0; 
	}
      par_y += 1; 
    }

  continue_par = 1;
  par_y = y - 1; 
  par_x = x; 
  
  while(continue_par && par_y >= 0)
    {
      if( board[par_y*8+par_x].type == NONE )
	{
	  if(isInCheck(board, color_team, x, y, par_x, par_y) == 0)
	    { 
	      struct coordonates_moves *move = malloc(sizeof(struct coordonates_moves));
	      move->x = x;
	      move->y = y;
	      move->x_des = par_x; 
	      move->y_des = par_y;
	      move->board = new_board(board, x,y, par_x, par_y);
      
	      list_of_moves[index] = *move;
	      index += 1;
	    }
	}

      else if( board[par_y*8+par_x].type != NONE )
	{
	  if(board[par_y*8+par_x].color != color_team) 
	    {
	      if(isInCheck(board, color_team, x, y, par_x, par_y) == 0)
		{ 
		  struct coordonates_moves *move = malloc(sizeof(struct coordonates_moves));
		  move->x = x;
		  move->y = y;
		  move->x_des = par_x; 
		  move->y_des = par_y;
		  move->board = new_board(board, x,y, par_x, par_y);
      
		  list_of_moves[index] = *move;
		  index += 1;
		}
	    }

	  continue_par = 0; 
	}
      par_y -= 1; 
    }

  continue_par = 1;
  par_y = y ; 
  par_x = x - 1; 
  
  while(continue_par && par_x >= 0)
    {
      if( board[par_y*8+par_x].type == NONE )
	{
	  if(isInCheck(board, color_team, x, y, par_x, par_y) == 0)
	    { 
	      struct coordonates_moves *move = malloc(sizeof(struct coordonates_moves));
	      move->x = x;
	      move->y = y;
	      move->x_des = par_x; 
	      move->y_des = par_y;
	      move->board = new_board(board, x,y, par_x, par_y);
      
	      list_of_moves[index] = *move;
	      index += 1;
	    }
	}

      else if( board[par_y*8+par_x].type != NONE )
	{
	  if(board[par_y*8+par_x].color != color_team) 
	    {
	      if(isInCheck(board, color_team, x, y, par_x, par_y) == 0)
		{ 
		  struct coordonates_moves *move = malloc(sizeof(struct coordonates_moves));
		  move->x = x;
		  move->y = y;
		  move->x_des = par_x; 
		  move->y_des = par_y;
		  move->board = new_board(board, x,y, par_x, par_y);
      
		  list_of_moves[index] = *move;
		  index += 1;
		}
	    }

	  continue_par = 0; 
	}
      par_x -= 1; 
    }

  continue_par = 1;
  par_y = y ; 
  par_x = x + 1; 
  
  while(continue_par && par_x <= 7)
    {
      if( board[par_y*8+par_x].type == NONE )
	{
	  if(isInCheck(board, color_team, x, y, par_x, par_y) == 0)
	    { 
	      struct coordonates_moves *move = malloc(sizeof(struct coordonates_moves));
	      move->x = x;
	      move->y = y;
	      move->x_des = par_x; 
	      move->y_des = par_y;
	      move->board = new_board(board, x,y, par_x, par_y);
      
	      list_of_moves[index] = *move;
	      index += 1;
	    }
	}

      else if( board[par_y*8+par_x].type != NONE )
	{
	  if(board[par_y*8+par_x].color != color_team) 
	    {
	      if(isInCheck(board, color_team, x, y, par_x, par_y) == 0)
		{ 
		  struct coordonates_moves *move = malloc(sizeof(struct coordonates_moves));
		  move->x = x;
		  move->y = y;
		  move->x_des = par_x; 
		  move->y_des = par_y;
		  move->board = new_board(board, x,y, par_x, par_y);
      
		  list_of_moves[index] = *move;
		  index += 1;
		}
	    }

	  continue_par = 0; 
	}
      par_x += 1; 
    }
  
  tab_struct->index = index;
  tab_struct->list_of_moves = list_of_moves;

  return tab_struct; 
  
}

/**
 * @author Marie
 * @date Start 16/04/2021
 * @details find all the possible moves for a bishop
 */

struct tabm *possible_moves_bishop(Piece *board, int color_team,int x, int y, struct tabm *tab_struct)
{
  int index  = tab_struct->index;
  struct coordonates_moves *list_of_moves = tab_struct->list_of_moves;

  int continue_par = 1;
  int par_y = y + 1; 
  int par_x = x + 1; 
  
  while(continue_par && par_y <= 7 && par_x <= 7)
    {
      if( board[par_y*8+par_x].type == NONE )
	{
	  if(isInCheck(board, color_team, x, y, par_x, par_y) == 0)
	    { 
	      struct coordonates_moves *move = malloc(sizeof(struct coordonates_moves));
	      move->x = x;
	      move->y = y;
	      move->x_des = par_x; 
	      move->y_des = par_y;
	      move->board = new_board(board, x,y, par_x, par_y);
      
	      list_of_moves[index] = *move;
	      index += 1;
	    }
	}

      else if( board[par_y*8+par_x].type != NONE )
	{
	  if(board[par_y*8+par_x].color != color_team) 
	    {
	      if(isInCheck(board, color_team, x, y, par_x, par_y) == 0)
	    { 
	      struct coordonates_moves *move = malloc(sizeof(struct coordonates_moves));
	      move->x = x;
	      move->y = y;
	      move->x_des = par_x; 
	      move->y_des = par_y;
	      move->board = new_board(board, x,y, par_x, par_y);
      
	      list_of_moves[index] = *move;
	      index += 1;
	    }
	    }

	  continue_par = 0; 
	}
      par_y += 1;
      par_x += 1; 
    }

  continue_par = 1;
  par_y = y - 1; 
  par_x = x + 1; 
  
  while(continue_par && par_y >= 0 && par_x <= 7)
    {
      if( board[par_y*8+par_x].type == NONE )
	{
	  if(isInCheck(board, color_team, x, y, par_x, par_y) == 0)
	    { 
	      struct coordonates_moves *move = malloc(sizeof(struct coordonates_moves));
	      move->x = x;
	      move->y = y;
	      move->x_des = par_x; 
	      move->y_des = par_y;
	      move->board = new_board(board, x,y, par_x, par_y);
      
	      list_of_moves[index] = *move;
	      index += 1;
	    }
	}

      else if( board[par_y*8+par_x].type != NONE )
	{
	  if(board[par_y*8+par_x].color != color_team) 
	    {
	      if(isInCheck(board, color_team, x, y, par_x, par_y) == 0)
		{ 
		  struct coordonates_moves *move = malloc(sizeof(struct coordonates_moves));
		  move->x = x;
		  move->y = y;
		  move->x_des = par_x; 
		  move->y_des = par_y;
		  move->board = new_board(board, x,y, par_x, par_y);
      
		  list_of_moves[index] = *move;
		  index += 1;
		}
	    }

	  continue_par = 0; 
	}
      par_y -= 1;
      par_x += 1;
    }

  continue_par = 1;
  par_y = y + 1; 
  par_x = x - 1; 
  
  while(continue_par && par_x >= 0 && par_y <= 7)
    {
      if( board[par_y*8+par_x].type == NONE )
	{
	  if(isInCheck(board, color_team, x, y, par_x, par_y) == 0)
	    { 
	      struct coordonates_moves *move = malloc(sizeof(struct coordonates_moves));
	      move->x = x;
	      move->y = y;
	      move->x_des = par_x; 
	      move->y_des = par_y;
	      move->board = new_board(board, x,y, par_x, par_y);
      
	      list_of_moves[index] = *move;
	      index += 1;
	    }
	}

      else if( board[par_y*8+par_x].type != NONE )
	{
	  if(board[par_y*8+par_x].color != color_team) 
	    {
	      if(isInCheck(board, color_team, x, y, par_x, par_y) == 0)
		{ 
		  struct coordonates_moves *move = malloc(sizeof(struct coordonates_moves));
		  move->x = x;
		  move->y = y;
		  move->x_des = par_x; 
		  move->y_des = par_y;
		  move->board = new_board(board, x,y, par_x, par_y);
      
		  list_of_moves[index] = *move;
		  index += 1;
		}
	    }

	  continue_par = 0; 
	}
      par_x -= 1;
      par_y += 1;
    }

  continue_par = 1;
  par_y = y - 1; 
  par_x = x - 1; 
  
  while(continue_par && par_x >= 0 && par_y >= 0)
    {
      if( board[par_y*8+par_x].type == NONE )
	{
	  if(isInCheck(board, color_team, x, y, par_x, par_y) == 0)
	    { 
	      struct coordonates_moves *move = malloc(sizeof(struct coordonates_moves));
	      move->x = x;
	      move->y = y;
	      move->x_des = par_x; 
	      move->y_des = par_y;
	      move->board = new_board(board, x,y, par_x, par_y);
      
	      list_of_moves[index] = *move;
	      index += 1;
	    }
	}

      else if( board[par_y*8+par_x].type != NONE )
	{
	  if(board[par_y*8+par_x].color != color_team) 
	    {
	      if(isInCheck(board, color_team, x, y, par_x, par_y) == 0)
		{ 
		  struct coordonates_moves *move = malloc(sizeof(struct coordonates_moves));
		  move->x = x;
		  move->y = y;
		  move->x_des = par_x; 
		  move->y_des = par_y;
		  move->board = new_board(board, x,y, par_x, par_y);
      
		  list_of_moves[index] = *move;
		  index += 1;
		}
	    }

	  continue_par = 0; 
	}
      par_x -= 1;
      par_y -= 1; 
    }


  tab_struct->index = index;
  tab_struct->list_of_moves = list_of_moves;

  return tab_struct; 
}


#endif
