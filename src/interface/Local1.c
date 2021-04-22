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

// ____________________     Game    _____________________________________
//__ Global Variables _____
int second_clicked = 0;
int x = 0;
int y = 0;
int des_x = 0;
int des_y = 0;

void change_boarders(struct coord *org)
{
  // TODO: get possible moves from function
  // FOR NOW: LIL EXAMPLE WITH (0,0) (7,7)
  struct Moves possible[2];
  int nb_moves = 2;
  for (int i = 0; i < nb_moves; i++) {
    GdkColor color;
    gdk_color_parse ("green", &color);
    GtkWidget *current_button = org->Bboard[possible->y * 8 + possible->x];
    gtk_widget_modify_bg ( GTK_WIDGET(current_button), GTK_STATE_NORMAL, &color);
    gtk_widget_set_opacity(current_button , 0.20);
    gtk_widget_show(current_button);
  }
}


/*
 * @author Anna
 * @date 22/04/2021
 * @details On button clicked
 */
void on_clickedB(GtkButton *button, gpointer user_data)
{
  struct coord * aboutB = user_data;
  if (second_clicked == 0) { // Chose original chess piece
    x = aboutB->x;
    y = aboutB->y;
    // Change possible moves' border
    change_boarders(aboutB);
    // Change info label
    gtk_label_set_text (aboutB->Info, "Please select a chess piece that is selected to play your move");
    // Is now second time clicked
    second_clicked = 1;
  }
  else // Chose destination chess piece
  {
    des_x = aboutB->x;
    des_y = aboutB->y;
    // second_clicked = 1 -> move piece in play function
  }
 }


void printRulesLabel(GtkLabel *Rules)
{
  char *rules = " _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n|                  Rules                        |\n|                                               |\n| If you wish to Withdraw please click on       |\n|              the Withdraw button              |\n|                                               |\n|                                               |\n| If you want to ask for a stalemate please     |\n|      click on the stalemate buttons           |\n|                                               |\n|                                               |\n| White team =  ♙  ♖  ♘  ♗  ♔  ♕                |\n| Black team =  ♟  ♜  ♞  ♝  ♚  ♛                |\n|_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _|\n";

  gtk_label_set_text (Rules, rules);
}

void whiteplayerturn(struct Player *player1, struct Player *player2, GtkLabel *turn)
{
  if (player1->team_color == 0) {
    printf("before get name \n");
    char *name = getNAME(player1->email);
    printf(" after get name \n");
    printf("name if %s \n", name);
    char *white = " (White), it is your turn to play";
    strcat(name, white);
    gtk_label_set_text (turn, name);
  }
  else
  {
    char *name = getNAME(player2->email);
    char *white = " (White), it is your turn to play";
    strcat(name, white);
    gtk_label_set_text (turn, name);
  }
}

void blackplayerturn(struct Player *player1, struct Player *player2, GtkLabel *turn)
{
  if (player1->team_color == 1) {
    char *name = getNAME(player1->email);
    char *black = " (Black), it is your turn to play";
    strcat(name, black);
    gtk_label_set_text (turn, name);
  }
  else
  {
    char *name = getNAME(player2->email);
    char *black = " (Black), it is your turn to play";
    strcat(name, black);
    gtk_label_set_text (turn, name);
  }
}

/*
 * @author Anna and Marine
 * @date 21/04/2021
 * @details Main Game function (from version1 originaly)
*/

void play_gtk(struct Player *player1, struct Player *player2, struct construction constr, GtkLabel *Rules, GtkLabel *Info, GtkLabel *turn)
{
  printf("in play \n");
  // #TODO
  // 1) Print Rules in rulesL
  // 2) Get player's color and turn + play
  // 3) Print that
  // 4) Get clicked button
  // 5) Get possible moves for position and change its buttons borders
  // 6) Button -> if second clicked (extra variable)
  //              then move piece and call on draw? (check if it doesn't do it by itself)
  // 7) Update needed positions and player's turn

  // Variables _________________________________________________________________
  struct Piece* board = constr.board;

  //_______________ Variables
  // Current white chess pieces on chessboard
  struct currentpiece *currentW = create_whiteList();
  int nbWhite = 16;

  // Current black chess pieces on chessboard
  struct currentpiece *currentB = create_blackList();
  int nbBlack = 16;

  //kings'positions to know if check or checkmat
  int x_kingw = 4;
  int y_kingw = 0;
  int x_kingb = 4;
  int y_kingb = 7;

  enum turn player_turn = WHITETURN; // team's turn
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

  //____________________________________________________________________________
  // 1
  printf("before print rules \n");
  printRulesLabel(Rules);
  printf("after print rules \n");
  // 2 + 3 + Start Game
  while( white_kingstatus != CHECKMATE || black_kingstatus != CHECKMATE ) //continue while not chessmate
    {
      if (player_turn == WHITETURN) { whiteplayerturn(player1, player2, turn);} // Prints who's turn it is
      else{ blackplayerturn(player1, player2, turn); }

      gtk_label_set_text (Info, "Please select the chess piece you want to move (ex: A3)");

      if (second_clicked == 1) { // Move detected
        // To align with Marie's logic -> -1
        x -= 1;
        des_x -= 1;

        //____________________________________ Game settings _____________________________________________________________
        //Rock
        struct res_rock res = rock_sub( player_turn, board, white_kingstatus, black_kingstatus, white_rock, black_rock, x_kingb, y_kingb, x_kingw, y_kingw, x, y, des_x, des_y);
        player_turn = res.player_turn;
        x_kingb = res.x_kingb;
        y_kingb = res.y_kingb;
        x_kingw = res.x_kingw;
        y_kingw = res.y_kingw;

        if (res.continuee == 1) {
          continue;
        }

        //Other chess piece movements
        int possible = isValidMove(x-1, y-1, des_x-1, des_y-1, board); //movement is possible


        switch(possible)
        {
            case 0:
                gtk_label_set_text(Info, "This move isn't possible for that chess piece, please check the rules.\n\n");
                break;
            case 2:
                 gtk_label_set_text(Info,"This move isn't possible because one or some coordinates are out of bounds\n\n");
                break;
            case 3:
                gtk_label_set_text(Info,"This move isn't possible because the chess piece on the destination coordinates is already yours!\n\n");
                break;
            case 4:
                gtk_label_set_text(Info,"This move isn't possible because there aren't any chess pieces to move!\n\n");
                break;
            case 1:
                // Check if there are any chess pieces on destination coordinates and if so remove them from list
                // AND modifies in List coordinates of the chess piece that's moved

                if (player_turn == WHITETURN) {
                  nbWhite = removedpiece(x-1 , y-1, des_x-1, des_y-1, board, currentW, nbWhite); }
                else { nbBlack = removedpiece(x-1 , y-1, des_x-1, des_y-1, board, currentB, nbBlack); }


                //Move chess piece
                board = pieceMove(x-1 , y-1, des_x-1, des_y-1, board);

              //________ King ____________
                if(board[(y-1)*8+(x-1)].color == WHITE && board[(y-1)*8+(x-1)].type == KING) //change position of the king to help check/pat/checkmat
            	    {
            	      x_kingw = des_x - 1;
            	      y_kingw = des_y - 1;
            	      white_rock = CANT_ROCK;
            	    }

            	  if(board[(y-1)*8+(x-1)].color == BLACK && board[(y-1)*8+(x-1)].type == KING)
            	    {
            	      x_kingb = des_x - 1;
            	      y_kingb = des_y - 1;
            	      black_rock = CANT_ROCK;
            	    }

                //___________________________


                // Impossible move
            	  if((player_turn == BLACKTURN && piece_to_place(x_kingb, y_kingb, board) == 1 ) || (player_turn == WHITETURN && piece_to_place(x_kingw, y_kingw, board) == 1))
            	    {
                    board = pieceMove(des_x-1, des_y-1, x-1, y-1, board);
            	      gtk_label_set_text(Info, "Impossible to move the king as checkmate would be unavoidable\n");

            	      if(board[(y-1)*8+(x-1)].color == BLACK && board[(y-1)*8+(x-1)].type == KING) //change position of the king to help check/pat/checkmat
            		    {   x_kingb = x - 1;
            		        y_kingb = y - 1; }

                   if(board[(y-1)*8+(x-1)].color == WHITE && board[(y-1)*8+(x-1)].type == KING) //change position of the king to help check/pat/checkmat
                   {    x_kingw = x - 1;
                        y_kingw = y - 1; }
            	      continue;
            	    }

                // Check for checkmates _________________________________________
                struct checking res = check4checkmates( player_turn, board, white_kingstatus, black_kingstatus, x_kingb, y_kingb, x_kingw, y_kingw, des_x, des_y,  player1, player2);
                player_turn = res.player_turn;
                white_kingstatus = res.white_kingstatus;
                black_kingstatus = res.black_kingstatus;
                if (res.returned == 1)
                { return;}
          } // end switch
      second_clicked = 0;
    } // end if clicked x2
  }// While
}


#endif
