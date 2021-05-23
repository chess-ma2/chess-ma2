#include <stdio.h>
#include <gtk/gtk.h>
#include <string.h>
#ifndef LOCAL1_INIT_H
#define LOCAL1_INIT_H

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


// @struct Needed to create chessboard
struct construction{
  struct Piece *board;
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

// @struct for Clicked
struct for_clicked{
  GtkEntry * Ori_Coord;
  GtkEntry * New_Coord;
  struct Player *player1;
  struct Player *player2;
  GtkLabel *turn;
  GtkLabel *Info;
  struct currentpiece *currentW;
  int nbWhite;
  struct currentpiece *currentB;
  int nbBlack;
  int x_kingw;
  int y_kingw;
  int x_kingb;
  int y_kingb;
  enum turn *player_turn; // team's turn
  enum rock white_rock;
  enum rock black_rock;
  enum king_status white_kingstatus;
  enum king_status black_kingstatus;
  struct construction constr;
  GtkWidget *EndWindow;
  GtkWidget *Window;
};

// Players___________________________________________________________________
// GTK Dialog for transition page
void transition_page(GtkWidget *PREwindow, GtkWidget *PASTwindow);

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

// Prints rules
void printRulesLabel(GtkLabel *Rules);

// Prints who's turn it is
void playerturn_print(enum turn *player_turn, struct Player *player1, struct Player *player2, GtkLabel *turn);

// Main Game Init function
void init_gtk(struct Player *player1, struct Player *player2, struct construction constr, GtkLabel *Rules, GtkLabel *Info, GtkLabel *turn, struct for_clicked *needed, GtkWidget *EndWindow);

// Updates board images after a move or creates board
void update_board(struct construction constr);

#endif
