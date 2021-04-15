#ifndef VERSION1_C
#define VERSION1_C

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>
#include <unistd.h>
#include <stdio.h>
#include <sqlite3.h>
#include <stdlib.h>
#include "version1.h"



/*
 * @author Anna
 * @date started on 17/03/2021
 * @details all the functions needed for the first version of the game
*/

//________________ Printing the chess board and chess pieces __________________
//Prints chess pieces
void print_special_CHAR(struct Piece current, int color)
{
    if(color == 0)
    { printf("\e[48;5;$124m"); }
    else
    { printf("\e[48;5;$173m"); }

    if(current.color == BLACK)
    {
        switch(current.type)
        {
            case PAWN:
                printf(" ♟ |");
                break;
            case ROOK:
                printf(" ♜ |");
                break;
            case BISHOP:
                printf(" ♝ |");
                break;
            case KNIGHT:
                printf(" ♞ |");
                break;
            case QUEEN:
                printf(" ♛ |");
                break;
            case KING:
                printf(" ♚ |");
                break;
            default: printf("   |");
        }
    }
    else
    {
        switch(current.type)
        {
            case PAWN:
                printf(" ♙ |");
                break;
            case ROOK:
                printf(" ♖ |");
                break;
            case BISHOP:
                printf(" ♗ |");
                break;
            case KNIGHT:
                printf(" ♘ |");
                break;
            case QUEEN:
                printf(" ♕ |");
                break;
            case KING:
                printf(" ♔ |");
                break;
            default: printf("   |");
        }
    }
    printf(reset);
}

//Print board
void display_board_special(struct Piece *board)
{
    printf("    ");
    int as = (int) 'A';
    printf("| %c |", (char)( as));
    for(int y = 1; y < 8; y++)
    {
      printf(" %c |", (char)(y + as));
    }
    printf("\n");
    int color = 0;
    for(int y = 0; y < 8; y++)
    {
        printf("| %d |",y+1);

      for(int x = 0; x < 8; x++)
    {
        // Get printf '\e[48;2;0;0;0m Background color: black\n'
        print_special_CHAR( board[y*8+x], color);
        if(color == 0)
            {color = 1;}
        else
            {color = 0;}
    }
        if(color == 0)
            {color = 1;}
        else
            {color = 0;}
        printf("\n");
    }
}
//____________________________________________________________________________
//________________________ For login _________________________________________

// Verying password, 3 incorrect answers max
void verify_password(struct Player *pl,  int *finished, char *firstTime1)
{
    char * err = malloc(sizeof(char));
    printf("Please enter your password \n");
    scanf(" %s", pl->password);
    system("clear");
    if( rightPassword( pl->email, pl->password) == 1)
    {
        printf(BYEL "Logged in with success \n" reset);
        // Wait for other functions to be created
        //pl->password = password;
        pl->nb_won = getWINS(pl->email);
        pl->nb_lost = getLOST(pl->email);
        *finished = 1;
    }
    else
    {

        printf("Wrong password, is it because you are a new player [Y/N]\n");
        scanf(" %c", err);
        if(*err != (char)'N')
        {   *firstTime1 = 'Y'; }
        else
        {
            int k = 0;
            while(*finished == 0 && k < 2)
            {
                printf(RED "Wrong password, you can try again %i time(s) \n ", 2-k);
                printf(reset);
                printf("Please enter your password \n");
                scanf(" %s", pl->password);
                system("clear");
                if(rightPassword( pl->email, pl->password) != 0)
                {
                    printf(BYEL "Logged in with success \n\n" reset);
                    *finished = 1;
                }
                k++;
            }
            *firstTime1 = 'Y';
            printf(RED "You don't know the password to this account, please create a new one to play \n\n" reset);
        }
    }
    free(err);
}

//Checks if email exists, 3 incorrect answers max
void incorrect_email(struct Player *pl, int *finished, char *firstTime1)
{
    int k = 0;
    while(*finished == 0 && k < 2)
    {
        printf("Wrong email, you can try again %i time(s) \n ", 2-k );
        printf("Please enter your email \n");
        scanf(" %s", pl->email);
        if(email_in_DB( pl->email) != 0)
        {
            verify_password(pl, finished, firstTime1);
        }
        k++;
    }

    if ( *finished == 0) {
      printf(RED "Error: Email doesn't exist, please create an account \n\n" reset);
    }
    *firstTime1 = 'Y';


}

//Checks if account hasn't been created and creates it
void new_account(struct Player *pl, int *finished, char *firstTime1)
{
  printf("Welcome to the Chess ma² family! We're just going to ask a few questions for your profile.\n");
  printf("Enter your name (100 char max): \n");
  scanf(" %s", pl->name);
  printf("Enter your email (100 char max): \n");
  scanf(" %s", pl->email);
  char answer;
  if( email_in_DB( pl->email) != 0 ) {
    printf("This mail is already affiliated to an account, do you wish to log in or create an account with another email?\n Type 'L' for login or 'C' for creating a new account.\n");
    scanf(" %c", &answer);

    while (!(answer == 'L' || answer == 'C')) {
      printf(RED "Type 'L' for login or 'C' for creating a new account.\n" reset);
      scanf(" %c", &answer);
    }

    if (answer == 'C') {
      *firstTime1 = 'Y';
    }
    return;
  }
  printf("Enter your password (64 char max): \n");
  scanf(" %s", pl->password);
  //Clear terminal
  system("clear");
  printf("Your secret password is safe with us %s \n", pl->name);
  newPLAYER( pl->name, pl->password, pl->email, 0, 0);
  printf(BYEL "Account created with success welcome to the family! \n" reset);
  *finished = 1;
  pl->nb_won = 0;
  pl->nb_lost = 0;

}

//Create or get information from login for player1
struct Player *Player1()
{
    struct Player *player1 = malloc(sizeof(struct Player));
    player1->name = malloc(100 * sizeof(char));
    player1->email = malloc(100 * sizeof(char));
    char *err = malloc(sizeof(char));
    char *firstTime1 = malloc(sizeof(char));
    printf("Hi player n°1, is it your first time playing Chess ma²? [Y/N] \n\n");
    scanf(" %c", firstTime1);

    while(!(*firstTime1 == 'Y' || *firstTime1 == 'N'))
    {
        printf("So sorry but you must put either 'Y'(yes) or 'N'(no), is this your first time? \n");
        scanf(" %c", firstTime1);
    }

    int *finished = malloc(sizeof(int));
    *finished = 0;

    while(*finished == 0)
    {
        if(*firstTime1 =='Y')
        {
            new_account( player1, finished, firstTime1);
        }
    else
    {
        printf("Welcome back, please enter your email so we can log you in \n");
        scanf("%s", player1->email);
        if(email_in_DB( player1->email) != 0)
        {
            verify_password(player1, finished, firstTime1);
        }
        else
        {
            printf(RED "Email hasn't been found, is it because you are a new player [Y/N]\n" reset);
            scanf(" %c", err);
            if(*err != (char)'N')
            {
                *firstTime1 = (char) 'Y';
            }
            else
            {
                printf("Ok, let's try again.. \n");
                incorrect_email( player1, finished, firstTime1);
            }
        }
    }
  }

    free(firstTime1);
    free(finished);
    free(err);
    return player1;
}

//Create or get information from login for player2
struct Player *Player2()
{
    struct Player *player2 = malloc(sizeof(struct Player));
    player2->name = malloc(100 * sizeof(char));
    player2->email = malloc(100 * sizeof(char));
    char *err = malloc(sizeof(char));
    char *firstTime1 = malloc(sizeof(char));

    printf("Hi player n°2, is it your first time playing Chess ma²? [Y/N] \n\n");
    scanf(" %c", firstTime1);
    while(!(*firstTime1 == 'Y' || *firstTime1 == 'N'))
    {
        printf("So sorry but you must put either 'Y'(yes) or 'N'(no), is this your first time? \n");
        scanf(" %c", firstTime1);
    }

    int *finished = malloc(sizeof(int));
    *finished = 0;

    while(*finished == 0)
    {
        if(*firstTime1 =='Y')
        {
          new_account( player2, finished, firstTime1);
        }
    else
    {
        printf("Welcome back, please enter your email so we can log you in \n");
        scanf(" %s", player2->email);
        if(email_in_DB( player2->email) != 0)
        {
            verify_password(player2, finished, firstTime1);
        }
        else
        {
            printf(RED "Email hasn't been found, is it because you are a new player [Y/N]\n" reset);
            scanf(" %c", err);
            if(*err != (char)'N')
            {
                *firstTime1 = 'Y';
            }
            else
            {
                printf("Ok, let's try again.. \n");
                incorrect_email( player2, finished, firstTime1);
            }
        }
    }

  }
    free(firstTime1);
    free(finished);
    free(err);
    return player2;
}

//_________________________________________  Game _________________________________________
// Withdraw subfunction
int withdraw(enum turn player_turn, struct Player *pl1, struct Player *pl2)
{
  if( (player_turn == WHITETURN && pl1->team_color == 0 ) || (player_turn == BLACKTURN && pl1->team_color == 1))
    {
        //Player 2 wins
        printf(WHTHB HMAG);
        printNAME(pl1->email);
        printf(" lost by resignation, ");
        printNAME(pl2->email);
        printf(" wins! Congrats to the ");
        if (player_turn == WHITETURN) {
          printf("black team!\n");
        }
        else{
          printf("white team!\n");
        }
        printf(reset);
        update_victory(pl2->email);
        update_loss(pl1->email);
      }
    else
      {
        //Player 1 wins
        printf(WHTHB HMAG);
        printNAME(pl2->email);
        printf(" lost by resignation, ");
        printNAME(pl1->email);
        printf(" wins! Congrats to the ");
        if (player_turn == WHITETURN) {
          printf("black team!\n");
        }
        else{
          printf("white team!\n");
        }
        printf(reset);
        update_victory(pl1->email);
        update_loss(pl2->email);
      }
    return 0;
}

//Stalemate subfunction
struct res_stalemate stalemate(enum turn player_turn, struct Player *player1, struct Player *player2)
{
  struct res_stalemate res;
  res.answer = 2;

  if( player_turn == WHITETURN)
    {
      if(player1->team_color == 0)
        {printNAME(player1->email);}
      else
      {printNAME(player2->email);}
      printf(" (White) is asking for a stalemate. \n");
    }
    else{
      if(player1->team_color == 1)
        {printNAME(player1->email);}
      else
      {printNAME(player2->email);}
      printf(" (Black) is asking for a stalemate. \n");

    }
      int answer;
      printf(" Type " GRN "1" reset" if you accept or else type " RED "0 \n" reset);
      scanf(" %d", &answer);

      // In case answer isn't 1 or 0
      while(!(answer == 1 || answer == 0))
      {
        printf(URED "Please try again...\n" reset);
        printf("Type " GRN "1" reset" if you accept or else type " RED "0 \n" reset);
        scanf(" %d", &answer);
      }

      if( answer == 1) // Accepted = draw
        {
          if(player_turn == WHITETURN)
          {
            printf(BGRN);
            if(player1->team_color == 1)
              printNAME(player1->email);
            else
              printNAME(player2->email);

            printf(" (Black) accepted the stalemate\n" reset);

            printf(BHGRN "\n It's a draw!! \n" reset);
            update_victory(player1->email);
            update_victory(player2->email);
            res.answer = 0;
         }
         else{

           printf(BGRN);
           if(player1->team_color == 0)
             printNAME(player1->email);
           else
             printNAME(player2->email);

           printf( "(White) accepted the stalemate\n" reset);

           printf(BHGRN "\n It's a draw!! \n" reset);
           update_victory(player1->email);
           update_victory(player2->email);
           res.answer = 0;

         }
       }
      else // Not accepted
        {
          printf(BRED);
          if(player_turn == WHITETURN)
          {
            if(player1->team_color == 1)
              printNAME(player1->email);
            else
              printNAME(player2->email);

            printf(" (Black) refuses so the game continues.\n" reset);
            res.player_turn = BLACKTURN;
         }
         else{
             if(player1->team_color == 0)
               printNAME(player1->email);
             else
               printNAME(player2->email);

             printf(" (White) refuses so the game continues.\n" reset);
             res.player_turn = WHITETURN;
         }
       }
      return res;
}

// Checking if coordinates are correct
int incorrect_char(char x)
{
    return x < 'A' || x > 'H'; // 1 if incorrect
}

// Checking if coordinates are correct
int incorrect_int(int x)
{
    return x < 1 || x > 8; // 1 if incorrect
}


//White team wins
void whiteT_Vict(struct Player *pl1, struct Player *pl2)
{
  printf(BGRN);
  if(pl1->team_color == 0)
  {
    printNAME(pl1->email);
    update_victory(pl1->email);
    update_loss(pl2->email);
  }
  else
  {
    printNAME(pl2->email);
    update_victory(pl2->email);
    update_loss(pl1->email);
  }

  printf(" (White) won this game well done! \n" reset);
}


//Black team wins
void blackT_Vict(struct Player *pl1, struct Player *pl2)
{
  printf(BGRN);
  if(pl1->team_color == 1)
  {
    printNAME(pl1->email);
    update_victory(pl1->email);
    update_loss(pl2->email);
  }
  else
  {
    printNAME(pl2->email);
    update_victory(pl2->email);
    update_loss(pl1->email);
  }

  printf(" (Black) won this game well done! \n" reset);
}

// Subfunction if chess piece is Rock
struct res_rock rock_sub(enum turn player_turn, struct Piece *board,
  enum king_status white_kingstatus, enum king_status black_kingstatus,
  enum rock white_rock, enum rock black_rock, int x_kingb, int y_kingb,
  int x_kingw, int y_kingw, int x, int y, int des_x, int des_y)
{
    int continuee = 0;
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
    }
    continuee = 1;
  }
    struct res_rock res = { player_turn, x_kingb, y_kingb, x_kingw, y_kingw, continuee};
    return res;
  }

// Subfunction check for checkmates
struct checking check4checkmates(enum turn player_turn, struct Piece *board,
  enum king_status white_kingstatus, enum king_status black_kingstatus,
  int x_kingb, int y_kingb, int x_kingw, int y_kingw, int des_x, int des_y, struct Player *player1, struct Player *player2)
  {
    int returned = 0;
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
          blackT_Vict(player1, player2);
          returned = 1;
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
          whiteT_Vict(player1, player2);
          returned = 1;
        }
        player_turn = BLACKTURN;
      }

    if((player_turn == WHITETURN && pat(x_kingb, y_kingb, board)) || (player_turn == BLACKTURN && pat(x_kingw, y_kingw, board)))
      {
        printf(BHGRN "\n It's a draw!! \n" reset);
        update_victory(player1->email);
        update_victory(player2->email);
        returned = 1;
      }

  struct checking res = { player_turn, white_kingstatus, black_kingstatus, returned };
  return res;
  }

void print_rules()
{
  printf(RED " _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n");
  printf( "|                  Rules                        |\n");
  printf( "|                                               |\n");
  printf( "| If you wish to Withdraw please type 'W0'      |\n");
  printf( "|              as the original coordinates      |\n");
  printf( "| and then type 'W0' for the new coordinates    |\n");
  printf( "|                                               |\n");
  printf( "|                                               |\n");
  printf( "| If you want to ask for a stalemate please     |\n");
  printf( "|      type 'S0' as the original coordinates    |\n");
  printf( "| and then type 'S0' for the new coordinates    |\n");
  printf( "|                                               |\n");
  printf( "| White team =  ♙  ♖  ♘  ♗  ♔  ♕                |\n");
  printf( "| Black team =  ♟  ♜  ♞  ♝  ♚  ♛                |\n");
  printf( "|_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _|\n");
  printf(reset);
}

// Play game -> reused rules function in rules.c but changed quite a lot
// This is the core function
int play(struct Piece *board, struct Player *player1, struct Player *player2)
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

  int x_kingb = 4;
  int y_kingb = 0;
  int x_kingw = 4;
  int y_kingw = 7;

  enum turn player_turn = WHITETURN; // team's turn
  enum rock white_rock = CAN_ROCK;
  enum rock black_rock = CAN_ROCK;
  enum king_status white_kingstatus = NOTHING;
  enum king_status black_kingstatus = NOTHING;

  //___________________ Random to get which player starts
  int starts = rand() % 2;
  if (starts == 0)
  {
      player1->team_color = 0; // Player 1 is white
      player2->team_color = 1; // Player 2 is black
  }
  else
  {
      player1->team_color = 1; // Player 1 is black
      player2->team_color = 0; // Player 2 is white
  }
  //_______________________________________________________________________________________________________________________________


  while( white_kingstatus != CHECKMATE || black_kingstatus != CHECKMATE ) //continue while not chessmate
    {
      printf("\n\n");
      // Print the name of who's turn it is _________________________________________________________________
      if( (player_turn == WHITETURN && player1->team_color == 0) || (player_turn == BLACKTURN && player1->team_color == 1) )
      { printNAME(player1->email); }
      else{ printNAME(player2->email); }
      if(player_turn == WHITETURN)
      {printf(" (White) ");}
      else
      {printf(" (Black) ");}
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

      //__________________ Withdraw ______________________________________________________________________________________________

      if( x_char == 'W' && y == 0 && des_x_char == 'W' && des_y == 0)
	    {
        return withdraw(player_turn, player1, player2);
	     }

      //__________________ If Stalemate ______________________________________________________________________________________________

      if(x_char == 'S' && y == 0 && des_x_char == 'S' && des_y == 0)
	    {    struct res_stalemate res = stalemate(player_turn, player1, player2);
           if (res.answer == 0) {return 0;}
           else {player_turn = res.player_turn;} }

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
	    { printf(URED "\n That isn't your chess piece to move. \n" reset);
        continue; }

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

              // Check for checkmates _________________________________________
              struct checking res = check4checkmates( player_turn, board, white_kingstatus, black_kingstatus, x_kingb, y_kingb, x_kingw, y_kingw, des_x, des_y,  player1, player2);
              player_turn = res.player_turn;
              white_kingstatus = res.white_kingstatus;
              black_kingstatus = res.black_kingstatus;
              if (res.returned == 1)
              { return 0;}
      }
      printf(reset);
      display_board_special(board); //print the board after modifications

    }
    return 0;
}

#endif
