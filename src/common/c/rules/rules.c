#include "pieces.c"
#include "plate.c"
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
  int res; //ask positions
  
  int nulle; //if ask nulle
  
  int answer = 0; // answer oth the nulle proposition
  
  int x = 0; 
  int y = 0;
  int des_x = 0;
  int des_y = 0;

  int winner; //1 = white win else black 
  
  enum turn player_turn = WHITETURN; // team's turn
  
  enum rock white_rock = CAN_ROCK; 
  enum rock black_rock = CAN_ROCK;
  
  enum king_status white_kingstatus = NOTHING;
  enum king_status black_kingstatus = NOTHING;
  
  struct Piece *board = init_board();

  display(board); //display the first board
  
  while( white_kingstatus != CHECKMATE || black_kingstatus != CHECKMATE ) //continue while not chessmate
    {
      printf("\n\n");
  
      printf("Entrez une valeur : \n");
  
      res = scanf("%d%d%d%d", &x, &y, &des_x, &des_y); //ask positions to the player


      //--------------------------abandonment--------------------------------
      
      if( x == -1 && y == -1 && des_x == -1 && des_y == -1) 
	{
	  if( player_turn == WHITETURN)
	    {
	      winner = 0;
	      printf("\nL'adversaire (blanc) déclare l'abandon.\n");
	      printf("\nLes noirs ont gagnés.\n");
	      return 0;
	    }
	  else
	    {
	      winner = 1;
	      printf("\nL'adversaire (noir) déclare l'abandon.\n");
	      printf("\nLes blancs ont gagné.\n");
	      return 0;
	    }
	    
	}

      //-----------------------------nulle-------------------------------------

      if( x == 0 && y == 0 && des_x == 0 && des_y == 0)
	{
	  if( player_turn == WHITETURN)
	    {
	     
	      printf("\nL'adversaire (blanc) demande la nulle. Tapez 1 si vous accepter sinon tapez 0 \n");

	      nulle = scanf("%d", &answer);

	      if( answer == 1)
		{
		  winner = 2;
		  printf("\nL'adversaire (noir) accepte la nulle.\n");
		  printf("EGALITÉ\n");
		  return 0;
		}
	      else
		{
		  printf("\nL'adversaire (noir) refuse la nulle.\n");
		  printf("La partie continue.\n");
		}

	      player_turn = BLACKTURN;
	    
	    }
	  else
	    {
	      printf("\nL'adversaire (noir) demande la nulle. Tapez 1 si vous accepter sinon tapez 0\n");

	      nulle = scanf("%d", &answer);

	      if( answer == 1)
		{
		  winner = 2;
		  printf("\nL'adversaire (blanc) accepte la nulle.\n");
		  printf("EGALITÉ\n");
		  return 0;
		}
	      else
		{
		  printf("\nL'adversaire (blanc) refuse la nulle.\n");
		  printf("La partie continue.\n");
		}

	      player_turn = WHITETURN;
	    }
	}

      //--------------------------------------------------------------------------------------

      
      if(player_turn == WHITETURN && board[(y-1)*8+(x+1)].color == BLACK && board[(y-1)*8+(x+1)].type != NONE)
	{
	  printf("\nVous avez sélectionner une pièce de l'adversaire\n");  
	}
      else if(player_turn == BLACKTURN && board[(y-1)*8+(x+1)].color == WHITE && board[(y-1)*8+(x+1)].type != NONE)
	{
	  printf(" \nVous avez sélectionner une pièce de l'adversaire\n"); 
	}
      else if( white_rock == CAN_ROCK && board[(y-1)*8+(x+1)].color == WHITE && board[(y-1)*8+(x+1)].type == KING)
	{
	  int possible_rock = isValidMove_Rock( x - 1, y-1, des_x-1, des_y-1, board[(y-1)*8+(x+1)].color, board);
	  white_rock = CANT_ROCK;

	  if (possible_rock == 1)
	    {
	      board = pieceMove_Rock(x-1, y-1, des_x-1, des_y-1, board);
	  
	      if(player_turn == WHITETURN) 
		{
		  player_turn = BLACKTURN; 
		}
	      else
		{
		  player_turn = WHITETURN; 
		}

	    }
	}
      else if( black_rock == CAN_ROCK && board[(y-1)*8+(x+1)].color == BLACK && board[(y-1)*8+(x+1)].type == KING)
	{
	  int possible_rock = isValidMove_Rock( x - 1, y-1, des_x -1, des_y -1, board[(y-1)*8+(x+1)].color, board);
	  black_rock = CANT_ROCK;

	  if (possible_rock == 1)
	    {
	      board = pieceMove_Rock(x-1, y-1, des_x-1, des_y-1, board);
	  
	      if(player_turn == WHITETURN)//change the player turn
		{
		  player_turn = BLACKTURN; 
		}
	      else
		{
		  player_turn = WHITETURN; 
		}

	    }
	}

	 
      int possible = isValidMove(x-1, y-1, des_x-1, des_y-1, board); //movement is possible

      printf("%d", possible); 

      if (possible == 0)
	{
	  printf("Le mouvement n'est pas possible.\n");
	}

      if (possible == 2)
	{
	  printf("Le mouvement n'est pas possible car une ou plusieurs des coordonnées données se trouve hors du plateau.\n");
	}
	  
      if (possible == 3)
	{
	  printf("Le mouvement n'est pas possible car il y a une piece de la même couleur sur la case de la destination que sur celle de départ.\n");
	}
	  
      if (possible == 4)
	{
	  printf("Le mouvement n'est pas possible car vous n'avez sélectionné aucune piece à bouger.\n");
	}
	  
      if (possible == 1)
	{
	  board = pieceMove(x-1, y-1, des_x-1, des_y-1, board);
	  
	  if(player_turn == WHITETURN) //change the player turn
	    {
	      player_turn = BLACKTURN; 
	    }
	  else
	    {
	      player_turn = WHITETURN; 
	    }

	}
    


      display(board); //print the board after modifications

    }  

  return 0;
   
}