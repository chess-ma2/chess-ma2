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

/*
 * {"♜ ♞ ♝ ♛ ♚ ♝ ♞ ♜"},
    {"♟ ♟ ♟ ♟ ♟ ♟ ♟ ♟"},
    {"… … … … … … … …"},
    {"… … … … … … … …"},
    {"… … … … … … … …"},
    {"… … … … … … … …"},
    {"♙ ♙ ♙ ♙ ♙ ♙ ♙ ♙"},
    {"♖ ♘ ♗ ♕ ♔ ♗ ♘ ♖"}
 *
 */

void print_special_CHAR(struct Piece current, int color)
{
    if(color == 0)
    {
        //printf("\e[48;5;$124m%03d");
        printf("\e[48;5;$124m");
    }
    else
    {
        printf("\e[48;5;$173m");
    }

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

struct Player {
    char *name;
    unsigned char password[64];
    char *email;
    size_t nb_won;
    size_t nb_lost;

};

void verify_password(struct Player *pl, unsigned char password[64],  int *finished, char *firstTime1)
{
    char * err = malloc(sizeof(char));
    printf("Please enter your password \n");
    scanf("%s", pl->password);
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
        pl->name = "Player 1";
        //pl->password = password;
        pl->nb_won = 0;
        pl->nb_lost = 0;
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
                if(rightPassword( pl->email, pl->password) != 0)
                {
                    const char *forlen = (const char *)pl->password;
                    int len = strlen(forlen);
                    for(int i = 0; i < len; i++)
                    { printf("\b"); }
                    printf(BYEL "Logged in with success \n\n" reset);
                    // Wait for other functions to be created
                    pl->name = "Player 1";
                    //pl->password = password;
                    pl->nb_won = 0;
                    pl->nb_lost = 0;
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
            unsigned char password[64];
            verify_password(pl, password, finished, firstTime1);
        }
        k++;
    }
    printf(RED "Error: Email doesn't exist, please create an account \n\n" reset);
    *firstTime1 = 'Y';


}

struct Player *Player1()
{
    struct Player *player1 = malloc(sizeof(struct Player));
    player1->name = malloc(100 * sizeof(char));
    unsigned char password[64];
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
            printf("Welcome to the Chess ma² family! We're just going to ask a few questions for your profile.\n");
            printf("Enter your name (100 char max): \n");
            scanf(" %s", player1->name);
            printf("Enter your email (100 char max): \n");
            scanf(" %s", player1->email);
            printf("Enter your password (64 char max): \n");
            scanf(" %s", player1->password);

            const char *forlen =  (const char *) player1->password;
            int len = strlen(forlen);
            for(int i = 0; i < 20; i++)
            {
                printf("\b");
            }
            printf("Your secret password is safe with us %s \n", player1->name);
            newPLAYER( player1->name, player1->password, player1->email, 0, 0);
            printf(BYEL "Account created with success welcome to the family! \n" reset);
            *finished = 1;
            //player1->password = password;
            player1->nb_won = 0;
            player1->nb_lost = 0;
    }
    else
    {
        printf("Welcome back, please enter your email so we can log you in \n");
        scanf("%s", player1->email);
        if(email_in_DB( player1->email) != 0)
        {
            verify_password(player1, password, finished, firstTime1);
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

struct Player *Player2()
{
    struct Player *player2 = malloc(sizeof(struct Player));
    player2->name = malloc(100 * sizeof(char));
    unsigned char password[64];
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
            printf("Welcome to the Chess ma² family! We're just going to ask a few questions for your profile.\n");
            printf("Enter your name (100 char max): \n");
            scanf(" %s", player2->name);
            printf("Enter your email (100 char max): \n");
            scanf(" %s", player2->email);
            printf("Enter your password (64 char max): \n");
            scanf(" %s", player2->password);

            const char * forlen = (const char *) player2->password;
            int len = strlen(forlen);
            for(int i = 0; i < len; i++)
            {
                printf("\b");
            }
            printf("Your secret password is safe with us %s \n", player2->name);
            newPLAYER( player2->name, player2->password, player2->email, 0, 0);
            printf(BYEL "Account created with success welcome to the family! \n" reset);
            *finished = 1;
            //player1->password = password;
            player2->nb_won = 0;
            player2->nb_lost = 0;
    }
    else
    {
        printf("Welcome back, please enter your email so we can log you in \n");
        scanf(" %s", player2->email);
        if(email_in_DB( player2->email) != 0)
        {
            verify_password(player2, player2->password, finished, firstTime1);
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

void play(struct Piece *board)
{
  int res; //ask positions

  int null; //if ask nulle

  int answer = 0; // answer oth the nulle proposition

  int x = 0;
  char x_char = A;
  int y = 0;
  int des_x = 0;
  char des_x_char = A;
  int des_y = 0;

  int winner; //1 = white win else black

  enum turn player_turn = WHITETURN; // team's turn

  enum rock white_rock = CAN_ROCK;
  enum rock black_rock = CAN_ROCK;

  enum king_status white_kingstatus = NOTHING;
  enum king_status black_kingstatus = NOTHING;

  while( white_kingstatus != CHECKMATE || black_kingstatus != CHECKMATE ) //continue while not chessmate
    {
      printf("\n\n");

      printf("Please enter the original coordonates of the chess piece you want to move () : \n");
      char x_char;
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
}

int main()
{

    //_________________ Welcome message ________________________________

    printf("__________________________________________________________________________________________________\n\n");
    printf(BRED "                                 Welcome to Chess ma² \n\n" reset);
    printf("This is the first version of the project. \n");
    printf("In this version, you can play with a friend (or your sworn chess enemy) on a same computer.\n");
    printf(URED "You must both have (or create) an account to play.\n\n" reset);

    printf("__________________________________________________________________________________________________\n\n");
    //_________________ Connecting to database _________________________
    creatingTables();

    //______ Get or create players
    struct Player *player1 = Player1();
    printf("\n \n");

    struct Player *player2 = Player2();

    //___________________   Start Game   ________________________________
    struct Piece *board = init_board();
    display_board_special(board);
    play(board);

    //___________________   Free memory_   ________________________________

    free(player1->name);
    free(player1->email);
    free(player1);
    free(player2->name);
    free(player2->email);
    free(player2);
    free(board);

    return 0;
}
