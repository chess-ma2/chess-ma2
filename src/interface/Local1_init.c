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
#include "Local1_init.h"

#ifndef LOCAL1_INIT_C
#define LOCAL1_INIT_C

/*
 * @author Anna
 * @date 01/05/2021
 * @details GKT Dialog
*/
void transition_page(GtkWidget *PREwindow, GtkWidget *PASTwindow)
{
  GtkWidget *dialog;
  dialog = gtk_message_dialog_new(GTK_WINDOW(PREwindow),
            GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_INFO,
            GTK_BUTTONS_OK,
            "Player n°1 is all up and done!");
  gtk_window_set_title(GTK_WINDOW(dialog), "On to player n°2");
  gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG (dialog), "Please now give the device to player n°2!");

  struct windows for_rees;
  for_rees.New_pl = PREwindow;
  for_rees.Login = PASTwindow;

  // Link to subfunction
  g_signal_connect(GTK_DIALOG (dialog), "response", G_CALLBACK (on_response), &for_rees);
  gtk_dialog_run (GTK_DIALOG (dialog));
  //gtk_widget_destroy(dialog);
}

/*
 * @author Anna
 * @date 10/04/2021 - 16/04/2021
 * @details draw chessboard without chess pieces
*/

// Signal handler for the "draw" signal of the drawing area.
gboolean on_draw(GtkWidget *widget, cairo_t *cr, gpointer user_data)
{
    struct construction *res = user_data;

    int c = 0; //white
    int x = 56; //original coordinates
    int y = 90; //original coordinates
    int width = 60;
    int height = 60;

    //Iterate through chessboard
    for (size_t i = 0; i < 8; i++) {
      for (size_t j = 0; j < 8; j++) {

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

  // If the button clicked gives response "Login" == OK (response_id being -5)
  if (response_id == GTK_RESPONSE_OK)
  { // Go to login page
    gtk_widget_show(res->Login);
    gtk_widget_hide(res->New_pl);
  }
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
  strcpy((char *)&password, password1);

  // Connect to Database
  creatingTables();

  // If email is already in Database
  if(email_in_DB(email) == 1)
  {
    // Create dialog if email in db
    GtkWidget *dialog;
    dialog = GTK_WIDGET (gtk_message_dialog_new (GTK_WINDOW(parentwindow),
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
    strcpy((char *)&password, password1);
    //testing if email is in database
    if (email_in_DB(email) && rightPassword(email, password))
    {
        p->email=email;
        //p->name=printNAME(email);
        p->nb_won=getWINS(email);
        p->nb_lost=getLOST(email);
        return p;
    }
    else
    {
        return NULL;
    }

}

// ____________________     Game    _____________________________________
void printRulesLabel(GtkLabel *Rules)
{
  char *rules = " _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n|                                Rules                                  |\n|                                                                            |\n| If you wish to Withdraw please click on         |\n|                the Withdraw button                          |\n|                                                                            |\n|                                                                            |\n| If you want to ask for a stalemate please      |\n|      click on the stalemate button                     |\n|                                                                            |\n|                                                                            |\n| White team =  ♙  ♖  ♘  ♗  ♔  ♕                          |\n| Black team =  ♟  ♜  ♞  ♝  ♚  ♛                          |\n|_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _|\n";
  gtk_label_set_text (Rules, rules);
}


/*
 * @author Anna
 * @date 01/05/2021
 * @details Prints who's turn it is
*/
void playerturn_print(enum turn *player_turn, struct Player *player1, struct Player *player2, GtkLabel *turn)
{
  char *infoo = malloc(700 * sizeof(char));
  strcpy(infoo, player1->name);
  if(*player_turn == WHITETURN)
  {
    if (player1->team_color == 1)
      strcpy(infoo, player2->name);
    strcat(infoo, " ,it's your turn to play (White)");
  }
  else
  {
    if (player1->team_color == 0)
        strcpy(infoo, player2->name);
    strcat(infoo, " ,it's your turn to play (Black)");
  }
  gtk_label_set_text(turn, infoo);
  free(infoo);
}

/*
 * @author Anna and Marine
 * @date 21/04/2021
 * @details Main Game function (from version1 originaly)
*/

void init_gtk(struct Player *player1, struct Player *player2, struct construction constr, GtkLabel *Rules, GtkLabel *Info, GtkLabel *turn, struct for_clicked *needed, GtkWidget *EndWindow)
{
  //_______________ Variables
  // Current white chess pieces on chessboard
  struct currentpiece *currentW = create_whiteList();
  int nbWhite = 16;

  // Current black chess pieces on chessboard
  struct currentpiece *currentB = create_blackList();
  int nbBlack = 16;

  //kings'positions to know if check or checkmat
  int x_kingb = 4;
  int y_kingb = 0;
  int x_kingw = 4;
  int y_kingw = 7;
  enum rock white_rock = CAN_ROCK;
  enum rock black_rock = CAN_ROCK;
  enum king_status white_kingstatus = NOTHING;
  enum king_status black_kingstatus = NOTHING;

  //____________________________________________________________________________

  //___________________ Random to get which player starts
  int starts = rand() % 2;
  if (starts == 0)
  {
      player1->team_color = 0; // Player 1 is white
      player2->team_color = 1; // Player 2 is black
  }
  else
  {
      player1->team_color = 1; // Player 1 is black
      player2->team_color = 0; // Player 2 is white
  }
  player1->name = getNAME(player1->email);
  player2->name = getNAME(player2->email);
  //____________________________________________________________________________
  playerturn_print(needed->player_turn, player1, player2, turn);

  // Show Board
  update_board(constr);

  // Define needed variables
  needed->player1 = player1;
  needed->player2 = player2;
  needed->turn = turn;
  needed->Info = Info;

  gtk_label_set_text(Info, "\n  Please select the chess piece you want to move (ex: A3)");
  needed->currentW = currentW;
  needed->nbWhite = nbWhite;
  needed->currentB = currentB;
  needed->nbBlack = nbBlack;
  needed->x_kingw = x_kingw;
  needed->y_kingw = y_kingw;
  needed->x_kingb = x_kingb;
  needed->y_kingb = y_kingb;
  needed->white_rock = white_rock;
  needed->black_rock = black_rock;
  needed->white_kingstatus = white_kingstatus;
  needed->black_kingstatus = black_kingstatus;
  needed->EndWindow = EndWindow;
  return;
}

/*
 * @author Anna
 * @date 01/05/2021
 * @details Updates board images after a move
*/

void update_board(struct construction constr){
  // All Images
  char normal_images_cha[][sizeof("Images/blackBISHOP_N.png")] = {"Images/whitePAWN_N.png", "Images/whiteROOK_N.png", "Images/whiteBISHOP_N.png", "Images/whiteKNIGHT_N.png", "Images/whiteQUEEN_N.png","Images/whiteKING_N.png", "Images/blackPAWN_N.png", "Images/blackROOK_N.png", "Images/blackBISHOP_N.png", "Images/blackKNIGHT_N.png", "Images/blackQUEEN_N.png","Images/blackKING_N.png"};
  char epita_images_cha[][sizeof("Images/blackBISHOP_N.png")] = {"Images/epita_white.png", "Images/marie_white.png", "Images/anna_white.png", "Images/antoine_white.png", "Images/marine_white.png","Images/king_white.png", "Images/epita_black.png", "Images/marie_black.png", "Images/anna_black.png", "Images/antoine_black.png", "Images/marine_black.png","Images/king_black.png"};


  int x = 56; //original coordinates
  int y = 90; //original coordinates

  int width = 60;
  int height = 60;

  //Iterate through chessboard
  for (size_t i = 0; i < 8; i++) {
    for (size_t j = 0; j < 8; j++) {

      // Current piece of Board
      struct Piece current = constr.board[i*8+j];
      // Get correct index for image from list in .h
      int in = -1;

      if(current.color == BLACK){
      switch(current.type){
          case PAWN: in = 6; break;
          case ROOK: in = 7; break;
          case BISHOP: in = 8; break;
          case KNIGHT: in = 9; break;
          case QUEEN: in = 10; break;
          case KING: in = 11; break;
          default: in = -1; }}
      else {
      switch(current.type)
      {   case PAWN: in = 0; break;
          case ROOK: in = 1; break;
          case BISHOP: in = 2; break;
          case KNIGHT: in = 3; break;
          case QUEEN: in = 4; break;
          case KING: in = 5; break;
          default: in = -1;} }

      // Sets info on Image
      if (in != -1) {
        if (constr.type == EPITA) {
          gtk_image_set_from_file(GTK_IMAGE(constr.ImageBoard[i*8+j]), epita_images_cha[in]);
        }
        else
        {
          gtk_image_set_from_file(GTK_IMAGE(constr.ImageBoard[i*8+j]), normal_images_cha[in]);
        }
        gtk_widget_show(constr.ImageBoard[i*8+j]);
      }
      else
      {
        gtk_image_set_from_file(GTK_IMAGE(constr.ImageBoard[i*8+j]), normal_images_cha[0]);
        gtk_widget_hide(constr.ImageBoard[i*8+j]);
      }
      x += width;
    }
    x = 56;
    y += height;
  }
}

#endif
