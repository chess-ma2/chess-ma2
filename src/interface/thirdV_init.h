#include <stdio.h>
#include <gtk/gtk.h>
#include <string.h>
#ifndef THIRDV_INIT_H
#define THIRDV_INIT_H

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
#include "../common/c/game/playwithrobot.c"

// Main Game Init function
void init_gtk3(struct Player *player1, struct Player *player2, struct construction constr, GtkLabel *Rules, GtkLabel *Info, GtkLabel *turn, struct for_clicked *needed, GtkWidget *EndWindow);



#endif
