#include "plate.h"
#include "pieces.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "check_and_pat.h"

//autres mouvements possibles pour arreter le echec et mat
// return 1
//return 0

int checkmat_secondcondition(int x_king, int y_king, int color,  struct Piece *board)
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
		  struct Piece * board2 = calloc(8*8, sizeof(struct Piece));

		  for( int i = 0; i < 64; i++)
		    {
		      board2[i].type = board[i].type;
		      board2[i].color = board[i].color;
		    }

		  if( color == board2[y*8+x].color)
		    { 
		   
		      if(isValidMove(x, y, des_x, des_y, board2) == 1)
			{

			  if(board2[y*8+x].type == KING)
			    { 
			      x_king = des_x;
			      y_king = des_y;
			    }
			  
			  
			  board2 = pieceMove(x, y, des_x, des_y, board2);


			  if (piece_to_place( x_king, y_king,board2)== 0)
			    {
			      return 1; 
			    }			
	 
			}

		      x_king = tmp1;
		      y_king = tmp2;

		      free(board2); 
	  
		    }
		}
	    }
	 
	}

    }
      

  return 0;
 
}


int checkking_and_aroud(int place_king_x, int place_king_y, int x_place, int y_place,struct Piece *board)
{

  struct Piece * board2 = calloc(8*8, sizeof(struct Piece));

  for( int i = 0; i < 64; i++)
   {
      board2[i].type = board[i].type;
      board2[i].color = board[i].color;
   }
    
  if(isValidMove(place_king_x, place_king_y, x_place, y_place, board2) == 0)
    {
      return 0; 
    }

  board2 = pieceMove(place_king_x, place_king_y, x_place, y_place, board2);
  
  for(int y = 0; y < 8; y++) 
    {
      for(int x = 0; x < 8; x++)
	{
	  if(kingcheck_place(x_place, y_place, x, y, board2) == 1)
	    {
	      return 1;
	    }
	}
    }

  free(board2); 

  return 0;
  
}


//d'autres mouvements possibles si pat
//return 0 si possible
// sinon return 1

int othermove_pat1(struct Piece *board)
{

  for(int y = 0; y < 8; y++) 
    {
      for(int x = 0; x < 8; x++)
	{
	  if(othermove_pat2(x, y, board) == 1)
	    {
	      return 1;
	    }
	}
    }

  return 0;
}


int othermove_pat2(int x_place, int y_place,struct Piece *board)
{

  for(int y = 0; y < 8; y++) 
    {
      for(int x = 0; x < 8; x++)
	{
	  if(isValidMove(x_place, y_place, x, y, board) == 1)
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
	  if(board[y*8+x].color != board[y_place*8+x_place].color && kingcheck_place(x_place, y_place, x, y, board) == 1)
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
      sum += checkking_and_aroud(x_king, y_king,x_king - 1, y_king, board); 
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
      sum +=checkking_and_aroud(x_king, y_king,x_king , y_king-1, board); 
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
      sum += checkking_and_aroud(x_king, y_king,x_king - 1, y_king-1, board); 
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
      sum += checkking_and_aroud(x_king, y_king,x_king + 1, y_king + 1, board); 
      
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
      sum += checkking_and_aroud(x_king, y_king,x_king + 1, y_king, board); 
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
      sum += checkking_and_aroud(x_king, y_king,x_king , y_king+ 1, board); 
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
      sum += checkking_and_aroud(x_king, y_king,x_king + 1, y_king -1, board); 
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
      sum += checkking_and_aroud(x_king, y_king,x_king - 1, y_king + 1, board); 
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


int check_mat(int x_king, int y_king, int color, struct Piece *board)
{
  if(checkmat_firstcondition(x_king, y_king, board) == 1 && checkmat_secondcondition(x_king, y_king, color, board) == 0)
    {
      return 1;
    }

    return 0; 
} 

int pat(int x_king, int y_king, struct Piece *board)
{
  
  int sum = 0;

    if(board[(y_king)*8+(x_king-1)].color == board[y_king*8+x_king].color && board[(y_king)*8+(x_king-1)].type != 0 && (x_king - 1) <= 7 && (x_king - 1) >= 0 &&  y_king >= 0 &&  y_king <= 7)
    {
      sum += 1; 
    }

  else if ((x_king - 1) <= 7 && (x_king - 1) >= 0 &&  y_king >= 0 &&  y_king <= 7)
    {
      sum += checkking_and_aroud(x_king, y_king,x_king - 1, y_king, board); 
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
      sum +=checkking_and_aroud(x_king, y_king,x_king , y_king-1, board); 
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
      sum += checkking_and_aroud(x_king, y_king,x_king - 1, y_king-1, board); 
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
      sum += checkking_and_aroud(x_king, y_king,x_king + 1, y_king + 1, board); 
      
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
      sum += checkking_and_aroud(x_king, y_king,x_king + 1, y_king, board); 
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
      sum += checkking_and_aroud(x_king, y_king,x_king , y_king+ 1, board); 
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
      sum += checkking_and_aroud(x_king, y_king,x_king + 1, y_king -1, board); 
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
      sum += checkking_and_aroud(x_king, y_king,x_king - 1, y_king + 1, board); 
    }

  else
    {
      sum += 1; 
    }
  
   if(piece_to_place(x_king, y_king, board) == 0 && sum == 8 &&  othermove_pat1(board) == 0)
     {
       return 1;
     }

  return 0; 

}

