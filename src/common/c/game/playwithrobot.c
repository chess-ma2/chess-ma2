#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../../client/c/network/game.c"
#include "../data/process_board.c"
//#include "../rules/rules.c"
#include "../rules/pieces.c"
#include "version1.c"
#include "../rules/check_and_pat.c"
#include "added_functions.c"
#include "../../../database/create_db.c"
#include "../../../database/functions_db.c"
#include "../../../AI/MiniMax/minimax.c"
#include "../../../AI/montecarlo/tree/create_childs.c"
#include "../../../AI/montecarlo/search_and_play/monte_carlo_method.c"
#include "../../../AI/montecarlo/tree/mcts.c"

#ifndef PLAYWITHROBOT_C
#define PLAYWITHROBOT_C


struct Player * makeRobot()
{
    struct Player * robot= malloc( sizeof(struct Player));
    robot->name = "MiniMaxAI";
    robot->email = "robychoux4052tropfortceminimax";
    robot->nb_won = 0;
    robot->nb_lost = 0;
    robot->team_color = 1;

    return robot;
}


//using nearly anna and marie 's function but a little adaptation
int playwrobot(struct Piece *board, struct Player *player1, int type)
{
  print_rules();
  //_______________ Variables
  int x = 0;
  char x_char = 'A';
  int y = 0;
  int des_x = 0;
  char des_x_char = 'A';
  int des_y = 0;

  // Current white chess pieces on chessboard
  struct currentpiece *currentW = create_whiteList();
  int nbWhite = 16;

  // Current black chess pieces on chessboard
  struct currentpiece *currentB = create_blackList();
  int nbBlack = 16;
  struct Player *robot = makeRobot();
  //kings'positions to know if check or checkmat

  int x_kingb = 4;
  int y_kingb = 0;
  int x_kingw = 4;
  int y_kingw = 7;

  enum turn player_turn = WHITETURN; // team's turn
  enum rock white_rock = CAN_ROCK;
  enum rock black_rock = CAN_ROCK;
  enum king_status white_kingstatus = NOTHING;
  enum king_status black_kingstatus = NOTHING;

  player1->team_color = 1; // Player is black
  robot->team_color = 0; // robot is white


  //_______________________________________________________________________________________________________________________________


  while( white_kingstatus != CHECKMATE || black_kingstatus != CHECKMATE ) //continue while not chessmate
    {
      printf("\n\n");

      //HERE entering the parameters for local game
      // Print the name of who's turn it is _________________________________________________________________
      if(player_turn == BLACKTURN)
      {
        printNAME(player1->email);
        printf(" (Black) ");
        printf(" it's your turn! \n\n");


      //______________________________________________________________________________________________________

      //Get original coordinates
      printf("Please enter the original coordinates of the chess piece you want to move (ex: A3) : \n");
      scanf(" %c%d", &x_char, &y);
      x = ((int)x_char) - 64;

      //Get new coordinates
      printf("Please enter the new coordinates of the chess piece you want to move (ex: B1) : \n");
      scanf(" %c%d", &des_x_char, &des_y);
      des_x = ((int)des_x_char) - 64;

      //__________________ Withdraw ______________________________________________________________________________________________

      if( x_char == 'W' && y == 0 && des_x_char == 'W' && des_y == 0)
	    {
        return withdraw(player_turn, player1, robot);
	     }

      //__________________ If Stalemate ______________________________________________________________________________________________

      if(x_char == 'S' && y == 0 && des_x_char == 'S' && des_y == 0)
	    {
           struct res_stalemate res = stalemate(player_turn, player1, robot);

           if (res.answer == 0)
            {return 0;}
          else
            {player_turn = res.player_turn;}
	     }

      //--------------------------------------------------------------------------------------
      // Make sure the coordonates are correct
      while(incorrect_char(x_char) || incorrect_int(y))
      {
        printf(URED "Oops... you haven't entered correct coordinates please try again \n" reset);
        printf("Please enter the original coordinates of the chess piece you want to move (ex: A3) : \n");
        scanf(" %c%d\n", &x_char, &y);
      }
      x = ((int)x_char) - 64;

      // It's not your piece to move
      if( board[(y-1)*8+(x+1)].color == WHITE && board[(y-1)*8+(x+1)].type != NONE)
	    {
	       printf(URED "\n That isn't your chess piece to move. \n" reset);
         continue;
	     }

      //____________________________________ Game settings _____________________________________________________________
      //Rock
      struct res_rock res = rock_sub( player_turn, board, white_kingstatus, black_kingstatus, white_rock, black_rock, x_kingb, y_kingb, x_kingw, y_kingw, x, y, des_x, des_y);
      player_turn = res.player_turn;
      x_kingb = res.x_kingb;
      y_kingb = res.y_kingb;
      x_kingw = res.x_kingw;
      y_kingw = res.y_kingw;

      if (res.continuee == 1) {
        continue;
      }

      //Other chess piece movements
      int possible = isValidMove(x-1, y-1, des_x-1, des_y-1, board); //movement is possible

      printf(RED);
      switch(possible)
      {
          case 0: printf("This move isn't possible for that chess piece, please check the rules.\n\n"); break;
          case 2: printf("This move isn't possible because one or some coordinates are out of bounds\n\n"); break;
          case 3: printf("This move isn't possible because the chess piece on the destination coordinates is already yours!\n\n"); break;
          case 4: printf("This move isn't possible because there aren't any chess pieces to move!\n\n"); break;
          case 1:
          // Check if there are any chess pieces on destination coordinates and if so remove them from list
          // AND modifies in List coordinates of the chess piece that's moved

          nbWhite = removedpiece(x-1 , y-1, des_x-1, des_y-1, board, currentB, currentW, nbBlack, nbWhite);
          board = pieceMove(x-1 , y-1, des_x-1, des_y-1, board); // Move piece


            //________ King ____________
              if(board[(y-1)*8+(x-1)].color == WHITE && board[(y-1)*8+(x-1)].type == KING) //change position of the king to help check/pat/checkmat
          	    { x_kingw = des_x - 1;
          	      y_kingw = des_y - 1;
          	      white_rock = CANT_ROCK;}

          	  if(board[(y-1)*8+(x-1)].color == BLACK && board[(y-1)*8+(x-1)].type == KING)
          	    { x_kingb = des_x - 1;
          	      y_kingb = des_y - 1;
          	      black_rock = CANT_ROCK;}

              //___________________________

                // Check for checkmates _________________________________________
                struct checking res = check4checkmates( player_turn, board, white_kingstatus, black_kingstatus, x_kingb, y_kingb, x_kingw, y_kingw, des_x, des_y,  player1, robot);
                player_turn = res.player_turn;
                white_kingstatus = res.white_kingstatus;
                black_kingstatus = res.black_kingstatus;
                if (res.returned == 1)
                {
                  free(currentW);
                  free(currentB);
                  return 0;}

    }
  }
    //HERE updating the parameters from robot
    else
    {
      //throwing the functions of the different IA
      if (type==0)
	{


	  struct MCTS_Node *tree = malloc(sizeof(struct MCTS_Node));
	  struct coordonates_moves *coordonates = malloc(sizeof(struct coordonates_moves));

	  tree = create_treem(board, 0, tree);

	  tree = chosen_best(tree);
	  coordonates = coordonates_by_mc(coordonates, tree);

	  x = coordonates->x ;
	  y = coordonates->y ;
	  des_x = coordonates->x_des;
	  des_y = coordonates->y_des;

	  if( x == -1 && y == -1 && des_x == -1 && des_y == -1) //if the 4 coordinates a -1 == ask abandonment
	{
	      printf("\n The AI withdraws\n");
	      printf("\n You won. \n");
	      return 0;
	}
    free(tree);



	}

      if (type==1)
      {

        struct finalmove * move = get_right_move_ia(board,currentW,currentB,WHITETURN, 2,nbWhite, nbBlack);
        x= move->x;
        y=move->y;
        des_y=move->ydes;
        des_x=move->xdes;
        printf("from x=%c y=%i to x=%c and y=%i\n", (char)(x +65), y + 1, (char)(des_x + 65), des_y+1 );
      }
      //for now putting the variables to withdraw to avoid pbms but will be removed later
      //____________________________________ Game settings _____________________________________________________________
      //Rock
      struct res_rock res = rock_sub( player_turn, board, white_kingstatus, black_kingstatus, white_rock, black_rock, x_kingb, y_kingb, x_kingw, y_kingw, x, y, des_x, des_y);
      player_turn = res.player_turn;
      x_kingb = res.x_kingb;
      y_kingb = res.y_kingb;
      x_kingw = res.x_kingw;
      y_kingw = res.y_kingw;

      if (res.continuee == 1) {
        continue;
      }

      nbBlack = removedpiece(x , y, des_x, des_y, board, currentW, currentB, nbWhite, nbBlack);
      board = pieceMove(x, y, des_x, des_y, board); // Move piece

      if(board[(y-1)*8+(x-1)].color == WHITE && board[(y-1)*8+(x-1)].type == KING) //change position of the king to help check/pat/checkmat
        { x_kingw = des_x - 1;
          y_kingw = des_y - 1;
          white_rock = CANT_ROCK;}

      struct checking res2 = check4checkmates( player_turn, board, white_kingstatus, black_kingstatus, x_kingb, y_kingb, x_kingw, y_kingw, des_x, des_y,  player1, robot);
      player_turn = res2.player_turn;
      white_kingstatus = res2.white_kingstatus;
      black_kingstatus = res2.black_kingstatus;
      if (res2.returned == 1)
      {
        free(currentW);
        free(currentB);
            return 0;}
          }
      printf(reset);
      display_board_special(board); //print the board after modifications
      //printf("white \n");
      //printList(currentW,nbWhite);
      //printf("black \n");
      //printList(currentB,nbBlack);

    }
    free(currentW);
    free(currentB);
    return 0;
}

#endif
