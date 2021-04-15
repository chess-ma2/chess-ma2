#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>
#include <unistd.h>
#include <stdio.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "Local1.h"

/*
 * @author Anna
 * @date 10/04/2021
 * @details draw chessboard without chess pieces
*/

// Signal handler for the "draw" signal of the drawing area.
gboolean on_draw(GtkWidget *widget, cairo_t *cr, gpointer user_data)
{
    // Gets the rectangle.
    //GdkRectangle *r = user_data;
    int c = 0; //white
    int x = 56; //original coordinates
    int y = 90; //original coordinates
    int width = 30;
    int height = 30;

    // Sets the background to white.
    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_paint(cr);

    //Iterate through chessboard
    for (size_t i = 0; i < 8; i++) {
      for (size_t j = 0; j < 8; j++) {
        if (c == 0) {
          // Draws the rectangle in white.
          cairo_set_source_rgb(cr, 1, 1, 1);
        }
        else{
          // Draws the rectangle in black.
          cairo_set_source_rgb(cr, 0, 0, 0);
        }
        //cairo_paint(cr);
        cairo_rectangle(cr, x, y, width, height);
        cairo_fill(cr);

        x += width;
        if (c == 0) { c = 1; }
        else{ c = 0; }
      }
      if (c == 0) { c = 1; }
      else{ c = 0; }

      x = 56;
      y += height;
    }

    // Propagates the signal.
    return FALSE;
}

// Create New Player in database
struct Player * New_player_v1(GtkEntry* Name_Entry1, GtkEntry* Email_Entry1, GtkEntry* Password_Entry1, GtkLabel* Create_account1_yes )
{
  // Get name from Entry
  char * name = (char *) gtk_entry_get_text(Name_Entry1);
  // Get Email from Entry
  char * email = (char *)gtk_entry_get_text(Email_Entry1);
  // Get Password from Entry
  char * password1 = (char *) gtk_entry_get_text(Password_Entry1);
  unsigned char password[64];
  // Copy to array to get password
  strcpy(&password, password1);

  // Connect to Database
  creatingTables();

  // Create New Player
  newPLAYER( name, password, email, 0, 0);

  // Set text to delete password (added security)
  gtk_entry_set_text(Password_Entry1, "Your secret password is safe with us");

  // Tell user that account has been created
  gtk_label_set_text (Create_account1_yes, "Account created with success");

  // Define Player structure
  struct Player *pl = malloc(sizeof(struct Player));
  pl->email = email;

  return pl;

  //TODO for final presentation?:
    //   1) Get the nb of games won
    //   2) Get the nb of games lost

}
