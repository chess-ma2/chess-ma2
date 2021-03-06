#include "pieces.h"
#include "plate.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>


/*

File main.c containing all the functions relating the a game.
By Marie Maturana & Antoine
Start the 2021-03-04

*/

/**
 * @author Marie Maturana & Antoine
 * @date Start 06/03/2021
 * @details Small print of board for debug the game
 * @param board the board of the game
 */
void display(struct Piece *board)
{
  printf("   ");
  for(int y = 0; y < 8; y++)
    {
      printf(" %c:   ",y+'A'); 
    }
  printf("\n");
  for(int y = 0; y < 8; y++) 
    {
      printf("%d: ",y+1);

      for(int x = 0; x < 8; x++)
	{
	  if(board[y*8+x].type != NONE)
	    {
	      printf("(%d|%d)", board[y*8+x].color,board[y*8+x].type ); //print the color and the type of the piece
	    }
	  else
	    {
	      printf("     ");
	    }
	  printf(" ");
	}
      printf("\n");
    }

}


/*

Name of the function : rules
Function for a chess game
Called all the functions needed 
By Marie Maturana
Start the 2021-03-04

*/
int rules()
{

  return 0;
   
}
