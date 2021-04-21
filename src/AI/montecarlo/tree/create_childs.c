/**
 * @author Marie
 * @date Start 15/04/2021
 * @details optimate functions to create list of son
 */



#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "create_childs.h"
#include "../../../common/c/rules/pieces.h"
#include "../../../common/c/rules/check_and_pat.h"


/**
 * @author Marie
 * @date Start 17/04/2021
 * @details find all the possible moves for the list of sons of a node
 */

struct tab *possible_moves(Piece *board, int color_team)
{
  struct coordonates_moves list_of_moves[200];
  int index = 0;

  struct tab *struct_list_of_moves = malloc(sizeof(struct tab));
  struct_list_of_moves->index = index ;
  struct_list_of_moves->list_of_moves = list_of_moves ; 
    
  for(int x = 0; x < 8; x++)
    {
      for( int y = 0; y < 8; y++)
	{
	  if(board[y*8+x].color == color_team && board[y*8+x].type != 0)
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
 * @details find all the possible moves for a pawn
 */

struct tab *possible_moves_pawn(Piece *board, int color_team, int x, int y, struct tab *tab_struct)
{
  int index  = tab_struct->index;
  struct coordonates_moves *list_of_moves = tab_struct->list_of_moves;

  if(color_team == 1)
    {
      int x_des = x;
      int y_des = y-1 ;

      if( isValidMove( x, y, x_des, y_des, board) == 1)
	{
	  struct coordonates_moves *move = malloc(sizeof(struct coordonates_moves));
	  move->x = x;
	  move->y = y;
	  move->x_des = x_des; 
	  move->y_des = y_des;
      
	  list_of_moves[index] = *move;
	  index += 1; 
	}
      x_des = x ;
      y_des = y-2 ;

      if( isValidMove( x, y, x_des, y_des, board) == 1)
	{
	  struct coordonates_moves *move = malloc(sizeof(struct coordonates_moves));
	  move->x = x;
	  move->y = y;
	  move->x_des = x_des; 
	  move->y_des = y_des;
      
	  list_of_moves[index] = *move;
	  index += 1; 
	}
      x_des = x-1 ;
      y_des = y-1 ;

      if( isValidMove( x, y, x_des, y_des, board) == 1)
	{
	  struct coordonates_moves *move = malloc(sizeof(struct coordonates_moves));
	  move->x = x;
	  move->y = y;
	  move->x_des = x_des; 
	  move->y_des = y_des;
      
	  list_of_moves[index] = *move;
	  index += 1; 
	}
      x_des = x+1 ;
      y_des = y-1 ;

      if( isValidMove( x, y, x_des, y_des, board) == 1)
	{
	  struct coordonates_moves *move = malloc(sizeof(struct coordonates_moves));
	  move->x = x;
	  move->y = y;
	  move->x_des = x_des; 
	  move->y_des = y_des;
      
	  list_of_moves[index] = *move;
	  index += 1; 
	}
    }

  else if(color_team == 0)
    {
      int x_des = x;
      int y_des = y+1 ;

      if( isValidMove( x, y, x_des, y_des, board) == 1)
	{
	  struct coordonates_moves *move = malloc(sizeof(struct coordonates_moves));
	  move->x = x;
	  move->y = y;
	  move->x_des = x_des; 
	  move->y_des = y_des;
      
	  list_of_moves[index] = *move;
	  index += 1; 
	}
      x_des = x ;
      y_des = y+2 ;

      if( isValidMove( x, y, x_des, y_des, board) == 1)
	{
	  struct coordonates_moves *move = malloc(sizeof(struct coordonates_moves));
	  move->x = x;
	  move->y = y;
	  move->x_des = x_des; 
	  move->y_des = y_des;
      
	  list_of_moves[index] = *move;
	  index += 1; 
	}
      x_des = x-1 ;
      y_des = y+1 ;

      if( isValidMove( x, y, x_des, y_des, board) == 1)
	{
	  struct coordonates_moves *move = malloc(sizeof(struct coordonates_moves));
	  move->x = x;
	  move->y = y;
	  move->x_des = x_des; 
	  move->y_des = y_des;
      
	  list_of_moves[index] = *move;
	  index += 1; 
	}
      x_des = x+1 ;
      y_des = y+1 ;

      if( isValidMove( x, y, x_des, y_des, board) == 1)
	{
	  struct coordonates_moves *move = malloc(sizeof(struct coordonates_moves));
	  move->x = x;
	  move->y = y;
	  move->x_des = x_des; 
	  move->y_des = y_des;
      
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
 * @details find all the possible moves for a queen
 */

struct tab *possible_moves_queen(Piece *board, int color_team,int x, int y, struct tab *tab_struct)
{
  struct tab *tab_inter = malloc(sizeof(struct tab));
  tab_inter = possible_moves_bishop(board, color_team, x, y, tab_struct);

  struct tab *tab_inter1 = malloc(sizeof(struct tab));
  tab_inter1 = possible_moves_rook(board, color_team, x, y, tab_inter);

  return tab_inter1; 
  
}

/**
 * @author Marie
 * @date Start 16/04/2021
 * @details find all the possible moves for a king
 */

struct tab *possible_moves_king(Piece *board, int color_team,int x, int y, struct tab *tab_struct)
{
  int index  = tab_struct->index;
  struct coordonates_moves *list_of_moves = tab_struct->list_of_moves;

   int x_des = x-1 ;
  int y_des = y-1 ;

  if( isValidMove( x, y, x_des, y_des, board) == 1)
    {
      struct coordonates_moves *move = malloc(sizeof(struct coordonates_moves));
      move->x = x;
      move->y = y;
      move->x_des = x_des; 
      move->y_des = y_des;
      
      list_of_moves[index] = *move;
      index += 1; 
    }

  x_des = x ;
  y_des = y-1 ;

  if( isValidMove( x, y, x_des, y_des, board) == 1)
    {
      struct coordonates_moves *move = malloc(sizeof(struct coordonates_moves));
      move->x = x;
      move->y = y;
      move->x_des = x_des; 
      move->y_des = y_des;
      
      list_of_moves[index] = *move;
      index += 1; 
    }

  x_des = x+1 ;
  y_des = y-1 ;

  if( isValidMove( x, y, x_des, y_des, board) == 1)
    {
      struct coordonates_moves *move = malloc(sizeof(struct coordonates_moves));
      move->x = x;
      move->y = y;
      move->x_des = x_des; 
      move->y_des = y_des;
      
      list_of_moves[index] = *move;
      index += 1; 
    }

  x_des = x+1 ;
  y_des = y ;

  if( isValidMove( x, y, x_des, y_des, board) == 1)
    {
      struct coordonates_moves *move = malloc(sizeof(struct coordonates_moves));
      move->x = x;
      move->y = y;
      move->x_des = x_des; 
      move->y_des = y_des;
      
      list_of_moves[index] = *move;
      index += 1; 
    }

  x_des = x-1 ;
  y_des = y ;

  if( isValidMove( x, y, x_des, y_des, board) == 1)
    {
      struct coordonates_moves *move = malloc(sizeof(struct coordonates_moves));
      move->x = x;
      move->y = y;
      move->x_des = x_des; 
      move->y_des = y_des;
      
      list_of_moves[index] = *move;
      index += 1; 
    }

  x_des = x-1 ;
  y_des = y+1 ;

  if( isValidMove( x, y, x_des, y_des, board) == 1)
    {
      struct coordonates_moves *move = malloc(sizeof(struct coordonates_moves));
      move->x = x;
      move->y = y;
      move->x_des = x_des; 
      move->y_des = y_des;
      
      list_of_moves[index] = *move;
      index += 1; 
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
      
      list_of_moves[index] = *move;
      index += 1; 
    }

  x_des = x+1 ;
  y_des = y+1 ;

  if( isValidMove( x, y, x_des, y_des, board) == 1)
    {
      struct coordonates_moves *move = malloc(sizeof(struct coordonates_moves));
      move->x = x;
      move->y = y;
      move->x_des = x_des; 
      move->y_des = y_des;
      
      list_of_moves[index] = *move;
      index += 1; 
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

struct tab *possible_moves_knight(Piece *board, int color_team,int x, int y, struct tab *tab_struct)
{
  int index  = tab_struct->index;
  struct coordonates_moves *list_of_moves = tab_struct->list_of_moves;

  int x_des = x-2 ;
  int y_des = y-1 ;

  if( isValidMove( x, y, x_des, y_des, board) == 1)
    {
      struct coordonates_moves *move = malloc(sizeof(struct coordonates_moves));
      move->x = x;
      move->y = y;
      move->x_des = x_des; 
      move->y_des = y_des;
      
      list_of_moves[index] = *move;
      index += 1; 
    }

  x_des = x-2 ;
  y_des = y+1 ;

  if( isValidMove( x, y, x_des, y_des, board) == 1)
    {
      struct coordonates_moves *move = malloc(sizeof(struct coordonates_moves));
      move->x = x;
      move->y = y;
      move->x_des = x_des; 
      move->y_des = y_des;
      
      list_of_moves[index] = *move;
      index += 1; 
    }

  x_des = x+2 ;
  y_des = y+1 ;

  if( isValidMove( x, y, x_des, y_des, board) == 1)
    {
      struct coordonates_moves *move = malloc(sizeof(struct coordonates_moves));
      move->x = x;
      move->y = y;
      move->x_des = x_des; 
      move->y_des = y_des;
      
      list_of_moves[index] = *move;
      index += 1; 
    }

  x_des = x+2 ;
  y_des = y-1 ;

  if( isValidMove( x, y, x_des, y_des, board) == 1)
    {
      struct coordonates_moves *move = malloc(sizeof(struct coordonates_moves));
      move->x = x;
      move->y = y;
      move->x_des = x_des; 
      move->y_des = y_des;
      
      list_of_moves[index] = *move;
      index += 1; 
    }

  x_des = x+1 ;
  y_des = y+2 ;

  if( isValidMove( x, y, x_des, y_des, board) == 1)
    {
      struct coordonates_moves *move = malloc(sizeof(struct coordonates_moves));
      move->x = x;
      move->y = y;
      move->x_des = x_des; 
      move->y_des = y_des;
      
      list_of_moves[index] = *move;
      index += 1; 
    }

  x_des = x-1 ;
  y_des = y+2 ;

  if( isValidMove( x, y, x_des, y_des, board) == 1)
    {
      struct coordonates_moves *move = malloc(sizeof(struct coordonates_moves));
      move->x = x;
      move->y = y;
      move->x_des = x_des; 
      move->y_des = y_des;
      
      list_of_moves[index] = *move;
      index += 1; 
    }

  x_des = x-1 ;
  y_des = y-2 ;

  if( isValidMove( x, y, x_des, y_des, board) == 1)
    {
      struct coordonates_moves *move = malloc(sizeof(struct coordonates_moves));
      move->x = x;
      move->y = y;
      move->x_des = x_des; 
      move->y_des = y_des;
      
      list_of_moves[index] = *move;
      index += 1; 
    }

  x_des = x+1 ;
  y_des = y-2 ;

  if( isValidMove( x, y, x_des, y_des, board) == 1)
    {
      struct coordonates_moves *move = malloc(sizeof(struct coordonates_moves));
      move->x = x;
      move->y = y;
      move->x_des = x_des; 
      move->y_des = y_des;
      
      list_of_moves[index] = *move;
      index += 1; 
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

struct tab *possible_moves_rook(Piece *board, int color_team,int x, int y, struct tab *tab_struct)
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
	  struct coordonates_moves *move = malloc(sizeof(struct coordonates_moves));
	  move->x = x;
	  move->y = y;
	  move->x_des = par_x; 
	  move->y_des = par_y;
      
	  list_of_moves[index] = *move;
	  index += 1;
	}

      else if( board[par_y*8+par_x].type != NONE )
	{
	  if(board[par_y*8+par_x].color != color_team) 
	    {
	      struct coordonates_moves *move = malloc(sizeof(struct coordonates_moves));
	      move->x = x;
	      move->y = y;
	      move->x_des = par_x; 
	      move->y_des = par_y;
      
	      list_of_moves[index] = *move;
	      index += 1;
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
	  struct coordonates_moves *move = malloc(sizeof(struct coordonates_moves));
	  move->x = x;
	  move->y = y;
	  move->x_des = par_x; 
	  move->y_des = par_y;
      
	  list_of_moves[index] = *move;
	  index += 1;
	}

      else if( board[par_y*8+par_x].type != NONE )
	{
	  if(board[par_y*8+par_x].color != color_team) 
	    {
	      struct coordonates_moves *move = malloc(sizeof(struct coordonates_moves));
	      move->x = x;
	      move->y = y;
	      move->x_des = par_x; 
	      move->y_des = par_y;
      
	      list_of_moves[index] = *move;
	      index += 1;
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
	  struct coordonates_moves *move = malloc(sizeof(struct coordonates_moves));
	  move->x = x;
	  move->y = y;
	  move->x_des = par_x; 
	  move->y_des = par_y;
      
	  list_of_moves[index] = *move;
	  index += 1;
	}

      else if( board[par_y*8+par_x].type != NONE )
	{
	  if(board[par_y*8+par_x].color != color_team) 
	    {
	      struct coordonates_moves *move = malloc(sizeof(struct coordonates_moves));
	      move->x = x;
	      move->y = y;
	      move->x_des = par_x; 
	      move->y_des = par_y;
      
	      list_of_moves[index] = *move;
	      index += 1;
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
	  struct coordonates_moves *move = malloc(sizeof(struct coordonates_moves));
	  move->x = x;
	  move->y = y;
	  move->x_des = par_x; 
	  move->y_des = par_y;
      
	  list_of_moves[index] = *move;
	  index += 1;
	}

      else if( board[par_y*8+par_x].type != NONE )
	{
	  if(board[par_y*8+par_x].color != color_team) 
	    {
	      struct coordonates_moves *move = malloc(sizeof(struct coordonates_moves));
	      move->x = x;
	      move->y = y;
	      move->x_des = par_x; 
	      move->y_des = par_y;
      
	      list_of_moves[index] = *move;
	      index += 1;
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

struct tab *possible_moves_bishop(Piece *board, int color_team,int x, int y, struct tab *tab_struct)
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
	  struct coordonates_moves *move = malloc(sizeof(struct coordonates_moves));
	  move->x = x;
	  move->y = y;
	  move->x_des = par_x; 
	  move->y_des = par_y;
      
	  list_of_moves[index] = *move;
	  index += 1;
	}

      else if( board[par_y*8+par_x].type != NONE )
	{
	  if(board[par_y*8+par_x].color != color_team) 
	    {
	      struct coordonates_moves *move = malloc(sizeof(struct coordonates_moves));
	      move->x = x;
	      move->y = y;
	      move->x_des = par_x; 
	      move->y_des = par_y;
      
	      list_of_moves[index] = *move;
	      index += 1;
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
	  struct coordonates_moves *move = malloc(sizeof(struct coordonates_moves));
	  move->x = x;
	  move->y = y;
	  move->x_des = par_x; 
	  move->y_des = par_y;
      
	  list_of_moves[index] = *move;
	  index += 1;
	}

      else if( board[par_y*8+par_x].type != NONE )
	{
	  if(board[par_y*8+par_x].color != color_team) 
	    {
	      struct coordonates_moves *move = malloc(sizeof(struct coordonates_moves));
	      move->x = x;
	      move->y = y;
	      move->x_des = par_x; 
	      move->y_des = par_y;
      
	      list_of_moves[index] = *move;
	      index += 1;
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
	  struct coordonates_moves *move = malloc(sizeof(struct coordonates_moves));
	  move->x = x;
	  move->y = y;
	  move->x_des = par_x; 
	  move->y_des = par_y;
      
	  list_of_moves[index] = *move;
	  index += 1;
	}

      else if( board[par_y*8+par_x].type != NONE )
	{
	  if(board[par_y*8+par_x].color != color_team) 
	    {
	      struct coordonates_moves *move = malloc(sizeof(struct coordonates_moves));
	      move->x = x;
	      move->y = y;
	      move->x_des = par_x; 
	      move->y_des = par_y;
      
	      list_of_moves[index] = *move;
	      index += 1;
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
	  struct coordonates_moves *move = malloc(sizeof(struct coordonates_moves));
	  move->x = x;
	  move->y = y;
	  move->x_des = par_x; 
	  move->y_des = par_y;
      
	  list_of_moves[index] = *move;
	  index += 1;
	}

      else if( board[par_y*8+par_x].type != NONE )
	{
	  if(board[par_y*8+par_x].color != color_team) 
	    {
	      struct coordonates_moves *move = malloc(sizeof(struct coordonates_moves));
	      move->x = x;
	      move->y = y;
	      move->x_des = par_x; 
	      move->y_des = par_y;
      
	      list_of_moves[index] = *move;
	      index += 1;
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