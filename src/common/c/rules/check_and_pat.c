#include "plate.h"
#include "pieces.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "check_and_pat.h"

//autres mouvements possibles pour arreter le echec et mat
// return 1
//return 0

int checkmat_secondcondition(int x_king, int y_king, int can_rock, struct Piece *board)
{

  int tmp1 = x_king;
  int tmp2 = y_king; 
  
  for(int y = 0; y < 8; y++) 
    {
      for(int x = 0; x < 8; x++)
	{
	  for(int des_y = 0; des_y < 8; des_y++) 
	    {
	      for(int des_x = 0; des_x < 8; des_x++)
		{
		   
		  
		  if (can_rock == 1 && isValidMove_Rock( x, y, des_x, des_y, board[y*8+x].color, board) == 1)
		    { 
		      board = pieceMove_Rock(x, y, des_x, des_y, board);
		      x_king = des_x;
		      y_king = des_y; 

		      if (piece_to_place( x_king, y_king, board) == 0)
			{
			  board = pieceMove(des_x, des_y, x, y, board);
			  return 1; 
			}
			  board = pieceMove(des_x, des_y, x, y, board);
		    }
		    
		  else if(isValidMove(x, y, des_x, des_y, board) == 1)
		    {

		      if(board[y*8+x].type == KING)
			{ 
			  x_king = des_x;
			  y_king = des_y;
			}
			  
			  
		      board = pieceMove(x, y, des_x, des_y, board);


		      if (piece_to_place( x_king, y_king,board)== 0 )
			{

			  printf("plus d'échec quand la piece %d %d va a %d %d\n", x, y, des_x, des_y);
			   board = pieceMove(des_x, des_y, x, y, board);
			  return 1; 
			}			 
		      board = pieceMove(des_x, des_y, x, y, board);
	 
		    }

		  x_king = tmp1;
		  y_king = tmp2;
	  
		}
	    }
	 
	}

    }
      

return 0;
 
}


//d'autres mouvements possibles si pat
//return 0 si possible
// sinon return 1

int othermove_pat(struct Piece *board)
{

  for(int y = 0; y < 8; y++) 
    {
      for(int x = 0; x < 8; x++)
	{
	  if(piece_to_place(x, y, board) == 1)
	    {
	      return 1;
	    }
	}
    }

  return 0;
}

int kingcheck_place(int x_king, int y_king, int x_piece, int y_piece, struct Piece *board)
{
  
  if( board[y_king*8+x_king].color != board[y_piece*8+x_piece].color )
    {

      if(isValidMove(x_piece, y_piece, x_king, y_king, board) == 1)
	{ 
	  return 1 ;
	} 
    } 

  return 0; 
  
}

int piece_to_place(int x_place, int y_place,struct Piece *board)
{

  for(int y = 0; y < 8; y++) 
    {
      for(int x = 0; x < 8; x++)
	{
	  if(kingcheck_place(x_place, y_place, x, y, board) == 1)
	    {
	      return 1;
	    }
	}
    }

  return 0;
  
}

int checkmat_firstcondition(int x_king, int y_king, struct Piece *board)
{

  int sum = 0;

  //---------------------------------------------------------------------

  if(board[(y_king)*8+(x_king-1)].color == board[y_king*8+x_king].color && board[(y_king)*8+(x_king-1)].type != 0 && (x_king - 1) <= 7 && (x_king - 1) >= 0 &&  y_king >= 0 &&  y_king <= 7)
    {
      sum += 1; 
    }

  else if ((x_king - 1) <= 7 && (x_king - 1) >= 0 &&  y_king >= 0 &&  y_king <= 7)
    {
      sum += piece_to_place(x_king - 1, y_king, board); 
    }

  else
    {
      sum += 1;
    }

  //---------------------------------------------------------------------

  if(board[(y_king-1)*8+(x_king)].color == board[y_king*8+x_king].color && board[(y_king-1)*8+(x_king)].type != 0 && (x_king) <= 7 && (x_king) >= 0 &&  (y_king - 1) >= 0 &&  (y_king-1) <= 7)
    {
      sum += 1;
    }
   
  else if ((x_king) <= 7 && (x_king) >= 0 &&  (y_king - 1) >= 0 &&  (y_king-1) <= 7)
    {
      sum += piece_to_place(x_king, y_king - 1, board);
    }

  else
    {
      sum += 1;
    } 
  
  //---------------------------------------------------------------------


  if(board[(y_king-1)*8+(x_king-1)].color == board[y_king*8+x_king].color && board[(y_king-1)*8+(x_king-1)].type != 0 && (x_king-1) <= 7 && (x_king-1) >= 0 &&  (y_king - 1) >= 0 &&  (y_king-1) <= 7)
    {
      sum += 1; 
    }
  else if ((x_king-1) <= 7 && (x_king-1) >= 0 &&  (y_king - 1) >= 0 &&  (y_king-1) <= 7)
    {
      sum += piece_to_place(x_king - 1, y_king - 1, board);
    }

  else
    {
      sum += 1;
    }

  //---------------------------------------------------------------------


  if(board[(y_king+1)*8+(x_king+1)].color == board[y_king*8+x_king].color && board[(y_king+1)*8+(x_king+1)].type != 0 && (x_king + 1) <= 7 && (x_king + 1) >= 0 &&  (y_king + 1) >= 0 &&  (y_king + 1) <= 7)
    {
      sum += 1;
    }
  else if ((x_king + 1) <= 7 && (x_king + 1) >= 0 &&  (y_king + 1) >= 0 &&  (y_king + 1) <= 7)
    {
      sum += piece_to_place(x_king + 1, y_king + 1, board);
      
    }

  else
    {
      sum += 1;
    }
   
  //---------------------------------------------------------------------

  if(board[(y_king)*8+(x_king+1)].color == board[y_king*8+x_king].color && board[(y_king)*8+(x_king+1)].type != 0 && (x_king + 1) <= 7 && (x_king + 1) >= 0 &&  (y_king) >= 0 &&  (y_king) <= 7)
    {
      sum += 1;
    }


  else if ((x_king + 1) <= 7 && (x_king + 1) >= 0 &&  (y_king) >= 0 &&  (y_king) <= 7)
    {
      sum += piece_to_place(x_king + 1, y_king, board); 
    }

  else
    {
      sum += 1;
    }

  //---------------------------------------------------------------------

  if(board[(y_king+1)*8+(x_king)].color == board[y_king*8+x_king].color && board[(y_king+1)*8+(x_king)].type != 0 && (x_king) <= 7 && (x_king) >= 0 &&  (y_king + 1) >= 0 &&  (y_king + 1) <= 7)
    {
      sum += 1;
    }
   
  else if ((x_king) <= 7 && (x_king) >= 0 &&  (y_king + 1) >= 0 &&  (y_king + 1) <= 7)
    {
      sum += piece_to_place(x_king, y_king+1, board);
    }

  else
    {
      sum += 1;
    }

  //---------------------------------------------------------------------


   
  if(board[(y_king-1)*8+(x_king+1)].color == board[y_king*8+x_king].color && board[(y_king-1)*8+(x_king+1)].type != 0 && (x_king + 1) <= 7 && (x_king + 1) >= 0 &&  (y_king - 1) >= 0 &&  (y_king - 1) <= 7)
    {
      sum += 1; 
    }
  
  else if ((x_king + 1) <= 7 && (x_king + 1) >= 0 &&  (y_king - 1) >= 0 &&  (y_king - 1) <= 7)
    {
      sum += piece_to_place(x_king + 1, y_king - 1, board);
    }

  else
    {
      sum += 1;
    }

  //---------------------------------------------------------------------


  if(board[(y_king+1)*8+(x_king-1)].color == board[y_king*8+x_king].color && board[(y_king+1)*8+(x_king-1)].type != 0 && (x_king - 1) <= 7 && (x_king - 1) >= 0 &&  (y_king + 1) >= 0 &&  (y_king + 1) <= 7)
    {
      sum += 1; 
    }
  else if ((x_king - 1) <= 7 && (x_king - 1) >= 0 &&  (y_king + 1) >= 0 &&  (y_king + 1) <= 7)
    {
      sum += piece_to_place(x_king - 1, y_king + 1, board);
    }

  else
    {
      sum += 1; 
    }

  //---------------------------------------------------------------------

  if ((x_king ) <= 7 && (x_king) >= 0 &&  (y_king) >= 0 &&  (y_king) <= 7)
    {
      sum += piece_to_place(x_king, y_king, board);
    }

  else
    {
      sum += 1;
    }

  //---------------------------------------------------------------------

  if(sum == 9)
    {
      return 1;
    }

  return 0; 

}


int check_mat(int x_king, int y_king, int can_rock, struct Piece *board)
{
  if(checkmat_firstcondition(x_king, y_king, board) == 1) // && checkmat_secondcondition(x_king, y_king, can_rock, board) == 0)
    {
      return 1;
    }

    return 0; 
} 

int pat(int x_king, int y_king, struct Piece *board)
{
  
  int sum = 0;

  //---------------------------------------------------------------------

  if(board[(y_king)*8+(x_king-1)].color == board[y_king*8+x_king].color && board[(y_king)*8+(x_king-1)].type != 0 && (x_king - 1) <= 7 && (x_king - 1) >= 0 &&  y_king >= 0 &&  y_king <= 7)
    {
      sum += 1;
    }

  if ((x_king - 1) <= 7 && (x_king - 1) >= 0 &&  y_king >= 0 &&  y_king <= 7)
    {
      sum += piece_to_place(x_king - 1, y_king, board);
    }

  else
    {
      sum += 1;
    }

  //---------------------------------------------------------------------

   if(board[(y_king-1)*8+(x_king)].color == board[y_king*8+x_king].color && board[(y_king-1)*8+(x_king)].type != 0 && (x_king) <= 7 && (x_king) >= 0 &&  (y_king - 1) >= 0 &&  (y_king-1) <= 7)
    {
      sum += 1;
    }
   
  if ((x_king) <= 7 && (x_king) >= 0 &&  (y_king - 1) >= 0 &&  (y_king-1) <= 7)
    {
      sum += piece_to_place(x_king, y_king - 1, board);
    }

  else
    {
      sum += 1;
    } 
  
  //---------------------------------------------------------------------


   if(board[(y_king-1)*8+(x_king-1)].color == board[y_king*8+x_king].color && board[(y_king-1)*8+(x_king-1)].type != 0 && (x_king-1) <= 7 && (x_king-1) >= 0 &&  (y_king - 1) >= 0 &&  (y_king-1) <= 7)
     {
       sum += 1;
     }
  if ((x_king-1) <= 7 && (x_king-1) >= 0 &&  (y_king - 1) >= 0 &&  (y_king-1) <= 7)
    {
      sum += piece_to_place(x_king - 1, y_king - 1, board);
    }

  else
    {
      sum += 1;
    }

  //---------------------------------------------------------------------


     if(board[(y_king+1)*8+(x_king+1)].color == board[y_king*8+x_king].color && board[(y_king+1)*8+(x_king+1)].type != 0 && (x_king + 1) <= 7 && (x_king + 1) >= 0 &&  (y_king + 1) >= 0 &&  (y_king + 1) <= 7)
    {
      sum += 1;
    }
   if ((x_king + 1) <= 7 && (x_king + 1) >= 0 &&  (y_king + 1) >= 0 &&  (y_king + 1) <= 7)
    {
      sum += piece_to_place(x_king + 1, y_king + 1, board);
    }

  else
    {
      sum += 1;
    }
   
  //---------------------------------------------------------------------

   if(board[(y_king)*8+(x_king+1)].color == board[y_king*8+x_king].color && board[(y_king)*8+(x_king+1)].type != 0 && (x_king + 1) <= 7 && (x_king + 1) >= 0 &&  (y_king) >= 0 &&  (y_king) <= 7)
     {
       sum += 1;
     }


   if ((x_king + 1) <= 7 && (x_king + 1) >= 0 &&  (y_king) >= 0 &&  (y_king) <= 7)
     {
       sum += piece_to_place(x_king + 1, y_king, board);
     }

   else
     {
       sum += 1;
     }

  //---------------------------------------------------------------------

  if(board[(y_king+1)*8+(x_king)].color == board[y_king*8+x_king].color && board[(y_king+1)*8+(x_king)].type != 0 && (x_king) <= 7 && (x_king) >= 0 &&  (y_king + 1) >= 0 &&  (y_king + 1) <= 7)
    {
      sum += 1;
    }
   
  if ((x_king) <= 7 && (x_king) >= 0 &&  (y_king + 1) >= 0 &&  (y_king + 1) <= 7)
    {
      sum += piece_to_place(x_king, y_king+1, board);
    }

  else
    {
      sum += 1;
    }

  //---------------------------------------------------------------------


   
  if(board[(y_king-1)*8+(x_king+1)].color == board[y_king*8+x_king].color && board[(y_king-1)*8+(x_king+1)].type != 0 && (x_king + 1) <= 7 && (x_king + 1) >= 0 &&  (y_king - 1) >= 0 &&  (y_king - 1) <= 7)
    {
      sum += 1;
    }
  
  if ((x_king + 1) <= 7 && (x_king + 1) >= 0 &&  (y_king - 1) >= 0 &&  (y_king - 1) <= 7)
    {
      sum += piece_to_place(x_king + 1, y_king - 1, board);
    }

  else
    {
      sum += 1;
    }

  //---------------------------------------------------------------------


   if(board[(y_king+1)*8+(x_king-1)].color == board[y_king*8+x_king].color && board[(y_king+1)*8+(x_king-1)].type != 0 && (x_king - 1) <= 7 && (x_king - 1) >= 0 &&  (y_king + 1) >= 0 &&  (y_king + 1) <= 7)
     {
       sum += 1;
     }
   if ((x_king - 1) <= 7 && (x_king - 1) >= 0 &&  (y_king + 1) >= 0 &&  (y_king + 1) <= 7)
     {
       sum += piece_to_place(x_king - 1, y_king + 1, board);
     }

   else
     {
       sum += 1;
     }

  //---------------------------------------------------------------------

  
   if(piece_to_place(x_king, y_king, board) == 0 && sum == 8 &&  othermove_pat(board) == 0)
     {
       return 1;
     }

  return 0; 

}

