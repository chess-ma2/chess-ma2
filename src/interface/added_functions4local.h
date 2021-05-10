#include <stdio.h>
#include <gtk/gtk.h>
#include <string.h>
#ifndef ADDED_FUNCTIONS4LOCAL_H
#define ADDED_FUNCTIONS4LOCAL_H
// Include Section
#include "../database/create_db.c"
#include "../database/functions_db.c"
#include "../common/c/game/version1.c"
#include "../common/c/game/added_functions.c"
#include "../common/c/rules/check_and_pat.c"
#include "../common/c/rules/pieces.c"
#include "../common/c/rules/plate.c"

// @struct Needed for Withdraw and Stalemate Subfunction
struct added_F{
    enum turn *player_turn;
    struct Player *pl1;
    struct Player *pl2;
    GtkWidget *Window;
};

// Function for Withdraw
void withdraw_2(GtkButton *button, gpointer user_data);

// Subfunction for Stalemate
void stalemate_dialog (GtkDialog *dialog,
             gint       response_id,
             gpointer   user_data);

// Function for Stalemate
void stalemate_2(GtkButton *button, gpointer user_data);


#endif
