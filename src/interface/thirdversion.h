#include <stdio.h>
#include <gtk/gtk.h>
#include <string.h>
#ifndef THIRDVERSION_H
#define THIRDVERSION_H

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
#include "thirdV_init.c"


// Game _________________________________________________________

// When move is chosen
void click4move_3(GtkButton *button, gpointer user_data);


#endif
