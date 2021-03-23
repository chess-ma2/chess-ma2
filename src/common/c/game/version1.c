#include "../rules/pieces.h"
#include "../rules/plate.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "ANSI-color-codes.h"
#include "../../../database/create_db.h"
#include <string.h>
#include <err.h>
#include <unistd.h>
#include <stdio.h>
#include <sqlite3.h>
#include <stdlib.h>
#include "../../../database/SHA.h"
#include "../../../database/functions_db.h"

/*
 * @author Anna
 * @date 17/03/2021
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
                printf(" ♚ |");
                break;
            case KING:
                printf(" ♛ |");
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
                printf(" ♔ |");
                break;
            case KING:
                printf(" ♕ |");
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
struct Player {
    char *name;
    unsigned char password[64];
    char *email;
    size_t nb_won;
    size_t nb_lost;
    int team_color;

};
// Verying password, 3 incorrect answers max
void verify_password(struct Player *pl,  int *finished, char *firstTime1)
{
    char * err = malloc(sizeof(char));
    printf("Please enter your password \n");
    scanf("%s", pl->password);
    system("clear");
    if( rightPassword( pl->email, pl->password) != 0)
    {
        const char *forlen = (const char *) pl->password;
        int len = strlen(forlen);
        for(int i = 0; i < len; i++)
        {
            printf("\b");
        }
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
    printf(RED "Error: Email doesn't exist, please create an account \n\n" reset);
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
    printf("This mail is already affiliated to an account, do you wish to log in or create an account with another email?\n Type 'Y' for yes or 'N' for no.\n");
    scanf(" %c", &answer);

    while (!(answer == 'Y' || answer == 'N')) {
      printf(RED "Type 'Y' for yes or 'N' for no.\n" reset);
      scanf(" %c", &answer);
    }
    *firstTime1 = answer;
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

void print_rules()
{
  printf(RED " _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n");
  char *str = malloc(300 * (sizeof(char)));
  printf( "|                  Rules                        |\n");
  printf( "|                                               |\n");
  strcpy(str, "If you wish to Withdraw please type 'W' '-1'");
  printf("|%s   |\n", str);
  strcpy(str, " as the original coordinates ");
  printf("|%s%18s|\n", str, "");
  strcpy(str, "and then type 'W' '-1' for the new coordinates ");
  printf("|%s|\n", str);
  printf( "|                                               |\n");
  printf( "|                                               |\n");
  //is asking for a stalemate
  strcpy(str, "If you want to ask for a stalemate please");
  printf("|%s%6s|\n", str, "");
  strcpy(str, "type 'S' '0' as the original coordinates");
  printf("|%s%7s|\n", str, "");
  strcpy(str, "and then type 'S' '0' for the new coordinates");
  printf("|%s%2s|\n", str, "");
  printf( "|_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _|\n");
  free(str);
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

  int winner; //1 = white win else black

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

      printf("Please enter the original coordinates of the chess piece you want to move (ex: A3) : \n");
      scanf(" %c%d", &x_char, &y);
      /*while(incorrect_char(x_char) || incorrect_int(y))
      {
        printf(URED "Oops... you haven't entered correct coordinates please try again \n" reset);
        printf("Please enter the original coordinates of the chess piece you want to move (ex: A 3 for A3) : \n");
        scanf(" %c %d\n", &x_char, &y);
      }*/
      x = ((int)x_char) - 65;
      printf("Please enter the new coordinates of the chess piece you want to move (ex: B1) : \n");
      scanf(" %c%d", &des_x_char, &des_y);
      /*while(incorrect_char(des_x_char) || incorrect_int(des_y))
      {
        printf(URED "Oops... you haven't entered correct coordinates please try again \n" reset);
        printf("Please enter the new coordinates of the chess piece you want to move (ex: B 1 for B1) : \n");
        scanf(" %c %d\n", &des_x_char, &des_y);
      }*/
      des_x = ((int)des_x_char) - 65;

      //__________________ Withdraw ______________________________________________________________________________________________

      if( x_char == 'W' && y == -1 && des_x_char == 'W' && des_y == -1)
	{
	  if( player_turn == WHITETURN)
	    {
	      winner = 0;
        if(player1->team_color == 0)
        {
          //Player 2 wins (black)
          printf(WHTHB HMAG "\n %s lost by resignation, %s wins! Congrats to the black team!\n" reset, player1->name, player2->name);
          update_victory(player2->email);
          update_loss(player1->email);
        }
        else
        {
          //Player 1 wins (black)
          printf(WHTHB HMAG "\n %s lost by resignation, %s wins! Congrats to the black team!\n" reset, player2->name, player1->name);
          update_victory(player1->email);
          update_loss(player2->email);
        }

	      return 0;
	    }
	  else
	    {
	      winner = 1;
        if(player1->team_color == 0)
        {
          //Player 1 wins (white)
          printf(BLKHB HMAG "\n %s lost by resignation, %s wins! Congrats to the white team!\n" reset, player2->name, player1->name);
          update_victory(player1->email);
          update_loss(player2->email);
        }
        else
        {
          //Player 2 wins (white)
          printf(BLKHB HMAG "\n %s lost by resignation, %s wins! Congrats to the white team!\n" reset, player1->name, player2->name);
          update_victory(player2->email);
          update_loss(player1->email);

        }
	      return 0;
	    }

	}

      //__________________ If null ______________________________________________________________________________________________

      if(x_char == 'S' && y == 0 && des_x_char == 'S' && des_y == 0)
	{
    int answer;
	  if( player_turn == WHITETURN)
	    {
        if(player1->team_color == 0)
          {printf("%s,", player1->name);}
        else
        {printf("%s,", player2->name);}
        printf("White is asking for a stalemate. Type " GRN "1" reset" if you accept or else type " RED "0" reset);
	      scanf("%d", &answer);

        // In case answer isn't 1 or 0
        while(!(answer == 1 || answer == 0))
        {
          printf(URED "Please try again...\n" reset);
          printf("Type " GRN "1" reset" if you accept or else type " RED "0" reset);
  	      scanf("%d", &answer);
        }

        //______________________ Stalemate _____________________________________________________________________________________
	      if( answer == 1) // Accepted = draw
		      {
		          winner = 2;
              printf(BGRN);
              if(player1->team_color == 1)
                {
                  printf("\n%s",player1->name);
                 }
              else
              {printf("\n%s,", player2->name);}
              printf( "(Black) accepted the stalemate\n" reset);
		          printf(BHGRN "\n It's a draw!! \n" reset);
              update_victory(player1->email);
              update_victory(player1->email);
		          return 0;
		       }
	      else // Not accepted
		      {
            printf(BRED);
            if(player1->team_color == 1)
              {
                printf("\n%s",player1->name);
               }
            else
            {printf("\n%s,", player2->name);}
		        printf("\n(Black) refuses so the game continues.\n" reset);
		       }

	      player_turn = BLACKTURN;

	    }
	  else
	    {
        if(player1->team_color == 1) // If black
          {printf("%s,", player1->name);}
        else
        {printf("%s,", player2->name);}
        printf("Black is asking for a stalemate. Type " GRN "1" reset" if you accept or else type " RED "0" reset);
	      scanf("%d", &answer);

        // In case answer isn't 1 or 0
        while(!(answer == 1 || answer == 0))
        {
          printf(URED "Please try again...\n" reset);
          printf("Type " GRN "1" reset" if you accept or else type " RED "0" reset);
  	      scanf("%d", &answer);
        }

	      if( answer == 1) // If white accepts
		    {
		        winner = 2;
            printf(BGRN);
            if(player1->team_color == 0)
              {
                printf("\n%s",player1->name);
               }
            else
            {printf("\n%s,", player2->name);}
            printf( "(White) accepted the stalemate\n" reset);
            printf(BHGRN "\n It's a draw!! \n" reset);
            update_victory(player1->email);
            update_victory(player1->email);
		        return 0;
		}
	      else// Not accepted
		      {
            printf(BRED);
            if(player1->team_color == 0)
              {
                printf("\n%s",player1->name);
               }
            else
            {printf("\n%s,", player2->name);}
		        printf("\n(White) refuses so the game continues.\n" reset);
		        }
	      player_turn = WHITETURN;
	    }
	}

      //--------------------------------------------------------------------------------------
      // Make sure the coordonates are correct
      while(incorrect_char(x_char) || incorrect_int(y))
      {
        printf(URED "Oops... you haven't entered correct coordinates please try again \n" reset);
        printf("Please enter the original coordinates of the chess piece you want to move (ex: A3) : \n");
        scanf(" %c%d\n", &x_char, &y);
      }
      x = ((int)x_char) - 65;

      // It's not your piece to move
      if((player_turn == WHITETURN && board[(y-1)*8+(x+1)].color == BLACK && board[(y-1)*8+(x+1)].type != NONE) ||
            (player_turn == BLACKTURN && board[(y-1)*8+(x+1)].color == WHITE && board[(y-1)*8+(x+1)].type != NONE))
	    {
	       printf(URED "\n That isn't your chess piece to move. \n" reset);
         continue;
         /*while(incorrect_char(x_char) || incorrect_int(y))
         {
           printf("Please enter the original coordinates of" URED "your" reset "chess piece you want to move (ex: A 3 for A3) : \n");
           scanf(" %c %d\n", &x_char, &y);
         }*/
	     }

      //____________________________________ Game settings _____________________________________________________________
      //Rock
      if( white_rock == CAN_ROCK && board[(y-1)*8+(x+1)].color == WHITE && board[(y-1)*8+(x+1)].type == KING)
	    {
	        int possible_rock = isValidMove_Rock( x - 1, y-1, des_x-1, des_y-1, board[(y-1)*8+(x+1)].color, board);
	        white_rock = CANT_ROCK;

	         if (possible_rock == 1)
	         {
	            board = pieceMove_Rock(x-1, y-1, des_x-1, des_y-1, board);
	            if(player_turn == WHITETURN)
		            { player_turn = BLACKTURN;}
	            else
		            { player_turn = WHITETURN;}
           }
	      }
      else if( black_rock == CAN_ROCK && board[(y-1)*8+(x+1)].color == BLACK && board[(y-1)*8+(x+1)].type == KING)
	    {
	       int possible_rock = isValidMove_Rock( x - 1, y-1, des_x -1, des_y -1, board[(y-1)*8+(x+1)].color, board);
	       black_rock = CANT_ROCK;

	       if (possible_rock == 1)
	       {
	          board = pieceMove_Rock(x-1, y-1, des_x-1, des_y-1, board);
            if(player_turn == WHITETURN)//change the players turn
		        { player_turn = BLACKTURN; }
	           else
		        { player_turn = WHITETURN; }
          }
	     }
      //Other chess piece movements
      //int possible = isValidMove(x-1, y-1, des_x-1, des_y-1, board); //movement is possible
      int possible = isValidMove(x, y-1, des_x, des_y-1, board); //movement is possible

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
              //board = pieceMove(x-1, y-1, des_x-1, des_y-1, board);
              board = pieceMove(x, y-1, des_x, des_y-1, board);
              if(player_turn == WHITETURN) //change the player turn
          	  { player_turn = BLACKTURN; }
          	  else
          	  { player_turn = WHITETURN; }

      }
      printf(reset);
      display_board_special(board); //print the board after modifications

    }
    return 0;
}
