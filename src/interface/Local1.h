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
#include "../common/c/rules/check_and_pat.c"
#include "../common/c/rules/pieces.c"
#include "../common/c/rules/plate.c"

// @struct Player
struct Player {
    char *name;
    char *email;
    size_t nb_won;
    size_t nb_lost;
    int team_color;

};

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


// Player 1 _________________________________________________________

// Create New Player in database and return the new player
struct Player * New_player_v1(GtkEntry* Name_Entry1, GtkEntry* Email_Entry1, GtkEntry* Password_Entry1, GtkLabel* Create_account1_yes);

struct Player * findplayer(GtkEntry* mail, GtkEntry* pass);


// Game _________________________________________________________
// Draw chessboard
gboolean on_draw(GtkWidget *widget, cairo_t *cr, gpointer user_data);
#endif
