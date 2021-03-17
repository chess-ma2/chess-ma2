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
        printf("\e[48;5;$124m%03d");
    }
    else
    {
        printf("\e[48;5;$173m%03d");
    }

    if(current.color == BLACK)
    {
        switch(current.type)
        {
            case PAWN: printf("| ♟ |");
            case ROOK: printf("| ♜ |");
            case BISHOP: printf("| ♝ |");
            case KNIGHT: printf("| ♞ |");
            case QUEEN: printf("| ♚ |");
            case KING: printf("| ♛ |");
            default: printf("|   |");
        }
    }
    else
    {
        switch(current.type)
        {
            case PAWN: printf("| ♙ |");
            case ROOK: printf("| ♖ |");
            case BISHOP: printf("| ♗ |");
            case KNIGHT: printf("| ♘ |");
            case QUEEN: printf("| ♔ |");
            case KING: printf("| ♕ |");
            default: printf("|   |");
        }
    }
    printf(reset);
}

void display_board_special(struct Piece *board)
{
    printf("   ");
    int as = (int) 'A';
    for(int y = 0; y < 8; y++)
    {
      printf("|%4c|", (char)y + as);
    }
    printf("\n");
    int color = 0;
    for(int y = 0; y < 8; y++)
    {
        printf("|%4d|",y+1);

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
        scanf("%c", err);
        if(*err != (char)'N')
        {   *firstTime1 = 'Y'; }
        else
        {
            int k = 0;
            while(*finished == 0 && k < 2)
            {
                printf("Wrong password, you can try again %i time(s) \n ", 2-k );
                printf("Please enter your password \n");
                scanf("%s", pl->password);
                if(rightPassword( pl->email, pl->password) != 0)
                {
                    const char *forlen = (const char *)pl->password;
                    int len = strlen(forlen);
                    for(int i = 0; i < len; i++)
                    { printf("\b"); }
                    printf(BYEL "Logged in with success \n" reset);
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
            printf("You don't know the password to this account, please create a new one to play \n");
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
        scanf("%s", pl->email);
        if(email_in_DB( pl->email) != 0)
        {
            unsigned char password[64];
            verify_password(pl, password, finished, firstTime1);
        }
        k++;
    }
    printf("Error: Email doesn't exist, please create an account \n");
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
    printf("Hi player n°1, is it your first time playing Chess ma²? [Y/N] \n");
    scanf("%c", firstTime1);
    while(!(*firstTime1 == 'Y' || *firstTime1 == 'N'))
    {
        printf("So sorry but you must put either 'Y'(yes) or 'N'(no), is this your first time? \n");
        scanf("%c", firstTime1);
    }

    int *finished = malloc(sizeof(int));
    *finished = 0;

    while(*finished == 0)
    {
        if(*firstTime1 =='Y')
        {
            printf("Welcome to the Chess ma² family! We're just going to ask a few questions for your profile.\n");
            printf("Enter your name (100 char max): \n");
            scanf("%s", player1->name);
            printf("Enter your email (100 char max): \n");
            scanf("%s", player1->email);
            printf("Enter your password (64 char max): \n");
            scanf("%s", player1->password);

            const char *forlen =  (const char *) player1->password;
            int len = strlen(forlen);
            for(int i = 0; i < len; i++)
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
            printf("Email hasn't been found, is it because you are a new player [Y/N]\n");
            scanf("%c", err);
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

    printf("Hi player n°2, is it your first time playing Chess ma²? [Y/N] \n");
    scanf("%c", firstTime1);
    while(!(*firstTime1 == 'Y' || *firstTime1 == 'N'))
    {
        printf("So sorry but you must put either 'Y'(yes) or 'N'(no), is this your first time? \n");
        scanf("%c", firstTime1);
    }

    int *finished = malloc(sizeof(int));
    *finished = 0;

    while(*finished == 0)
    {
        if(*firstTime1 =='Y')
        {
            printf("Welcome to the Chess ma² family! We're just going to ask a few questions for your profile.\n");
            printf("Enter your name (100 char max): \n");
            scanf("%s", player2->name);
            printf("Enter your email (100 char max): \n");
            scanf("%s", player2->email);
            printf("Enter your password (64 char max): \n");
            scanf("%s", player2->password);

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
        scanf("%s", player2->email);
        if(email_in_DB( player2->email) != 0)
        {
            verify_password(player2, player2->password, finished, firstTime1);
        }
        else
        {
            printf("Email hasn't been found, is it because you are a new player [Y/N]\n");
            scanf("%c", err);
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

int main()
{
    //_________________ Welcome message ________________________________

    printf("___________________________________________________\n");
    printf("   Welcome to Chess ma² \n This is the first version of the project. \nIn this version, you can play with a friend(or your sworn chess enemy) on a same computer. You must both have an account to play.\n");

    //_________________ Connecting to database _________________________
    creatingTables();

    //______ Get or create players
    struct Player *player1 = Player1();
    struct Player *player2 = Player2();

    //___________________   Start Game   ________________________________
    int res; //ask coordonates
    int null; //if ask null
    int answer = 0;

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
    display_board_special(board);

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
