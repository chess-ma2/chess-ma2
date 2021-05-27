#include <stdio.h>
#include <gtk/gtk.h>
#include <string.h>
#ifndef LOCAL1_H
#define LOCAL1_H

/*
 * @author Anna
 * @date 10/04/2021
 * @details all the functions needed for the first version of the game on gtk
*/
// Include Section
#include "../database/create_db.c"
#include "../database/functions_db.c"
#include "../common/c/game/version1.c"
#include "../common/c/game/added_functions.c"
#include "../common/c/rules/check_and_pat.c"
#include "../common/c/rules/pieces.c"
#include "../common/c/rules/plate.c"
#include "added_functions4local.c"
#include "Local1_init.c"

// Game _________________________________________________________

// When move is chosen
void click4move(GtkButton *button, gpointer user_data);

// Subfunction that check for checkmates
struct checking check4checkmates_2(enum turn *player_turn, struct Piece *board,
  enum king_status white_kingstatus, enum king_status black_kingstatus,
  int x_kingb, int y_kingb, int x_kingw, int y_kingw, int des_x, int des_y,
   struct Player *player1, struct Player *player2, GtkLabel *Info, GtkWidget *Window, GtkWidget *Window2);

//White Team wins
void whiteT_Wins(struct Player *pl1, struct Player *pl2, GtkLabel *Info, GtkWidget *Window,GtkWidget *Window2);

//Black Team wins
void blackT_Wins(struct Player *pl1, struct Player *pl2, GtkLabel *Info, GtkWidget *Window,GtkWidget *Window2);


#endif
