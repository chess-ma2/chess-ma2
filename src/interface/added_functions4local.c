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
#include "added_functions4local.h"

#ifndef ADDED_FUNCTIONS4LOCAL_C
#define ADDED_FUNCTIONS4LOCAL_C

/*
 * @author Anna
 * @date 09/05/2021
 * @details Function for Withdraw
*/
void withdraw_2(GtkButton *button, gpointer user_data)
{
  // Get players and player turn
  struct added_F *res = user_data;
  enum turn *player_turn = res->player_turn;
  struct Player *pl1 = res->pl1;
  struct Player *pl2 = res->pl2;
  char *won = malloc(700 * sizeof(char));
  char *lost = malloc(700 * sizeof(char));

  if( (*player_turn == WHITETURN && pl1->team_color == 0 ) || (*player_turn == BLACKTURN && pl1->team_color == 1))
    {
        //Player 2 wins
        strcpy(lost, pl1->name);
        char *lost_sentence = " lost by resignation";
        strcat(lost, lost_sentence);
        strcpy(won, pl2->name);
        strcat(won, " wins! Congrats to the ");
        //char *won_sentence =" wins! Congrats to the ";
        if (*player_turn == WHITETURN) {
          strcat(won, "black team!\n");
        }
        else{
          strcat(won,"white team!\n");
        }
        update_victory(pl2->email);
        update_loss(pl1->email);
      }
    else
      {
        //Player 1 wins
        strcpy(lost, pl2->name);
        char *lost_sentence = " lost by resignation";
        strcat(lost, lost_sentence);
        strcpy(won, pl1->name);
        strcat(won, " wins! Congrats to the ");
        if (*player_turn == WHITETURN) {
          strcat(won, "black team!\n");
        }
        else{
          strcat(won,"white team!\n");
        }
        update_victory(pl1->email);
        update_loss(pl2->email);
      }
      // Show Dialog to inform players
      GtkWidget *dialog;
      dialog = gtk_message_dialog_new(GTK_WINDOW(res->Window),
            GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_INFO,
            GTK_BUTTONS_OK,
            "%s",won);
      gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG (dialog), "%s",lost);
      gtk_window_set_title(GTK_WINDOW(dialog), "End of game");
      gtk_dialog_run(GTK_DIALOG(dialog));
      gtk_widget_destroy(dialog);
      //gtk_window_unfullscreen(GTK_WINDOW(res->Window));
      gtk_widget_hide(res->Window);
      gtk_widget_show(res->EndWindow);
      free(won);
      free(lost);


}

/*
 * @author Anna
 * @date 09/05/2021
 * @details Subfunction for Stalemate
*/
void stalemate_dialog (GtkDialog *dialog,
             gint       response_id,
             gpointer   user_data)
{

  struct added_F *res = user_data;

  // If the button clicked gives response "Login" == OK (response_id being -5)
  // Get current name
  char *current_name = malloc(700 * sizeof(char));
  if((* res->player_turn == WHITETURN && res->pl1->team_color == 1) || (* res->player_turn == BLACKTURN && res->pl1->team_color == 0))
  {
    strcpy(current_name, res->pl1->name);
  }
  else
  {
    strcpy(current_name, res->pl2->name);
  }

  if (response_id == GTK_RESPONSE_OK)
  {
    if (* res->player_turn == WHITETURN)
      strcat(current_name, " (Black) accepted the stalemate, it's a draw!");
    else
      strcat(current_name,  " (White) accepted the stalemate, it's a draw!");

   update_victory(res->pl1->email);
   update_victory(res->pl2->email);

   GtkWidget *dialog_accept;
   dialog_accept = gtk_message_dialog_new(GTK_WINDOW(res->Window),
            GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_INFO,
            GTK_BUTTONS_OK,
            "%s",current_name);
  gtk_window_set_title(GTK_WINDOW(dialog_accept), "End of game");
  gtk_dialog_run(GTK_DIALOG(dialog_accept));
  gtk_widget_destroy(dialog_accept);
  //gtk_window_unfullscreen(GTK_WINDOW(res->Window));
  gtk_widget_show(res->EndWindow);
  gtk_widget_hide(res->Window);
  free(current_name);

  }
  else
  {

    if (* res->player_turn == WHITETURN)
      strcat(current_name,  " (Black) refuses so the game continues.");
    else
      strcat(current_name,  " (White) refuses so the game continues.");
   GtkWidget *dialog_info;
   dialog_info = gtk_message_dialog_new(GTK_WINDOW(res->Window),
            GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_INFO,
            GTK_BUTTONS_OK,
            "%s",current_name);
  gtk_window_set_title(GTK_WINDOW(dialog_info), "The show must go on");
  gtk_dialog_run(GTK_DIALOG(dialog_info));
  gtk_widget_destroy(dialog_info);
  free(current_name);
  }
}


/*
 * @author Anna
 * @date 09/05/2021
 * @details Function for Stalemate
*/
void stalemate_2(GtkButton *button, gpointer user_data)
{
  // Get players and player turn
  struct added_F *usrdata = user_data;
  enum turn *player_turn = usrdata->player_turn;
  struct Player *pl1 = usrdata->pl1;
  struct Player *pl2 = usrdata->pl2;

  // Ask for stalemate
  char *asks = "";
  if((* player_turn == WHITETURN && pl1->team_color == 0) || (*player_turn == BLACKTURN && pl1->team_color == 1))
    asks = getNAME(pl1->email);
  else
    asks = getNAME(pl2->email);

  if(*player_turn == WHITETURN)
    strcat(asks, " (White) is asking for a stalemate.");
  else
    strcat(asks, " (Black) is asking for a stalemate.");


  // GTK Dialog to ask for stalemate
  GtkWidget *dialog;
  dialog = GTK_WIDGET (gtk_message_dialog_new (GTK_WINDOW(usrdata->Window),
                                             GTK_DIALOG_MODAL|
                                             GTK_DIALOG_DESTROY_WITH_PARENT|
                                             GTK_DIALOG_USE_HEADER_BAR,
                                             GTK_MESSAGE_INFO,
                                             GTK_BUTTONS_NONE,
                                             "%s",asks));
gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG (dialog), "Do you accept?");
gtk_window_set_title(GTK_WINDOW(dialog), "Stalemate");

// Buttons for dialog
gtk_dialog_add_buttons (GTK_DIALOG (dialog),
                        "Yes", GTK_RESPONSE_OK,
                        "No", GTK_RESPONSE_CANCEL,
                        NULL);
// Connect to function for gtk dialog
g_signal_connect(GTK_DIALOG (dialog), "response", G_CALLBACK(stalemate_dialog), usrdata);
gtk_dialog_run (GTK_DIALOG (dialog));
gtk_widget_destroy (GTK_WIDGET (dialog));
}

void init_added_structures(struct Player *player1, struct Player *player2, struct added_F *needed, GtkWidget *EndWindow)
{
  needed->pl1 = player1;
  needed->pl2 = player2;
  needed->EndWindow = EndWindow;
  }

#endif
