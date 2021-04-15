#ifndef VERSION1_H
#define VERSION1_H

/*
 * @author Anna
 * @date 20/03/2021 (finally spring)
 * @details all the functions needed for the first version of the game
*/

// Include Section
#include "../rules/pieces.c"
#include "../rules/plate.c"
#include "../rules/check_and_pat.c"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "ANSI-color-codes.h"
#include "../../../database/create_db.c"
#include <string.h>
#include <err.h>
#include <unistd.h>
#include <stdio.h>
#include <sqlite3.h>
#include <stdlib.h>
#include "../../../database/SHA.c"
#include "../../../database/functions_db.c"


// PLAYER STRUCTURE
struct Player {
    char *name;
    unsigned char password[64];
    char *email;
    size_t nb_won;
    size_t nb_lost;
    int team_color;

};

// Stalemate answer structure
struct res_stalemate{
    int answer;
    enum turn player_turn;
};

// Structure needed for Rock subfunction
struct res_rock{
  enum turn player_turn;
  int x_kingb;
  int y_kingb;
  int x_kingw;
  int y_kingw;
  int continuee;
};

// Structure needed for Check for checkmate subfunction
struct checking{
  enum turn player_turn;
  enum king_status white_kingstatus;
  enum king_status black_kingstatus;
  int returned;
};

//________________ Printing the chess board and chess pieces __________________
//Prints chess pieces
void print_special_CHAR(struct Piece current, int color);
//Print board
void display_board_special(struct Piece *board);

//________________________ For login __________________________________________
// Verying password, 3 incorrect answers max
void verify_password(struct Player *pl,  int *finished, char *firstTime1);

//Checks if email exists, 3 incorrect answers max
void incorrect_email(struct Player *pl, int *finished, char *firstTime1);

//Create or get information from login for player1
struct Player *Player1();

//Create or get information from login for player2
struct Player *Player2();

//Checks if account hasn't been created and creates it
void new_account(struct Player *pl, int *finished, char *firstTime1);

//________________________ Game _______________________________________________
//Stalemate subfunction
struct res_stalemate stalemate(enum turn player_turn, struct Player *player1, struct Player *player2);

// Withdraw subfunction
int withdraw(enum turn player_turn, struct Player *pl1, struct Player *pl2);

// Subfunction if chess piece is Rock
struct res_rock rock_sub(enum turn player_turn, struct Piece *board,
  enum king_status white_kingstatus, enum king_status black_kingstatus,
  enum rock white_rock, enum rock black_rock, int x_kingb, int y_kingb,
  int x_kingw, int y_kingw, int x, int y, int des_x, int des_y);

// Subfunction check for checkmates
struct checking check4checkmates(enum turn player_turn, struct Piece *board,
  enum king_status white_kingstatus, enum king_status black_kingstatus,
  int x_kingb, int y_kingb, int x_kingw, int y_kingw, int des_x, int des_y, struct Player *pl1, struct Player *pl2);


// Checking if coordinates are correct
int incorrect_char(char x);

// Checking if coordinates are correct
int incorrect_int(int x);

//White team wins
void whiteT_Vict(struct Player *pl1, struct Player *pl2);

//Black team wins
void blackT_Vict(struct Player *pl1, struct Player *pl2);

// Play game -> reused rules function in rules.c but changed quite a lot
// Print rules
void print_rules();

// This is the core function
int play(struct Piece *board, struct Player *player1, struct Player *player2);


#endif
