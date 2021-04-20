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

#ifndef LOCAL1_C
#define LOCAL1_C




/*
 * @author Anna
 * @date 10/04/2021 - 16/04/2021
 * @details draw chessboard without chess pieces
*/

// Signal handler for the "draw" signal of the drawing area.
gboolean on_draw(GtkWidget *widget, cairo_t *cr, gpointer user_data)
{
    // All Images
    char normal_images_cha[][sizeof("Images/blackBISHOP_N.png")] = {"Images/whitePAWN_N.png", "Images/whiteROOK_N.png", "Images/whiteBISHOP_N.png", "Images/whiteKNIGHT_N.png", "Images/whiteQUEEN_N.png","Images/whiteKING_N.png", "Images/blackPAWN_N.png", "Images/blackROOK_N.png", "Images/blackBISHOP_N.png", "Images/blackKNIGHT_N.png", "Images/blackQUEEN_N.png","Images/blackKING_N.png"};
    struct construction *res = user_data;
    printf("%s\n", normal_images_cha[0]);

    int c = 0; //white
    int x = 56; //original coordinates
    int y = 90; //original coordinates
    int width = 60;
    int height = 60;

    //Iterate through chessboard
    for (size_t i = 0; i < 8; i++) {
      for (size_t j = 0; j < 8; j++) {

        // Current piece of Board
        struct Piece current = res->board[i*8+j];
        // Current button
        GtkWidget *current_button = res->Bboard[i*8+j];

        // Get correct index for image from list in .h
        int i = -1;

        if(current.color == BLACK){
        switch(current.type){
            case PAWN: i = 6; break;
            case ROOK: i = 7; break;
            case BISHOP: i = 8; break;
            case KNIGHT: i = 9; break;
            case QUEEN: i = 10; break;
            case KING: i = 11; break;
            default: i = -1; }}
        else {
        switch(current.type)
        {   case PAWN: i = 0; break;
            case ROOK: i = 1; break;
            case BISHOP: i = 2; break;
            case KNIGHT: i = 3; break;
            case QUEEN: i = 4; break;
            case KING: i = 5; break;
            default: i = -1;} }


        gtk_widget_set_size_request (current_button,60,60);
        gtk_widget_set_opacity(current_button , 0.01);
        gtk_fixed_put (res->fixed, current_button, x + 15, y + 15);
        gtk_widget_show(current_button);

        if (i != -1) {
          res->ImageBoard[i] = gtk_image_new_from_file(normal_images_cha[i]);
          gtk_widget_set_size_request (res->ImageBoard[i],60,60);
        //  gtk_widget_set_opacity(res->ImageBoard[i] , 0.2);
          gtk_fixed_put (res->fixed, res->ImageBoard[i], x + 15, y + 15);
          gtk_widget_show(res->ImageBoard[i]);
        }


        if (c == 0) {
          // Draws the rectangle in bright-ish color.
          cairo_set_source_rgb(cr, 0.9, 0.7, 0.5);
        }
        else{
          // Draws the rectangle in dark-ish color
          cairo_set_source_rgb(cr, 0.8, 0, 0.2);
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

/*
 * @author Anna
 * @date 20/04/2021
 * @details Subfunction when email already in db
*/

void on_response (GtkDialog *dialog,
             gint       response_id,
             gpointer   user_data)
{
  // Get parent window and login window
  struct windows *res = user_data;

  /* If the button clicked gives response "Login" == OK (response_id being -5) */
  if (response_id == GTK_RESPONSE_OK)
  { // Go to login page
    gtk_widget_show(res->Login);
    gtk_widget_hide(res->New_pl);
  }

  /* If the button clicked gives response "Create New Account" == CANCEL (response_id being -6) */
  else if (response_id == GTK_RESPONSE_CANCEL)
  {
    gtk_label_set_text (res->label, "Please create a new account with a new email.");
    gtk_entry_set_text(res->Name, "");
    gtk_entry_set_text(res->Email, "");
    gtk_entry_set_text(res->Password, "");
  }

  /* If the message dialog is destroyed (for example by pressing escape) */
  else if (response_id == GTK_RESPONSE_DELETE_EVENT)
     g_print ("dialog closed or cancelled\n");

  /* Destroy the dialog after one of the above actions have taken place */
  gtk_widget_destroy (GTK_WIDGET (dialog));

}

/*
 * @author Anna
 * @date 1/04/2021 - 20/04/2021
 * @details Create New Player in database
*/

struct Player * New_player_v1(GtkEntry* Name_Entry1, GtkEntry* Email_Entry1, GtkEntry* Password_Entry1, GtkLabel* Create_account1_yes, GtkWidget *parentwindow, GtkWidget *login_window)
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

  // If email is already in Database
  if(email_in_DB(email) == 1)
  {
    // Create dialog if email in db
    GtkWidget *dialog;
    dialog = GTK_WIDGET (gtk_message_dialog_new (parentwindow,
                                               GTK_DIALOG_MODAL|
                                               GTK_DIALOG_DESTROY_WITH_PARENT|
                                               GTK_DIALOG_USE_HEADER_BAR,
                                               GTK_MESSAGE_INFO,
                                               GTK_BUTTONS_NONE,
                                               "Email already affiliated to an account"));
  gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG (dialog), "Do you wish to login? \n Otherwise you must create an account with another email.");

  // Buttons for dialog
  gtk_dialog_add_buttons (GTK_DIALOG (dialog),
                          "Create New Account", GTK_RESPONSE_CANCEL,
                          "Login", GTK_RESPONSE_OK,
                          NULL);

  struct windows for_rees;
  for_rees.New_pl = parentwindow;
  for_rees.Login = login_window;
  for_rees.label = Create_account1_yes;
  for_rees.Name = Name_Entry1;
  for_rees.Email = Email_Entry1;
  for_rees.Password = Password_Entry1;

  // Link to subfunction
  g_signal_connect(GTK_DIALOG (dialog), "response", G_CALLBACK (on_response), &for_rees);
  gtk_dialog_run (GTK_DIALOG (dialog));
  return NULL;
}
else{

  // Create New Player
  newPLAYER( name, password, email, 0, 0);

  // Set text to delete password (added security)
  gtk_entry_set_text(Password_Entry1, "Your secret password is safe with us");

  // Tell user that account has been created
  gtk_label_set_text (Create_account1_yes, "Account created with success");

  // Define Player structure
  struct Player *pl = malloc(sizeof(struct Player));
  pl->email = email;
  pl->name=name;

  return pl;
  }

  //TODO for final presentation?:
    //   1) Get the nb of games won
    //   2) Get the nb of games lost

}

struct Player * findplayer(GtkEntry* mail, GtkEntry* pass)
{
    // Connect to Database
    creatingTables();

    struct Player *p = malloc(sizeof(struct Player));

    char * email = (char *)gtk_entry_get_text(mail);
    char * password1 = (char *) gtk_entry_get_text(pass);
    unsigned char password[64];
    // Copy to array to get password
    strcpy(&password, password1);
    //testing if email is in database
    if (email_in_DB(email) && rightPassword(email, password))
    {
        p->email=email;
        //p->name=printNAME(email);
        p->nb_won=getWINS(email);
        p->nb_lost=getLOST(email);
    }
    else
    {
        return NULL;
    }

}

#endif
