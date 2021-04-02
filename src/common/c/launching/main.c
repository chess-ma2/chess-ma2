//marine 31/03


#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>
#include <unistd.h>
#include <stdio.h>
#include "../game/game1.c"
#include "../game/version1.c"
#include "../../client/c/network/compatibility.c"

int main():
{
    printf("Welcome to CHESS(MA)² !\n Are you ready to have a successful game?\n");
    printf("Remember, with CHESS(MA)², every checkmate brings mates closer ! \n");
    
    printf("Now, I am going to ask you, do you want to play with a player online or do you want to play on your computr with a friend ?\n");
    printf("To play on one computer with a friend, click on the 'enter' button of your keyboard\n");
    printf("To play only with a member of chess(ma)² tap '4' then 'enter' on your keyboard\n");
    printf("HAVE A GREAT GAME\n");
    
    //if empty then game local game, if 42 then online game
    char *type = malloc(sizeof(char));
    scanf(" %c", type);
    if (type=='4')
    {
        onlinegame();
    }
    else
    {
        localgame();
    }
    
    free(type);
    
    return 0;
}

//Create or get information from login for player
//ANNA's function a bit modified
//only adapted to the online game
struct Player *Player()
{
    struct Player *player = malloc(sizeof(struct Player));
    player->name = malloc(100 * sizeof(char));
    player->email = malloc(100 * sizeof(char));
    char *err = malloc(sizeof(char));
    char *firstTime = malloc(sizeof(char));
    printf("Hi player, is it your first time playing Chess ma²? [Y/N] \n\n");
    scanf(" %c", firstTime);

    while(!(*firstTime == 'Y' || *firstTime == 'N'))
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
            new_account( player, finished, firstTime);
        }
    else
    {
        printf("Welcome back, please enter your email so we can log you in \n");
        scanf("%s", player->email);
        if(email_in_DB( player->email) != 0)
        {
            verify_password(player, finished, firstTime);
        }
        else
        {
            printf(RED "Email hasn't been found, is it because you are a new player [Y/N]\n" reset);
            scanf(" %c", err);
            if(*err != (char)'N')
            {
                *firstTime = (char) 'Y';
            }
            else
            {
                printf("Ok, let's try again.. \n");
                incorrect_email( player, finished, firstTime);
            }
        }
    }}

    free(firstTime);
    free(finished);
    free(err);
    return player;
}

void onlinegame()
{
    printf("__________________________________________________________________________________________________\n\n");
    printf("In this version, you can play with a friend (or your sworn chess enemy) on a different.\n");
    printf("You are going to be connected with someone a person who currently wants to join an online game\n ");
    printf("be patient, it can take a while\n");
    //ici mettre un truc de fonction timer qui affiche les fonctions restantes
    
    struct Player * playerid =Player();
    //ici appeler les fonctions necessaires pour lancer la base de données
    //voir avec antoine
    //essaie
    //checking compatibility, to be continued....
    int comp= check_compatibility();
    switch (comp)
    {
        case 9:
            break;
        case 10:
            break;
        case 0:
            break;
        
        default:
            errx("THE VERSION OF THE SERVEUR AND THE CLIENT ARE NOTE COMPATIBLE")
            
    }
    //connexion to be done
    
    
    //end
    free(playerid);
    
}

//using anna's function to launch the local game
void localgame()
{
    //_________________ Welcome message ________________________________

    printf("__________________________________________________________________________________________________\n\n");
    printf("In this version, you can play with a friend (or your sworn chess enemy) on the same computer.\n");
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
    int res = play(board, player1, player2);

    //___________________   Free memory_   ________________________________

    free(player1->name);
    free(player1->email);
    free(player1);
    free(player2->name);
    free(player2->email);
    free(player2);
    free(board);

    return res;
}

