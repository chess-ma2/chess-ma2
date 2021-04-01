#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>
#include <unistd.h>
#include <stdio.h>
#include <../game/game1.c>
#include <../game/version1.c>

int main():
{
    printf("Welcome to CHESS(MA)² !\n Are you ready to have a successful game?\n");
    printf("Remember, with CHESS(MA)², every checkmate brings mates closer ! \n");
    
    printf("Now, I am going to ask you, do you want to play with a player online or do you want to play on your computr with a friend ?\n");
    printf("To play on one computer with a friend, click on the 'enter' button of your keyboard\n");
    printf("To play only with a member of chess(ma)² tap '4' then 'enter' on your keyboard");
    printf("HAVE A GREAT GAME");
    
    //if empty then game local game, if 42 then online game
    char *type = malloc(sizeof(char));
    scanf(" %c", type);
    if (type=='4')
    {
        //todo launching the online game
    }
    else
    {
        localgame();
    }
    free(type);
    
    return 0;
}

//using anna's function to launch the local game
void localgame()
{
    //_________________ Welcome message ________________________________

    printf("__________________________________________________________________________________________________\n\n");
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

