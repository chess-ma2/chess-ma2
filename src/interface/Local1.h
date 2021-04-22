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


// @struct Needed to create chessboard
struct construction{
  struct Piece *board;
  GtkWidget **Bboard;
  GtkFixed *fixed;
  GtkWidget **ImageBoard;
};

// @enum Game Type (normal by default)
enum GAME_TYPE
{
    NORMAL,
    EPITA,
    INVERSE,
};

// @struct windows Needed
struct windows{
  GtkWidget *New_pl;
  GtkWidget * Login;
  GtkLabel* label;
  GtkEntry * Name;
  GtkEntry * Email;
  GtkEntry * Password;
};

// @struct coord
struct coord{
  int x;
  int y;
  GtkWidget **Bboard;
  GtkLabel *Info;
};

// À SUPPRIMER
struct Moves
{
    unsigned char x;
    unsigned char y;
};

// @struct TO PLAY
struct to_play{
  struct construction constr;
  GtkLabel *Rules;
  GtkLabel *Info;
  GtkLabel *turn;
};

// Players___________________________________________________________________
// Subfunction when email already in db
void on_response (GtkDialog *dialog,
             gint       response_id,
             gpointer   user_data);

// Create New Player in database and return the new player
struct Player * New_player_v1(GtkEntry* Name_Entry1, GtkEntry* Email_Entry1, GtkEntry* Password_Entry1, GtkLabel* Create_account1_yes, GtkWidget *parentwindow, GtkWidget *login_window);

struct Player * findplayer(GtkEntry* mail, GtkEntry* pass);


// Game _________________________________________________________
// Draw chessboard
gboolean on_draw(GtkWidget *widget, cairo_t *cr, gpointer user_data);

void change_boarders(struct coord *org);

void on_clickedB(GtkButton *button, gpointer user_data);

void printRulesLabel(GtkLabel *Rules);

void whiteplayerturn(struct Player *player1, struct Player *player2, GtkLabel *turn);

void blackplayerturn(struct Player *player1, struct Player *player2, GtkLabel *turn);

// Main Game function
void play_gtk(struct Player *pl1, struct Player *pl2, struct construction constr, GtkLabel *Rules, GtkLabel *Info, GtkLabel *turn);

#endif
