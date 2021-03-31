#include "pieces.c"
#include "check_and_pat.c"
#include "plate.c"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/*

File rules.c containing all the functions relating the a game.
By Marie Maturana & Antoine
Start the 2021-03-04

*/


/**
 * @author Marie Maturana & Antoine
 * @date Start 04/03/2021
 * @details Small print of board for debug the game 
 * @param print the board of the game
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
  //-----------------------------------necessary variables-----------------------------------
  
  int answer = 0; // answer oth the nulle proposition
  
  int x = 0; 
  int y = 0;
  int des_x = 0;
  int des_y = 0;

  //kings'positions to know if check or checkmat

  int x_kingb = 4 ; 
  int y_kingb = 0;
  int x_kingw = 4;
  int y_kingw = 7; 

  int winner = 0; //1 = white win else black 
  
  enum turn player_turn = WHITETURN; // team's turn
  
  enum rock white_rock = CAN_ROCK; 
  enum rock black_rock = CAN_ROCK;
  
  enum king_status white_kingstatus = NOTHING;
  enum king_status black_kingstatus = NOTHING;
  
  struct Piece *board = init_board();

  //---------------------------------------------------------------------------------------------------------

  display(board); //display the first board

  //-------------------------------------START OF THE GAME---------------------------------------------------
  
  while( white_kingstatus != CHECKMATE || black_kingstatus != CHECKMATE ) //continue while not chessmate
    {
      printf("\n\n");
  
      printf("Entrez une valeur : \n");
  
      scanf("%d%d%d%d", &x, &y, &des_x, &des_y); //ask positions to the player


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

	      scanf("%d", &answer);

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
	      continue; 
	    
	    }
	  else
	    {
	      printf("\nL'adversaire (noir) demande la nulle. Tapez 1 si vous accepter sinon tapez 0\n");

	      scanf("%d", &answer);

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
	      continue; 
	    }
	}

      //------------------------------------------TURN PB-------------------------------------


      if(player_turn == WHITETURN && board[(y-1)*8+(x-1)].color == BLACK && board[(y-1)*8+(x-1)].type != NONE)
	{
	  printf("\nVous avez sélectionner une pièce de l'adversaire\n");
	  continue; 
	}
      if(player_turn == BLACKTURN && board[(y-1)*8+(x-1)].color == WHITE && board[(y-1)*8+(x-1)].type != NONE)
	{
	  printf(" \nVous avez sélectionner une pièce de l'adversaire\n");
	  continue; 
	}

      //------------------------------------------------ROCK---------------------------------
      
      if( player_turn == WHITETURN && white_kingstatus == NOTHING && white_rock == CAN_ROCK && board[(y-1)*8+(x-1)].color == WHITE && board[(y-1)*8+(x-1)].type == KING)
	{	  
	  int possible_rock = isValidMove_Rock( x - 1, y-1, des_x-1, des_y-1, board[(y-1)*8+(x-1)].color, board);

	  if (possible_rock == 1)
	    {
	  
	      board = pieceMove_Rock(x-1, y-1, des_x-1, des_y-1, board);

	      x_kingw = des_x - 1; 
	      y_kingw = des_y - 1;

	      if(piece_to_place(x_kingw, y_kingw, board) == 1)
		{
		  board = pieceMove(des_x-1, des_y-1, x-1, y-1, board);
		  printf("Mouvement impossible car ton roi est en échec dans cette position\n");
		    
		  x_kingw = x - 1; 
		  y_kingw = y - 1;

		  if( x - 1 == 4 && y - 1 == 7) 
		    {
		      if(des_x - 1 == 6 && des_y - 1 == 7) //little rock
			{
			  board[7*8+7].type = ROOK;
			  board[7*8+7].color = WHITE;
			  board[7*8+5].type = NONE;
			  board[7*8+5].color = 0;
			}
		      if (des_x - 1 == 2 && des_y - 1 == 7) //big rock
			{
			  board[7*8+0].type = ROOK;
			  board[7*8+0].color = WHITE;
			  board[7*8+3].type = NONE;   
			  board[7*8+3].color = 0;
			    
			}
		    }

		  continue; 
		}
	  
	      if(player_turn == WHITETURN) 
		{
		  player_turn = BLACKTURN; 
		}
	      else
		{
		  player_turn = WHITETURN; 
		}

	      white_rock = CANT_ROCK;

	      display(board); 

	      continue; 

	    }

	} 

      if( player_turn == BLACKTURN && black_kingstatus == NOTHING && black_rock == CAN_ROCK && board[(y-1)*8+(x-1)].color == BLACK && board[(y-1)*8+(x-1)].type == KING)
	{
	  int possible_rock = isValidMove_Rock( x - 1, y-1, des_x -1, des_y -1, board[(y-1)*8+(x-1)].color, board);

	  if (possible_rock == 1)
	    {
	      
	      board = pieceMove_Rock(x-1, y-1, des_x-1, des_y-1, board);

	      x_kingb = des_x - 1; 
	      y_kingb = des_y - 1;

	      if(piece_to_place(x_kingb, y_kingb, board) == 1)
		{
		  board = pieceMove(des_x-1, des_y-1, x-1, y-1, board);
		  printf("Mouvement impossible car ton roi est en échec dans cette position\n");
		 
		  x_kingb = x - 1; 
		  y_kingb = y - 1;


		  if( x - 1 == 4 && y - 1 == 0)  
		    {
		      if(des_x - 1 == 6 && des_y - 1 == 0) //litte rock 
			{
			  board[0*8+7].type = ROOK;
			  board[0*8+7].color = BLACK; 
			  board[0*8+5].type = NONE;
			  board[0*8+5].color = 0;
			    
			}
		      if (des_x - 1 == 2 && des_y - 1 == 0) //big rock
			{

			  board[0*8+0].type = ROOK;
			  board[0*8+0].color = BLACK; 
			  board[0*8+3].type = NONE;
			  board[0*8+3].color = 0;
			    
			}
		    
		      continue; 
		    }
		}
        
	  
	      if(player_turn == WHITETURN)//change the player turn
		{
		  player_turn = BLACKTURN; 
		}
	      else
		{
		  player_turn = WHITETURN; 
		}

	      black_rock = CANT_ROCK;
	      
	      display(board); 

	      continue; 

	    }
	}

      //---------------------------------------------DIFFERENT ERRORS----------------------------------------------------
	 
      int possible = isValidMove(x-1, y-1, des_x-1, des_y-1, board); //movement is possible

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

      //--------------------------------------------------------------------------------------------------------------------------------------
	  
      if (possible == 1)
	{

	  if(board[(y-1)*8+(x-1)].color == WHITE && board[(y-1)*8+(x-1)].type == KING) //change position of the king to help check/pat/checkmat
	    {
	      x_kingw = des_x - 1; 
	      y_kingw = des_y - 1;
	      white_rock = CANT_ROCK;
	      
	    }

	  if(board[(y-1)*8+(x-1)].color == BLACK && board[(y-1)*8+(x-1)].type == KING)
	    {
	      x_kingb = des_x - 1; 
	      y_kingb = des_y - 1;
	      black_rock = CANT_ROCK;
	    }

	  board = pieceMove(x-1, y-1, des_x-1, des_y-1, board); //move and update the new board
	  
	  if(player_turn == BLACKTURN && piece_to_place(x_kingb, y_kingb, board) == 1)
	    {
	      board = pieceMove(des_x-1, des_y-1, x-1, y-1, board);
	      printf("Mouvement impossible car ton roi est en échec dans cette position\n");
	      if(board[(y-1)*8+(x-1)].color == BLACK && board[(y-1)*8+(x-1)].type == KING) //change position of the king to help check/pat/checkmat
		{
		  x_kingb = x - 1; 
		  y_kingb = y - 1;
		}
	      continue; 
	    }

	  if(player_turn == WHITETURN && piece_to_place(x_kingw, y_kingw, board) == 1)
	    {
	      board = pieceMove(des_x-1, des_y-1, x-1, y-1, board);
	      printf("Mouvement impossible car ton roi est en échec dans cette position\n");
	      if(board[(y-1)*8+(x-1)].color == WHITE && board[(y-1)*8+(x-1)].type == KING) //change position of the king to help check/pat/checkmat
		{
		  x_kingw = x - 1; 
		  y_kingw = y - 1;
		}
	      continue; 
	    }

	  if(player_turn == BLACKTURN && kingcheck_place(x_kingw, y_kingw, des_x-1, des_y-1, board) == 1)
	    {
	      white_kingstatus = CHECK;
	      printf("Echec : le roi blanc est en échec \n"); 
	    }

	  if(player_turn == WHITETURN && kingcheck_place( x_kingb, y_kingb, des_x-1, des_y-1, board) == 1)
	    {
	      black_kingstatus = CHECK;
	      printf("Echec : le roi noir est en échec \n"); 
	    }

	  if(player_turn == BLACKTURN && kingcheck_place(x_kingb, y_kingb, des_x-1, des_y-1, board) == 0)
	    {
	      black_kingstatus = NOTHING;
	    }

	  if(player_turn == WHITETURN && kingcheck_place( x_kingw, y_kingw, des_x-1, des_y-1, board) == 0)
	    {
	      white_kingstatus = NOTHING; 
	    }

	  if(player_turn == WHITETURN && check_mat(x_kingb, y_kingb, BLACK, board)== 1) //check if I put the opponent king in checkmat
	    {
	      black_kingstatus = CHECKMATE;
	      winner = 1 ;
	      display(board); 
	      break; 
	    }
	  if(player_turn == BLACKTURN && check_mat(x_kingw, y_kingw, WHITE,  board)== 1)
	    {
	      white_kingstatus = CHECKMATE;
	      winner = 0;
	      display(board); 
	      break; 
	    }

	  if(player_turn == WHITETURN && pat(x_kingb, y_kingb, board)) //check if I put the opponent king in pat
	    {
	      black_kingstatus = PAT;
	      winner = 2 ;
	      printf("EGALITÉ\n");
	      return 0;
	    }
	  if(player_turn == BLACKTURN && pat(x_kingw, y_kingw, board))
	    {
	      white_kingstatus = PAT;
	      winner = 2;
	      printf("EGALITÉ\n");
	      return 0;
	    }
	   	  
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

  //-------------------------------------------------PRINT WHO IS THE WINNER----------------------------------------------------

  if(winner == 1)
    {
      printf("Les blancs ont gagnés \n");
    }

  if(winner == 0)
    {
      printf("Les noirs ont gagnés \n");
    }

  free(board);

  return 0;
   
}
