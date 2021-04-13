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
#include "../database/create_db.h"

//@struct Player
struct Player {
    char *name;
    unsigned char password[64];
    char *email;
    size_t nb_won;
    size_t nb_lost;
    int team_color;

};

// Player 1 _________________________________________________________

// Create New Player in database
void New_player_v1(GtkEntry* Name_Entry1, GtkEntry* Email_Entry1, GtkEntry* Password_Entry1, GtkLabel* Create_account1_yes);


// Game _________________________________________________________
gboolean on_draw(GtkWidget *widget, cairo_t *cr, gpointer user_data);
#endif
