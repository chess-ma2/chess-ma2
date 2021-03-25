#include "plate.h"
#include "pieces.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>



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

int piece_to_place(int x_place, int y_place, struct Piece *board)
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

int check_mat(int x_king, int y_king, struct Piece *board)
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

int pat(int x_king, int y_king, struct Piece *board)
{

    int sum = 0;

  //---------------------------------------------------------------------
  
  if ((x_king - 1) <= 7 && (x_king - 1) >= 0 &&  y_king >= 0 &&  y_king <= 7)
    {
      sum += piece_to_place(x_king - 1, y_king, board);
    }

  else
    {
      sum += 1;
    }

  //---------------------------------------------------------------------

  if ((x_king) <= 7 && (x_king) >= 0 &&  (y_king - 1) >= 0 &&  (y_king-1) <= 7)
    {
      sum += piece_to_place(x_king, y_king - 1, board);
    }

  else
    {
      sum += 1;
    }
  
  //---------------------------------------------------------------------


  if ((x_king-1) <= 7 && (x_king-1) >= 0 &&  (y_king - 1) >= 0 &&  (y_king-1) <= 7)
    {
      sum += piece_to_place(x_king - 1, y_king - 1, board);
    }

  else
    {
      sum += 1;
    }

  //---------------------------------------------------------------------

  if ((x_king + 1) <= 7 && (x_king + 1) >= 0 &&  (y_king + 1) >= 0 &&  (y_king + 1) <= 7)
    {
      sum += piece_to_place(x_king + 1, y_king + 1, board);
    }

  else
    {
      sum += 1;
    }

  //---------------------------------------------------------------------

  if ((x_king + 1) <= 7 && (x_king + 1) >= 0 &&  (y_king) >= 0 &&  (y_king) <= 7)
    {
      sum += piece_to_place(x_king + 1, y_king, board);
    }

  else
    {
      sum += 1;
    }

  //---------------------------------------------------------------------

  if ((x_king) <= 7 && (x_king) >= 0 &&  (y_king + 1) >= 0 &&  (y_king + 1) <= 7)
    {
      sum += piece_to_place(x_king, y_king+1, board);
    }

  else
    {
      sum += 1;
    }

  //---------------------------------------------------------------------


    if ((x_king + 1) <= 7 && (x_king + 1) >= 0 &&  (y_king - 1) >= 0 &&  (y_king - 1) <= 7)
    {
      sum += piece_to_place(x_king + 1, y_king - 1, board);
    }

  else
    {
      sum += 1;
    }

  //---------------------------------------------------------------------


      if ((x_king - 1) <= 7 && (x_king - 1) >= 0 &&  (y_king + 1) >= 0 &&  (y_king + 1) <= 7)
    {
      sum += piece_to_place(x_king - 1, y_king + 1, board);
    }

  else
    {
      sum += 1;
    }

  //---------------------------------------------------------------------


  if(sum == 8)
    {
      return 1;
    }

  return 0; 
}
