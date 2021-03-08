#include "pieces.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>


/*

File .c containing all the functions relating to the chess pieces and their movements.
By Marie Maturana
Start the 2021-03-04

*/



/*

Name of the function : pieceMove
Make the movement of the piece
By Marie Maturana
Start the 2021-03-04

*/

struct Piece *pieceMove(int x, int y, int des_x, int des_y, struct Piece *board)
{
  int promotion = 0;
  int val = 0; 

  struct Piece piece = board[y*8+x];
  struct Piece piece_des = board[des_y*8+des_x];

      
  board[des_y*8 + des_x] = piece ; //move the piece
  board[y*8+ x].type = NONE;;

  if( piece_des.type != NONE ) //catch an adverse piece
    {
      piece_des.type = NONE; //the adverse piece disappear 
    }

  //--------------------------------------PROMOTION----------------------------------------------

  //for the black team
  if(board[des_y*8 + des_x].type == PAWN && board[des_y*8 + des_x].color == BLACK && des_y == 7 )
    {
      printf("\nPromotion\n");

      printf("DAME = 5      CAVALIER = 4      FOU = 3       TOUR = 2 \n");
  
      printf("Entrez un chiffre : \n");
  
      promotion = scanf("%d", &val); //choose the new  piece
 
      board[des_y*8 + des_x].type = val; //replace the piece
    }

  
  //for the white team    
  if(board[des_y*8 + des_x].type == PAWN && board[des_y*8 + des_x].color == WHITE && des_y == 0 )
    {
      printf("\nPromotion\n");

      printf("DAME = 5      CAVALIER = 4      FOU = 3       TOUR = 2 \n");
  
      printf("Entrez un chiffre : \n");
  
      promotion = scanf("%d", &val); // choose the new piece
 
      board[des_y*8 + des_x].type = val; //replace the piece
    }

  //----------------------------------------------------------------------------------------------
      
  return board; //return the finally board
}



/*

Name of the function : isValidMove
Valid if the movement of the piece is possible
By Marie Maturana
Start the 2021-03-04

*/


int isValidMove(int x, int y, int des_x, int des_y, struct Piece *board)
{
  struct Piece piece = board[y*8+x];
  int color_piece = piece.color;  

  //penser à faire un switch

  if(x > 7 || x < 0 || y > 7 || y < 0 || des_x > 7 || des_x < 0 || des_y > 7 || des_y < 0) //coordinates out of range
    {
      return 2;
    }

  if ( board[des_y*8+des_x].color == color_piece &&  board[des_y*8+des_x].type != NONE )
    {
      return 3; //same color piece a destination
    }

  if (piece.type == NONE)
    {
      return 4; //select a none piece
    }

  if ( piece.type == PAWN)
    {
      return  isValidMove_Pawn( x, y, des_x, des_y, color_piece, board); //can move the pawn
    }

  if ( piece.type == KNIGHT)
    {
      return  isValidMove_Knight( x, y, des_x, des_y, color_piece); //can move the knight 
    }
  if ( piece.type == KING)
    { 
      return  isValidMove_King( x, y, des_x, des_y, color_piece) ; //can move the king
    }

  return  0; //movement is not possible
   
}


/*

Name of the function : isValidMove_Pawn
Valid if the movement of the pawn is possible
By Marie Maturana
Start the 2021-03-04

*/

int isValidMove_Pawn(int x, int y, int des_x, int des_y, int color_piece, struct Piece *board)
{
  if(color_piece)
    {
      if((y == 6) && (des_y == y-2) && (x == des_x))
	{
	  return 1; 
	}

      if((des_y == y-1) && ((des_x == x + 1 )||(des_x == x - 1 )) && (board[des_y*8+des_x].color != color_piece) && (board[des_y*8+des_x].type != NONE))
	{
	  return 1; 
	}
      
      if((des_y == y-1) && (x == des_x))
	{
	  return 1; 
	}
    }

  else
    {
       if((y == 1) && (des_y == y+2) && (x == des_x) && (board[des_y*8+des_x].type == NONE))
	{
	  return 1; 
	}

      if((des_y == y+1) && ((des_x == x + 1 )||(des_x == x - 1 )) && (board[des_y*8+des_x].color != color_piece) &&  (board[des_y*8+des_x].type != NONE))
	{
	  return 1; 
	}
      
      if((des_y == y+1) && (x == des_x) &&(board[des_y*8+des_x].type == NONE))
	{
	  return 1; 
	}
    }

  return 0; 
}





/*

Name of the function : isValidMove_Knight
Valid if the movement of the knight is possible
By Marie Maturana
Start the 2021-03-08

*/

int isValidMove_Knight(int x, int y, int des_x, int des_y, int color_piece)
{
  if(((des_x == x - 2)|| (des_x == x + 2 )) && ((des_y == y - 1) || (des_y == y + 1)))
    {
      return 1; 
    }

  if(((des_y == y - 2)|| (des_y == y + 2 )) && ((des_x == x - 1) || (des_x == x + 1)))
    {
      return 1; 
    }
  
  return 0; 
}



/*

Name of the function : isValidMove_King
Valid if the movement of the king is possible
By Marie Maturana
Start the 2021-03-07

*/

int isValidMove_King(int x, int y, int des_x, int des_y, int color_piece)
{
  if(((des_x == x)||(des_x == x - 1) || (des_x == x + 1))&&((des_y == y)||(des_y == y - 1) ||(des_y == y + 1)))
    {
      return 1; 
    }

  return 0; 
}



