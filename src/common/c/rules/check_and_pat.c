#include "plate.h"
#include "pieces.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "check_and_pat.h"

/**
 * @author Marie Maturana 
 * @date Start 23/03/2021
 * @details File .c containing all the functions relating to the check, pat and checkmat
 */

#ifndef CHECK_AND_PAT_C
#define CHECK_AND_PAT_C

/**
 * @author Marie Maturana 
 * @date Start 29/03/2021
 * @details see if an other movement can be make for stop the checkmat
 * @return  1 if an othen movement can be make / 0 else
 */

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
                    free(board2);
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



/**
 * @author Marie Maturana 
 * @date Start 29/03/2021
 * @details create new board to see if the king in in check at this place
 * @return  1 if king in check / 0 else
 */

int checkking_and_aroud(int place_king_x, int place_king_y, int x_place, int y_place,struct Piece *board)
{

  struct Piece * board2 = calloc(8*8, sizeof(struct Piece)); //create a new board just for tesr and move the king aroud himself

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



/**
 * @author Marie Maturana 
 * @date Start 27/03/2021
 * @details check if other movement can be make in the king is in pat
 * @return  1 other moves possible / 0 else
 */

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



/**
 * @author Marie Maturana 
 * @date Start 27/03/2021
 * @details see if the king is in check at this place
 * @return 1 if king in check / 0 else
 */

int kingcheck_place(int x_king, int y_king, int x_piece, int y_piece, struct Piece *board)
{
  
  if( board[y_king*8+x_king].color != board[y_piece*8+x_piece].color )
    {

      if(isValidMove(x_piece, y_piece, x_king, y_king, board) == 1) //movement possible so check
	{ 
	  return 1 ;
	} 
    } 

  return 0; 
  
}



/**
 * @author Marie Maturana 
 * @date Start 27/03/2021
 * @details test for all the pieces if the king is in check at this place
 * @return 1 if king in check around himself / 0 else
 */

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


/**
 * @author Marie Maturana 
 * @date Start 27/03/2021
 * @details test if the king is in check all around himself and at his place
 * @return 1 if king in check around himself / 0 else
 */

int checkmat_firstcondition(int x_king, int y_king, struct Piece *board)
{

  int sum = 0;

  //---------------------------------------------------------------------

  //test if is in check with the new coordonate aroud the king
  if(board[(y_king)*8+(x_king-1)].color == board[y_king*8+x_king].color && board[(y_king)*8+(x_king-1)].type != 0 && (x_king - 1) <= 7 && (x_king - 1) >= 0 &&  y_king >= 0 &&  y_king <= 7)
    {
      sum += 1; 
    }

  else if ((x_king - 1) <= 7 && (x_king - 1) >= 0 &&  y_king >= 0 &&  y_king <= 7) //coordonate next to the plate
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

  if(sum == 9) //if all the place in check for the king
    {
      return 1;
    }

  return 0; 

}


/**
 * @author Marie Maturana 
 * @date Start 27/03/2021
 * @details test if the king is in check and for that test the 2 conditions
 * @return 1 if king in checkmate / 0 else
 */


int check_mat(int x_king, int y_king, int color, struct Piece *board)
{
  if(checkmat_firstcondition(x_king, y_king, board) == 1 && checkmat_secondcondition(x_king, y_king, color, board) == 0) //valid all the condition for a check mat 
    {
      return 1;
    }

    return 0; 
}

/**
 * @author Marie Maturana 
 * @date Start 27/03/2021
 * @details test if the king is in pat => check all around him and not other moves
 * @return 1 if king in pat / 0 else
 */

int pat(int x_king, int y_king, struct Piece *board)
{
  
  int sum = 0;
  
  //try with coordonate aroud the king 
    if(board[(y_king)*8+(x_king-1)].color == board[y_king*8+x_king].color && board[(y_king)*8+(x_king-1)].type != 0 && (x_king - 1) <= 7 && (x_king - 1) >= 0 &&  y_king >= 0 &&  y_king <= 7)
    {
      sum += 1; 
    }

    else if ((x_king - 1) <= 7 && (x_king - 1) >= 0 &&  y_king >= 0 &&  y_king <= 7) //cordonnate not next the plate
    {
      sum += checkking_and_aroud(x_king, y_king,x_king - 1, y_king, board); 
    }

    else //other piece on the place
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
  
  if(piece_to_place(x_king, y_king, board) == 0 && sum == 8 &&  othermove_pat1(board) == 0) //if other movement can be make, all the place around in check and not check at the adverse king = pat 
     {
       return 1;
     }

  return 0; 

}

#endif

