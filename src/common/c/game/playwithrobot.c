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
      //x = ((int)x_char) - 65;
      x = ((int)x_char) - 64;

      //Get new coordinates
      printf("Please enter the new coordinates of the chess piece you want to move (ex: B1) : \n");
      scanf(" %c%d", &des_x_char, &des_y);
      //des_x = ((int)des_x_char) - 65;
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
      //x = ((int)x_char) - 65;
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
      if( (player_turn == WHITETURN && white_kingstatus == NOTHING && white_rock == CAN_ROCK && board[(y-1)*8+(x-1)].color == WHITE && board[(y-1)*8+(x-1)].type == KING) ||
      (player_turn == BLACKTURN && black_kingstatus == NOTHING && black_rock == CAN_ROCK && board[(y-1)*8+(x-1)].color == BLACK && board[(y-1)*8+(x-1)].type == KING))
      {

        if (isValidMove_Rock( x - 1, y-1, des_x-1, des_y-1, board[(y-1)*8+(x-1)].color, board) == 1)
        {   board = pieceMove_Rock(x-1, y-1, des_x-1, des_y-1, board);

            if (player_turn == WHITETURN) {
              x_kingw = des_x - 1;
              y_kingw = des_y - 1;
            }
            else
            {
              x_kingb = des_x - 1;
              y_kingb = des_y - 1;
            }


            if(piece_to_place(x_kingw, y_kingw, board) == 1 || piece_to_place(x_kingb, y_kingb, board) == 1)
           {
            board = pieceMove(des_x-1, des_y-1, x-1, y-1, board);
            printf("Impossible move for chessmate is inevitable\n");

            if (player_turn == WHITETURN) {
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
            player_turn = BLACKTURN;
          }
            else
            {
              x_kingb = x - 1;
              y_kingb = y - 1;

              if( x - 1 == 4 && y - 1 == 0)
              { if(des_x - 1 == 6 && des_y - 1 == 0) //litte rock
                {
                  board[0*8+7].type = ROOK;
                  board[0*8+7].color = BLACK;
                  board[0*8+5].type = NONE;
                  board[0*8+5].color = 0; }

                if (des_x - 1 == 2 && des_y - 1 == 0) //big rock
                {
                  board[0*8+0].type = ROOK;
                  board[0*8+0].color = BLACK;
                  board[0*8+3].type = NONE;
                  board[0*8+3].color = 0; }
            }
            player_turn = WHITETURN;
          }
        }
      //display_board_special(board);
      continue;
    }
  }
      //Other chess piece movements
      int possible = isValidMove(x-1, y-1, des_x-1, des_y-1, board); //movement is possible
      //int possible = isValidMove(x, y-1, des_x, des_y-1, board); //movement is possible

      //printf("%d", possible);
      printf(RED);
      switch(possible)
      {
          case 0:
              printf("This move isn't possible for that chess piece, please check the rules.\n\n");
              break;
          case 2:
              printf("This move isn't possible because one or some coordinates are out of bounds\n\n");
              break;
          case 3:
              printf("This move isn't possible because the chess piece on the destination coordinates is already yours!\n\n");
              break;
          case 4:
              printf("This move isn't possible because there aren't any chess pieces to move!\n\n");
              break;
          case 1:

              //Move chess piece
              board = pieceMove(x-1 , y-1, des_x-1, des_y-1, board);

            //________ King ____________
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

              //___________________________


              // Impossible move
          	  if((player_turn == BLACKTURN && piece_to_place(x_kingb, y_kingb, board) == 1 ) || (player_turn == WHITETURN && piece_to_place(x_kingw, y_kingw, board) == 1))
          	    {
                  board = pieceMove(des_x-1, des_y-1, x-1, y-1, board);
          	      printf("Impossible to move the king as checkmate would be unavoidable\n");

          	      if(board[(y-1)*8+(x-1)].color == BLACK && board[(y-1)*8+(x-1)].type == KING) //change position of the king to help check/pat/checkmat
          		    {   x_kingb = x - 1;
          		        y_kingb = y - 1; }

                 if(board[(y-1)*8+(x-1)].color == WHITE && board[(y-1)*8+(x-1)].type == KING) //change position of the king to help check/pat/checkmat
                 {    x_kingw = x - 1;
                      y_kingw = y - 1; }
          	      continue;
          	    }

              //___________________________ Black team's turn
          	  if(player_turn == BLACKTURN)
          	    {
                  if (kingcheck_place(x_kingw, y_kingw, des_x-1, des_y-1, board) == 1) {
                    white_kingstatus = CHECK;
            	      printf("Checkmate for the white king \n");
                  }

                  if (kingcheck_place(x_kingb, y_kingb, des_x-1, des_y-1, board) == 0)
                    black_kingstatus = NOTHING;

                  if (check_mat(x_kingw, y_kingw, WHITE,  board)== 1) {
                    return blackT_Vict(player1, robot);
                  }
                  player_turn = WHITETURN;
                }
                else//___________________________ White team's turn
          	    {
                  if (kingcheck_place( x_kingb, y_kingb, des_x-1, des_y-1, board) == 1) {
                    black_kingstatus = CHECK;
            	      printf("Checkmate for the black king \n");
                  }

                  if (kingcheck_place( x_kingw, y_kingw, des_x-1, des_y-1, board) == 0)
                    white_kingstatus = NOTHING;

                  if (check_mat(x_kingb, y_kingb, BLACK, board)== 1) {
                    return whiteT_Vict(player1, robot);
                  }
                  player_turn = BLACKTURN;
          	    }

          	  if((player_turn == WHITETURN && pat(x_kingb, y_kingb, board)) || (player_turn == BLACKTURN && pat(x_kingw, y_kingw, board)))
          	    {
                  printf(BHGRN "\n It's a draw!! \n" reset);
                  update_victory(player1->email);
                  update_victory(robot->email);
          	      return 0;
          	    }
      }
      printf(reset);
      display_board_special(board); //print the board after modifications

    }

    return 0;
}
