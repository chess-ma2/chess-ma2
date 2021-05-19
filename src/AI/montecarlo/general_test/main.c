/**
 * @author Marie
 * @date Start 29/04/2021
 * @details test for see if the AI is working
 */


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../../../common/c/rules/plate.h"
#include "../../../common/c/rules/check_and_pat.h"
#include "../tree/create_childs.h"
#include "../search_and_play/monte_carlo_method.h"
#include "../tree/mcts.h"





/**
 * @author Marie
 * @date Start 19/04/2021
 * @details main function to test if the list of moves for child nodes 
 */


int main()
{

  srand(time(NULL));
    //-----------------------------------necessary variables-----------------------------------
  
  int answer = 0; // answer oth the nulle proposition
  
  int x = 0; 
  int y = 0;
  int des_x = 0;
  int des_y = 0;

  //kings'positions to know if check or checkmat

  int x_kingb = 4 ; //coordonate x of the black king
  int y_kingb = 0;  //coordonate y of the black king
  int x_kingw = 4;  //coordonate x of the white king
  int y_kingw = 7;   //coordonate y of the white king

  int winner = 0; //1 = white win else black 
  
  enum turn player_turn = WHITETURN; // team's turn
  
  enum rock white_rock = CAN_ROCK; //situation of the rock for the white team
  enum rock black_rock = CAN_ROCK;  //situation of the rock for the black team
  
  enum king_status white_kingstatus = NOTHING; // to know is the king is in check, checkmate ou pat
  enum king_status black_kingstatus = NOTHING;
  
  struct Piece *board = init_board(); //positionate de pieces one the piece cf funtion on plate.c

  struct MCTS_Node *tree_game = malloc(sizeof(struct MCTS_Node));
  tree_game = create_tree(board, 0, tree_game);

  printf("arbre done\n");

  //---------------------------------------------------------------------------------------------------------

  display(board); //display the first board with any movements

  //-------------------------------------START OF THE GAME---------------------------------------------------
  
  while( white_kingstatus != CHECKMATE || black_kingstatus != CHECKMATE ) //continue while not chessmate for any king
    {

      if (player_turn == WHITETURN)
	{
	  printf("\n\n");
  
	  printf("Entrez une valeur : \n");
  
	  scanf("%d%d%d%d", &x, &y, &des_x, &des_y); //ask positions to the player
	}

      if (player_turn == BLACKTURN)
	{
	  printf("\n\n");
  
	  printf("L'intelligence artificielle est entrain de jouer : \n");

	  tree_game = select_good_node(board, tree_game);

	  print_node_and_child(tree_game); 
	  
	  tree_game = chosen_best(tree_game);

	  //print_node(tree_game); 

	  printf("selec tthe best node move to play \n");

	  struct coordonates_moves *coordonates = malloc(sizeof(struct coordonates_moves));
	  coordonates = coordonates_by_mc(board, 0, coordonates, tree_game);

	  x = coordonates->x + 1;
	  y = coordonates->y + 1;
	  des_x = coordonates->x_des + 1;
	  des_y = coordonates->y_des + 1;

	  printf("%d      %d       %d       %d\n", x,y,des_x,des_y);
	}

      //--------------------------abandonment--------------------------------
      
      if( x == -1 && y == -1 && des_x == -1 && des_y == -1) //if the 4 coordinates a -1 == ask abandonment
	{
	  if( player_turn == WHITETURN) //if white turn, white ask abandonment and black win
	    {
	      winner = 0;
	      printf("\nL'adversaire (blanc) déclare l'abandon.\n");
	      printf("\nLes noirs ont gagnés.\n");
	      return 0;
	    }
	  else //if black turn, black ask abandonment and white win
	    {
	      winner = 1;
	      printf("\nL'adversaire (noir) déclare l'abandon.\n");
	      printf("\nLes blancs ont gagné.\n");
	      return 0;
	    }
	    
	}

      //-----------------------------nulle-------------------------------------

      if( x == 0 && y == 0 && des_x == 0 && des_y == 0)  //if the 4 coordinates a 0 == ask draw
	{
	  if( player_turn == WHITETURN) //if white turn, white ask the draw
	    {
	     
	      printf("\nL'adversaire (blanc) demande la nulle. Tapez 1 si vous accepter sinon tapez 0 \n");

	      scanf("%d", &answer);

	      if( answer == 1) //adverse king accept = 0 winner
		{
		  winner = 2; //nobody win
		  printf("\nL'adversaire (noir) accepte la nulle.\n");
		  printf("EGALITÉ\n");
		  return 0;
		}
	      else //adverse king refuse = game continue
		{
		  printf("\nL'adversaire (noir) refuse la nulle.\n");
		  printf("La partie continue.\n");
		}

	      player_turn = BLACKTURN;
	      continue; 
	    
	    }
	  else   //if black turn, black ask the nulle 
	    {
	      printf("\nL'adversaire (noir) demande la nulle. Tapez 1 si vous accepter sinon tapez 0\n");

	      scanf("%d", &answer);

	      if( answer == 1)//adverse king accept = 0 winner
		{
		  winner = 2; //nobody win
		  printf("\nL'adversaire (blanc) accepte la nulle.\n");
		  printf("EGALITÉ\n");
		  return 0;
		}
	      else //adverse king refuse = game continue
		{
		  printf("\nL'adversaire (blanc) refuse la nulle.\n");
		  printf("La partie continue.\n");
		}

	      player_turn = WHITETURN;
	      continue; 
	    }
	}

      //------------------------------------------TURN PB-------------------------------------


      if(player_turn == WHITETURN && board[(y-1)*8+(x-1)].color == BLACK && board[(y-1)*8+(x-1)].type != NONE) //select an adverse piece
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
      //white rock
      if( player_turn == WHITETURN && white_kingstatus == NOTHING && white_rock == CAN_ROCK && board[(y-1)*8+(x-1)].color == WHITE && board[(y-1)*8+(x-1)].type == KING)
	{	  
	  int possible_rock = isValidMove_Rock( x - 1, y-1, des_x-1, des_y-1, board[(y-1)*8+(x-1)].color, board); //if the rock is possible ...

	  if (possible_rock == 1)
	    {
	  
	      board = pieceMove_Rock(x-1, y-1, des_x-1, des_y-1, board); //make the rock

	      x_kingw = des_x - 1; //change de coordonate of the king : alway know where is the king for the pat or check functions
	      y_kingw = des_y - 1;

	      if(piece_to_place(x_kingw, y_kingw, board) == 1) //if a piece put un check the king remove the movement
		{
		  board = pieceMove(des_x-1, des_y-1, x-1, y-1, board);
		  printf("Mouvement impossible car ton roi est en échec dans cette position\n");
		    
		  x_kingw = x - 1; //rechange the coordonates of the king
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
	  
	      if(player_turn == WHITETURN) //change turn after make the rock 
		{
		  player_turn = BLACKTURN; 
		}
	      else
		{
		  player_turn = WHITETURN; 
		}

	      white_rock = CANT_ROCK;

	      display(board); //show the new bord 

	      continue; 

	    }

	}

      //idem than for the white team

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
	 
      int possible = isValidMove(x-1, y-1, des_x-1, des_y-1, board); //see if movement is possible

      if (possible == 0) //not a good movement 
	{
	  printf("Le mouvement n'est pas possible.\n");
	}

      if (possible == 2) //coordonates not in the plate
	{
	  printf("Le mouvement n'est pas possible car une ou plusieurs des coordonnées données se trouve hors du plateau.\n");
	}
	  
      if (possible == 3) //same piece color at destination
	{
	  printf("Le mouvement n'est pas possible car il y a une piece de la même couleur sur la case de la destination que sur celle de départ.\n");
	}
	  
      if (possible == 4) //you don't select a piece
	{
	  printf("Le mouvement n'est pas possible car vous n'avez sélectionné aucune piece à bouger.\n");
	}

      //--------------------------------------------------------------------------------------------------------------------------------------
	  
      if (possible == 1) //the movement is possible
	{

	  if(board[(y-1)*8+(x-1)].color == WHITE && board[(y-1)*8+(x-1)].type == KING) //change position of the king to help check/pat/checkmat if the piece is a king
	    {
	      x_kingw = des_x - 1; 
	      y_kingw = des_y - 1;
	      white_rock = CANT_ROCK; //when the king move, it cant make the rock after
	      
	    }

	  if(board[(y-1)*8+(x-1)].color == BLACK && board[(y-1)*8+(x-1)].type == KING)
	    {
	      x_kingb = des_x - 1; 
	      y_kingb = des_y - 1;
	      black_rock = CANT_ROCK; //when the king move it cant make the rock after
	    }

	  board = pieceMove(x-1, y-1, des_x-1, des_y-1, board); //move and update the new board
	  
	  if(player_turn == BLACKTURN && piece_to_place(x_kingb, y_kingb, board) == 1) //if your king is in check at this new place, remove the movment
	    {
	      board = pieceMove(des_x-1, des_y-1, x-1, y-1, board);
	      printf("Mouvement impossible car ton roi est en échec dans cette position\n");
	      if(board[(y-1)*8+(x-1)].color == BLACK && board[(y-1)*8+(x-1)].type == KING) //change position of the king to help check/pat/checkmat
		{
		  x_kingb = x - 1; //rechange position
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

	  if(player_turn == BLACKTURN && kingcheck_place(x_kingw, y_kingw, des_x-1, des_y-1, board) == 1) //put the adverse king in check
	    {
	      white_kingstatus = CHECK;
	      printf("Echec : le roi blanc est en échec \n"); 
	    }

	  if(player_turn == WHITETURN && kingcheck_place( x_kingb, y_kingb, des_x-1, des_y-1, board) == 1) //put the adverse king in check
	    {
	      black_kingstatus = CHECK;
	      printf("Echec : le roi noir est en échec \n"); 
	    }

	  if(player_turn == BLACKTURN && kingcheck_place(x_kingb, y_kingb, des_x-1, des_y-1, board) == 0) //valid if the king is not in check now
	    {
	      black_kingstatus = NOTHING;
	    }

	  if(player_turn == WHITETURN && kingcheck_place( x_kingw, y_kingw, des_x-1, des_y-1, board) == 0)
	    {
	      white_kingstatus = NOTHING; 
	    }

	  if(player_turn == WHITETURN && check_mat(x_kingb, y_kingb, BLACK, board)== 1) //check if I put the opponent king in checkmat and I win
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
	   	  
	  if(player_turn == WHITETURN) //change the player turn after this movement 
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

  return 0; //end of the main function
   
} 
