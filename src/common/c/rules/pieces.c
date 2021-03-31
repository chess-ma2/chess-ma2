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
  int val = 0; 

  struct Piece piece = board[y*8+x];
  struct Piece piece_des = board[des_y*8+des_x];

      
  board[des_y*8 + des_x] = piece ;//move the piece
  board[y*8+ x].type = NONE;
  board[y*8+ x].color = 0;

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
  
      scanf("%d", &val); //choose the new  piece
 
      board[des_y*8 + des_x].type = val; //replace the piece
    }

  
  //for the white team    
  if(board[des_y*8 + des_x].type == PAWN && board[des_y*8 + des_x].color == WHITE && des_y == 0 )
    {
      printf("\nPromotion\n");

      printf("DAME = 5      CAVALIER = 4      FOU = 3       TOUR = 2 \n");
  
      printf("Entrez un chiffre : \n");
  
      scanf("%d", &val); // choose the new piece
 
      board[des_y*8 + des_x].type = val; //replace the piece
    }

  //----------------------------------------------------------------------------------------------
      
  return board; //return the finally board
}


/*

Name of the function : pieceMove_Rock
Make the movement of the piece when it is the Rock movement 
By Marie Maturana
Start the 2021-03-12

*/

struct Piece *pieceMove_Rock(int x, int y, int des_x, int des_y, struct Piece *board)
{
  int color_piece =  board[y*8+x].color; 
    
  if(color_piece) //king is white
    {
      if( x == 4 && y == 7) //does the king is at the good place ?
	{
	  if(des_x == 6 && des_y == 7) //little rock
	    {
	      if( board[7*8+5].type == NONE && board[7*8+6].type == NONE && board[7*8+7].type == ROOK)
		{
		  board[y*8+x].type = NONE;
		  board[y*8+x].color = 0;
		  board[des_y*8+des_x].type = KING;
		  board[des_y*8+des_x].color = WHITE;
		  board[7*8+7].type = NONE;
		  board[7*8+7].color = 0;
		  board[7*8+5].type = ROOK;
		  board[7*8+5].color = WHITE;
		}
	    }
	  else if (des_x == 2 && des_y == 7) //big rock
	    {
	      if( board[7*8+3].type == NONE && board[7*8+2].type == NONE && board[7*8+1].type == NONE && board[7*8+0].type == ROOK)
		{
		  board[y*8+x].type = NONE;
		  board[y*8+x].color = 0;
		  board[des_y*8+des_x].type = KING;
		  board[des_y*8+des_x].color = WHITE;
		  board[7*8+0].type = NONE;
		  board[7*8+0].color = 0;
		  board[7*8+3].type = ROOK;
		  board[7*8+3].color = WHITE;
		}
	    }
	} 
	
    }
  if(!color_piece) //king is black
    {
      if( x == 4 && y == 0) // does the king is at the good place ? 
	{
	  if(des_x == 6 && des_y == 0) //litte rock 
	    {
	      if( board[0*8+5].type == NONE && board[0*8+6].type == NONE && board[0*8+7].type == ROOK)
		{
		  board[y*8+x].type = NONE;
		  board[y*8+x].color = 0;
		  board[des_y*8+des_x].type = KING;
		  board[des_y*8+des_x].color = BLACK;
		  board[0*8+7].type = NONE;
		  board[0*8+7].color = 0; 
		  board[0*8+5].type = ROOK;
		  board[0*8+5].color = BLACK;
		}
	    }
	  else if (des_x == 2 && des_y == 0) //big rock
	    {
	      if( board[0*8+3].type == NONE && board[0*8+2].type == NONE && board[0*8+1].type == NONE && board[0*8+0].type == ROOK)
		{
		  board[y*8+x].type = NONE;
		  board[y*8+x].color = 0;
		  board[des_y*8+des_x].type = KING;
		  board[des_y*8+des_x].color = BLACK;
		  board[0*8+0].type = NONE;
		  board[0*8+0].color = 0; 
		  board[0*8+3].type = ROOK;
		  board[0*8+3].color = BLACK;
		}
	    }
	} 
    }

  return board; //return the plate after the rock
  
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

  if ( board[des_y*8+des_x].color == (enum Color)color_piece &&  board[des_y*8+des_x].type != NONE )
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

  if ( piece.type == ROOK)
    {
      return  isValidMove_Rook( x, y, des_x, des_y,  board); //can move the rook
    }

  if ( piece.type == BISHOP)
    {
      return isValidMove_Bishop( x, y, des_x, des_y, board); //can move the bishop
    }

  if ( piece.type == KNIGHT)
    {
      return  isValidMove_Knight( x, y, des_x, des_y); //can move the knight 
    }
   
  if ( piece.type == QUEEN )
    {
      return  isValidMove_Queen( x, y, des_x, des_y, board); //can move the queen
    }

  if ( piece.type == KING)
    { 
      return  isValidMove_King( x, y, des_x, des_y) ; //can move the king
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
      if((y == 6) && (des_y == y-2) && (x == des_x) && (board[des_y*8+des_x].type == NONE))
	{
	  return 1; 
	}

      if((des_y == y-1) && ((des_x == x + 1 )||(des_x == x - 1 )) && (board[des_y*8+des_x].color != (enum Color)color_piece) && (board[des_y*8+des_x].type != NONE))
	{
	  return 1; 
	}
      
      if((des_y == y-1) && (x == des_x) && (board[des_y*8+des_x].type == NONE))
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

       if((des_y == y+1) && ((des_x == x + 1 )||(des_x == x - 1 )) && (board[des_y*8+des_x].color != (enum Color)color_piece) &&  (board[des_y*8+des_x].type != NONE))
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

Name of the function : isValidMove_Rook
Valid if the movement of the rook is possible
By Marie Maturana
Start the 2021-03-11

*/

int isValidMove_Rook(int x, int y, int des_x, int des_y, struct Piece *board)
{
  
  
  int continue_par = 1;                   
  int par_y = y + 1;
  int par_x = x; 
         
  while( continue_par && par_y <= 7)
    {

      if(continue_par && par_y == des_y && par_x == des_x)
	{
	  return 1; 
	}
      
      if( board[par_y*8+par_x].type != NONE )
	{
	  continue_par = 0;
	}
      
      else
	{
	  par_y += 1; 
	}

    }

  continue_par = 1;                  
  par_y = y - 1;
  par_x = x; 
         
  while( continue_par && par_y >= 0)
    {

      if(continue_par && par_y == des_y && par_x == des_x)
	{
	  return 1; 
	}
      
      if( board[par_y*8+par_x].type != NONE )
	{
	  continue_par = 0;
	}
      
      else
	{
	  par_y -= 1; 
	}
    }
      

  continue_par = 1;
  par_x = x - 1;
  par_y = y; 
         
  while( continue_par && par_x >= 0)
    {

      if(continue_par && par_y == des_y && par_x == des_x)
	{
	  return 1; 
	}
      
      if( board[par_y*8+par_x].type != NONE )
	{
	  continue_par = 0;
	}
      
      else
	{
	  par_x -= 1; 
	}
    }


  continue_par = 1;
  par_x = x + 1;                   
  par_y = y; 
  while( continue_par && par_x <= 7)
    {

      if(continue_par && par_y == des_y && par_x == des_x)
	{
	  return 1; 
	}
      
      if( board[par_y*8+par_x].type != NONE )
	{
	  continue_par = 0;
	}
      
      else
	{
	  par_x += 1;
	}
    }
  return 0; 
}




/*

Name of the function : isValidMove_Bishop
Valid if the movement of the bishop is possible
By Marie Maturana
Start the 2021-03-11

*/

int isValidMove_Bishop(int x, int y, int des_x, int des_y, struct Piece *board)
{

  
  int continue_par = 1;
  int par_x = x + 1;                   
  int par_y = y + 1;
         
  while( continue_par && par_y <= 7 && par_x <= 7)
    {

      if(continue_par && par_y == des_y && par_x == des_x)
	{
	  return 1; 
	}
      
      if( board[par_y*8+par_x].type != NONE ) //someone on the way
	{
	  continue_par = 0;
	}
      
      else
	{
	  par_x += 1;
	  par_y += 1; 
	}

    }

  continue_par = 1;
  par_x = x + 1;                   
  par_y = y - 1;
         
  while( continue_par && par_y >= 0 && par_x <= 7)
    {

      if(continue_par && par_y == des_y && par_x == des_x)
	{
	  return 1; 
	}
      
      if( board[par_y*8+par_x].type != NONE )
	{
	  continue_par = 0;
	}
      
      else
	{
	  par_x += 1;
	  par_y -= 1; 
	}
    }
      

  continue_par = 1;
  par_x = x - 1;                   
  par_y = y + 1;
         
  while( continue_par && par_x >= 0 && par_y <= 7)
    {

      if(continue_par && par_y == des_y && par_x == des_x)
	{
	  return 1; 
	}
      
      if( board[par_y*8+par_x].type != NONE )
	{
	  continue_par = 0;
	}
      
      else
	{
	  par_x -= 1;
	  par_y += 1; 
	}
    }


  continue_par = 1;
  par_x = x - 1;                   
  par_y = y - 1;
         
  while( continue_par && par_y >= 0 && par_x >= 0)
    {

      if(continue_par && par_y == des_y && par_x == des_x)
	{
	  return 1; 
	}
      
      if( board[par_y*8+par_x].type != NONE )
	{
	  continue_par = 0;
	}
      
      else
	{
	  par_x -= 1;
	  par_y -= 1; 
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

int isValidMove_Knight(int x, int y, int des_x, int des_y)
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

Name of the function : isValidMove_Queen
Valid if the movement of the Queen is possible
By Marie Maturana
Start the 2021-03-11

*/

int isValidMove_Queen(int x, int y, int des_x, int des_y, struct Piece *board) 
{
  return isValidMove_Bishop(x,y,des_x,des_y, board) || isValidMove_Rook(x,y,des_x,des_y, board); //call movement of bishop and rook
}




/*

Name of the function : isValidMove_King
Valid if the movement of the king is possible
By Marie Maturana
Start the 2021-03-07

*/

int isValidMove_King(int x, int y, int des_x, int des_y)
{
  if(((des_x == x)||(des_x == x - 1) || (des_x == x + 1))&&((des_y == y)||(des_y == y - 1) ||(des_y == y + 1)))
    {
      return 1; 
    }

  return 0; 
}



/*

Name of the function : isValidMove_Rock
Valid if the movement of the rock is possible
By Marie Maturana
Start the 2021-03-12

*/

int isValidMove_Rock(int x, int y, int des_x, int des_y, int color_piece,  struct Piece *board)
{

  if(color_piece == 1)
    {
      if( x == 4 && y == 7)
	{
	  if(des_x == 6 && des_y == 7)
	    {
	      if( board[7*8+5].type == NONE && board[7*8+6].type == NONE && board[7*8+7].type == ROOK)
		{
		  return 1; 
		}
	    }
	  else if (des_x == 2 && des_y == 7) 
	    {
	      if( board[7*8+3].type == NONE && board[7*8+2].type == NONE && board[7*8+1].type == NONE && board[7*8+0].type == ROOK)
		{
		  return 1; 
		}
	    }
	} 
	
    }
  if(color_piece == 0)
    {
      if( x == 4 && y == 0)
	{
	  if(des_x == 6 && des_y == 0)
	    {
	      if( board[0*8+5].type == NONE && board[0*8+6].type == NONE && board[0*8+7].type == ROOK)
		{
		  return 1; 
		}
	    }
	  else if (des_x == 2 && des_y == 0) 
	    {
	      if( board[0*8+3].type == NONE && board[0*8+2].type == NONE && board[0*8+1].type == NONE && board[0*8+0].type == ROOK)
		{
		  return 1; 
		}
	    }
	} 
    }
   
  
  return 0; 
}
