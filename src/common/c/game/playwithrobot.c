#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../../client/c/network/game.c"
#include "../data/process_board.c"
#include "../rules/rules.c"
#include "../rules/pieces.c"
#include "version1.c"
#include "../rules/check_and_pat.c"
#include "added_functions.c"


//using nearly anna and marie 's function but a little adaptation
int playwrobot(struct Piece *board, struct Player *player1, struct Player *robot,int type)
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

  //kings'positions to know if check or checkmat

  int x_kingw = 4;
  int y_kingw = 0;
  int x_kingb = 4;
  int y_kingb = 7;

  enum turn player_turn = WHITETURN; // team's turn
  enum rock white_rock = CAN_ROCK;
  enum rock black_rock = CAN_ROCK;
  enum king_status white_kingstatus = NOTHING;
  enum king_status black_kingstatus = NOTHING;

  //___________________ Random to get which player starts
  int starts = rand() % 2;
  if (starts == 0)
  {
      player1->team_color = 0; // Player is white
      robot->team_color = 1; // robot is black
  }
  else
  {
      player1->team_color = 1; // Player is black
      robot->team_color = 0; // robot is white
  }
  //_______________________________________________________________________________________________________________________________


  while( white_kingstatus != CHECKMATE || black_kingstatus != CHECKMATE ) //continue while not chessmate
    {
      printf("\n\n");

      //HERE entering the parameters for local game
      // Print the name of who's turn it is _________________________________________________________________
      if( player1->team_color == player_turn)
      {
        printNAME(player1->email);
        if(player_turn == WHITETURN)
        {
          printf(" (White) ");
        }
        else
        {
          printf(" (Black) ");
        }
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

    }
    //HERE updating the parameters from robot
    else
    {
      //throwing the functions of the different IA
      if (type==0)
      {
        //throw IA marie and antoine
      }
      if (type==1)
      {
        //struct Move * move= malloc(sizeof(int)*4);
        //throw IA anna and marine with move in parameters
        //move = throwrobot(board, move);
        //x_char= move->xbeg;
        //y=move->ybeg;
        //x = ((int)x_char) - 64;
        //des_x_char=move->xdes;
        //des_y=move->ydes;
        //des_x=((int)des_x_char) - 64;
      }
      //for now putting the variables to withdraw to avoid pbms but will be removed later
      x_char = 'W';
      y = 0;
      des_x_char = 'W';
      des_y = 0;
    }

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
      if((player_turn == WHITETURN && board[(y-1)*8+(x+1)].color == BLACK && board[(y-1)*8+(x+1)].type != NONE) ||
            (player_turn == BLACKTURN && board[(y-1)*8+(x+1)].color == WHITE && board[(y-1)*8+(x+1)].type != NONE))
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

          if (player_turn == WHITETURN) {
            nbWhite = removedpiece(x-1 , y-1, des_x-1, des_y-1, board, currentW, nbWhite); }
          else { nbBlack = removedpiece(x-1 , y-1, des_x-1, des_y-1, board, currentB, nbBlack); }

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


              // Impossible move
          	  if((player_turn == BLACKTURN && piece_to_place(x_kingb, y_kingb, board) == 1 ) || (player_turn == WHITETURN && piece_to_place(x_kingw, y_kingw, board) == 1))
          	    {  board = pieceMove(des_x-1, des_y-1, x-1, y-1, board);
          	       printf("Impossible to move the king as checkmate would be unavoidable\n");

          	      if(board[(y-1)*8+(x-1)].color == BLACK && board[(y-1)*8+(x-1)].type == KING) //change position of the king to help check/pat/checkmat
          		    {   x_kingb = x - 1;
          		        y_kingb = y - 1; }

                 if(board[(y-1)*8+(x-1)].color == WHITE && board[(y-1)*8+(x-1)].type == KING) //change position of the king to help check/pat/checkmat
                 {    x_kingw = x - 1;
                      y_kingw = y - 1; }
          	      continue;
          	    }

                // Check for checkmates _________________________________________
                struct checking res = check4checkmates( player_turn, board, white_kingstatus, black_kingstatus, x_kingb, y_kingb, x_kingw, y_kingw, des_x, des_y,  player1, player2);
                player_turn = res.player_turn;
                white_kingstatus = res.white_kingstatus;
                black_kingstatus = res.black_kingstatus;
                if (res.returned == 1)
                {
                  free(currentW);
                  free(currentB);
                  return 0;}
      }
      printf(reset);
      display_board_special(board); //print the board after modifications

    }
    free(currentW);
    free(currentB);
    return 0;
}
