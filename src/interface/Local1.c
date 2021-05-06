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
        return p;
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
    //gdk_color_parse ("green", &color);
    GtkWidget *current_button = org->Bboard[possible->y * 8 + possible->x];
    //gtk_widget_modify_bg ( GTK_WIDGET(current_button), GTK_STATE_NORMAL, &color);
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
  printf("\n \n \n clicked \n \n \n");
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
  char *rules = " _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n|                                Rules                                  |\n|                                                                            |\n| If you wish to Withdraw please click on         |\n|                the Withdraw button                          |\n|                                                                            |\n|                                                                            |\n| If you want to ask for a stalemate please      |\n|      click on the stalemate button                     |\n|                                                                            |\n|                                                                            |\n| White team =  ♙  ♖  ♘  ♗  ♔  ♕                          |\n| Black team =  ♟  ♜  ♞  ♝  ♚  ♛                          |\n|_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _|\n";

  gtk_label_set_text (Rules, rules);
}

void whiteplayerturn(struct Player *player1, struct Player *player2, GtkLabel *turn)
{
  if (player1->team_color == 0) {
    char *name = getNAME(player1->email);
    char *white = " (White), it is your turn to play";
    strcat(name, white);
    gtk_label_set_text (turn, name);
    return;
  }
  else
  {
    char *name = getNAME(player2->email);
    char *white = " (White), it is your turn to play";
    strcat(name, white);
    gtk_label_set_text (turn, name);
    return;
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
 * @author Anna
 * @date 01/05/2021
 * @details Updates board images after a move
*/
void update_board(struct construction constr){
  // All Images
  char normal_images_cha[][sizeof("Images/blackBISHOP_N.png")] = {"Images/whitePAWN_N.png", "Images/whiteROOK_N.png", "Images/whiteBISHOP_N.png", "Images/whiteKNIGHT_N.png", "Images/whiteQUEEN_N.png","Images/whiteKING_N.png", "Images/blackPAWN_N.png", "Images/blackROOK_N.png", "Images/blackBISHOP_N.png", "Images/blackKNIGHT_N.png", "Images/blackQUEEN_N.png","Images/blackKING_N.png"};

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
        gtk_image_set_from_file(constr.ImageBoard[i*8+j], normal_images_cha[in]);
        gtk_widget_set_size_request (constr.ImageBoard[i*8+j],60,60);
        gtk_fixed_put (constr.fixed, constr.ImageBoard[i*8+j], x + 15, y + 15);
        gtk_widget_show(constr.ImageBoard[i*8+j]);
      }
      else
      {
        gtk_image_clear(constr.ImageBoard[i*8+j]);
      }
      x += width;
    }
    x = 56;
    y += height;
  }
}

/*
 * @author Anna
 * @date 04/05/2021
 * @details When won shows message and updates database
*/
void win_update(GtkLabel *Info, struct Player *pl1, struct Player *pl2, enum turn player_turn)
{

  if(pl1->team_color == 0 && player_turn == WHITETURN)
  {
    update_victory(pl1->email);
    update_loss(pl2->email);
    char *name = getNAME(pl1->email);
    char *white = " (White), won this game well done!";
    strcat(name, white);
    gtk_label_set_text(Info, name);
  }

  if(pl2->team_color == 0 && player_turn == WHITETURN)
  {
    update_victory(pl2->email);
    update_loss(pl1->email);
    char *name = getNAME(pl2->email);
    char *white = " (White), won this game well done!";
    strcat(name, white);
    gtk_label_set_text(Info, name);
  }

  if(pl1->team_color == 1 && player_turn == BLACKTURN)
  {
    update_victory(pl1->email);
    update_loss(pl2->email);
    char *name = getNAME(pl1->email);
    char *white = " (Black), won this game well done!";
    strcat(name, white);
    gtk_label_set_text(Info, name);
  }
  if(pl2->team_color == 1 && player_turn == BLACKTURN)
  {
    update_victory(pl2->email);
    update_loss(pl1->email);
    char *name = getNAME(pl2->email);
    char *white = " (Black), won this game well done!";
    strcat(name, white);
    gtk_label_set_text(Info, name);
  }
}

// Subfunction needed
// Subfunction check for checkmates
struct checking check4checkmates_2(enum turn player_turn, struct Piece *board,
  enum king_status white_kingstatus, enum king_status black_kingstatus,
  int x_kingb, int y_kingb, int x_kingw, int y_kingw, int des_x, int des_y,
   struct Player *pl1, struct Player *pl2, GtkLabel *Info)
  {
    int returned = 0;
    //___________________________ Black team's turn
    if(player_turn == BLACKTURN)
      {
        if (kingcheck_place(x_kingw, y_kingw, des_x-1, des_y-1, board) == 1) {
          white_kingstatus = CHECK;
          gtk_label_set_text(Info,"Checkmate for the white king \n");
        }

        if (kingcheck_place(x_kingb, y_kingb, des_x-1, des_y-1, board) == 0)
          black_kingstatus = NOTHING;

        if (check_mat(x_kingw, y_kingw, WHITE,  board)== 1) {
          if(pl1->team_color == 1)
          {
            update_victory(pl1->email);
            update_loss(pl2->email);
            char *name = getNAME(pl1->email);
            char *white = " (Black), won this game well done!";
            strcat(name, white);
            gtk_label_set_text(Info, name);
          }
          else
          {
            update_victory(pl2->email);
            update_loss(pl1->email);
            char *name = getNAME(pl2->email);
            char *white = " (Black), won this game well done!";
            strcat(name, white);
            gtk_label_set_text(Info, name);
          }
          returned = 1;
        }
        player_turn = WHITETURN;
      }
      else//___________________________ White team's turn
      {
        if (kingcheck_place( x_kingb, y_kingb, des_x-1, des_y-1, board) == 1) {
          black_kingstatus = CHECK;
          printf("Checkmate for the black king \n");
        }

        if (kingcheck_place( x_kingw, y_kingw, des_x-1, des_y-1, board) == 0)
          white_kingstatus = NOTHING;

        if (check_mat(x_kingb, y_kingb, BLACK, board)== 1) {
          if(pl1->team_color == 0)
          {
            update_victory(pl1->email);
            update_loss(pl2->email);
            char *name = getNAME(pl1->email);
            char *white = " (White), won this game well done!";
            strcat(name, white);
            gtk_label_set_text(Info, name);
          }
          else
          {
            update_victory(pl2->email);
            update_loss(pl1->email);
            char *name = getNAME(pl2->email);
            char *white = " (White), won this game well done!";
            strcat(name, white);
            gtk_label_set_text(Info, name);
          }
          returned = 1;
        }
        player_turn = BLACKTURN;
      }

    if((player_turn == WHITETURN && pat(x_kingb, y_kingb, board)) || (player_turn == BLACKTURN && pat(x_kingw, y_kingw, board)))
      {
        gtk_label_set_text(Info, "\n It's a draw!! \n");
        update_victory(pl1->email);
        update_victory(pl2->email);
        returned = 1;
      }

  struct checking res = { player_turn, white_kingstatus, black_kingstatus, returned };
  return res;
  }



/*
 * @author Anna
 * @date 29/04/2021
 * @details Clicked for move
*/

void click4move(GtkButton *button, gpointer user_data)
{
  struct for_clicked *needed = user_data;
  if (needed->white_kingstatus == CHECKMATE || needed->black_kingstatus == CHECKMATE) {
    if (needed->white_kingstatus == CHECKMATE) {
      win_update(needed->Info, needed->player1, needed->player2, BLACKTURN);
    }
    else{
      win_update(needed->Info, needed->player1, needed->player2, WHITETURN);
    }
  }

  // Get Coordinates
  char * ori = (char *) gtk_entry_get_text(needed->Ori_Coord);
  char * new = (char *) gtk_entry_get_text(needed->New_Coord);

  if (incorrect_char(ori[0]) == 1 || incorrect_int((int)ori[1] - 48) == 1 ||
    incorrect_char(new[0]) == 1 || incorrect_int((int)new[1] - 48) == 1) {
    gtk_label_set_text(needed->Info, "Incorrect coordinates please try again");
    return;
  }
  int x = ((int)ori[0]) - 64;
  int des_x = (int)new[0] - 64;
  int y = (int)ori[1] - 48;
  int des_y = (int)new[1] - 48;
  //____________________________________ Game settings _____________________________________________________________
  //Rock
  struct res_rock res = rock_sub(needed->player_turn, needed->constr.board, needed->white_kingstatus,
    needed->black_kingstatus, needed->white_rock, needed->black_rock,needed-> x_kingb,
    needed->y_kingb, needed->x_kingw, needed->y_kingw, x, y, des_x, des_y);

  needed->player_turn = res.player_turn;
  needed->x_kingb = res.x_kingb;
  needed->y_kingb = res.y_kingb;
  needed->x_kingw = res.x_kingw;
  needed->y_kingw = res.y_kingw;

  if (res.continuee == 1) {
    // TURN FINISHED
    gtk_entry_set_text(needed->Ori_Coord, "");
    gtk_entry_set_text(needed->New_Coord, "");
    gtk_label_set_text(needed->Info, "New Turn");
  }
  //Other chess piece movements
  int possible = isValidMove(x-1, y-1, des_x-1, des_y-1, needed->constr.board); //movement is possible

  switch(possible)
  {
      case 0:
          gtk_label_set_text(needed->Info, "This move isn't possible for that chess piece, please check the rules.\n\n");
          break;
      case 2:
           gtk_label_set_text(needed->Info,"This move isn't possible because one or some coordinates are out of bounds\n\n");
          break;
      case 3:
          gtk_label_set_text(needed->Info,"This move isn't possible because the chess piece on the destination coordinates is already yours!\n\n");
          break;
      case 4:
          gtk_label_set_text(needed->Info,"This move isn't possible because there aren't any chess pieces to move!\n\n");
          break;
      case 1:
          // Check if there are any chess pieces on destination coordinates and if so remove them from list
          // AND modifies in List coordinates of the chess piece that's moved
          
          if (needed->player_turn == WHITETURN) {
            needed->nbWhite = removedpiece(x-1 , y-1, des_x-1, des_y-1, needed->constr.board, needed->currentW, needed->nbWhite); }
          else { needed->nbBlack = removedpiece(x-1 , y-1, des_x-1, des_y-1, needed->constr.board, needed->currentB, needed->nbBlack); }
          //Move chess piece
          needed->constr.board = pieceMove(x-1 , y-1, des_x-1, des_y-1, needed->constr.board);

        //________ King ____________
          if(needed->constr.board[(y-1)*8+(x-1)].color == WHITE && needed->constr.board[(y-1)*8+(x-1)].type == KING) //change position of the king to help check/pat/checkmat
            {
              needed->x_kingw = des_x - 1;
              needed->y_kingw = des_y - 1;
              needed->white_rock = CANT_ROCK;
            }

          if(needed->constr.board[(y-1)*8+(x-1)].color == BLACK && needed->constr.board[(y-1)*8+(x-1)].type == KING)
            {
              needed->x_kingb = des_x - 1;
              needed->y_kingb = des_y - 1;
              needed->black_rock = CANT_ROCK;
            }

          //___________________________
          // Impossible move
          if((needed->player_turn == BLACKTURN && piece_to_place(needed->x_kingb, needed->y_kingb, needed->constr.board) == 1 )
          || (needed->player_turn == WHITETURN && piece_to_place(needed->x_kingw, needed->y_kingw, needed->constr.board) == 1))
            {
              needed->constr.board = pieceMove(des_x-1, des_y-1, x-1, y-1, needed->constr.board);
              gtk_label_set_text(needed->Info, "Impossible to move the king as checkmate would be unavoidable\n");

              if(needed->constr.board[(y-1)*8+(x-1)].color == BLACK && needed->constr.board[(y-1)*8+(x-1)].type == KING) //change position of the king to help check/pat/checkmat
              {   needed->x_kingb = x - 1;
                  needed->y_kingb = y - 1; }

             if(needed->constr.board[(y-1)*8+(x-1)].color == WHITE && needed->constr.board[(y-1)*8+(x-1)].type == KING) //change position of the king to help check/pat/checkmat
             {    needed->x_kingw = x - 1;
                  needed->y_kingw = y - 1; }
              // NEXT TURN
              gtk_entry_set_text(needed->Ori_Coord, "");
              gtk_entry_set_text(needed->New_Coord, "");
              gtk_label_set_text(needed->Info, "New Turn");
            }

          // Check for checkmates _________________________________________
          struct checking res = check4checkmates_2(needed->player_turn, needed->constr.board, needed->white_kingstatus,
             needed->black_kingstatus, needed->x_kingb, needed->y_kingb, needed->x_kingw, needed->y_kingw,
             des_x, des_y,  needed->player1, needed->player2, needed->Info);
          needed->player_turn = res.player_turn;
          needed->white_kingstatus = res.white_kingstatus;
          needed->black_kingstatus = res.black_kingstatus;
          if (res.returned == 1)
          {
            gtk_entry_set_text(needed->Ori_Coord, "");
            gtk_entry_set_text(needed->New_Coord, "");
            gtk_label_set_text(needed->Info, "New Turn");
            return;}
          // Update board
          update_board(needed->constr);
    } // end switch

    if (needed->player_turn == WHITETURN) { whiteplayerturn(needed->player1,needed->player2, needed->turn);} // Prints who's turn it is
    else{ blackplayerturn(needed->player1, needed->player2, needed->turn); }
    gtk_label_set_text(needed->Info, "Please select the chess piece you want to move (ex: A3)");

}


/*
 * @author Anna and Marine
 * @date 21/04/2021
 * @details Main Game function (from version1 originaly)
*/

void init_gtk(struct Player *player1, struct Player *player2, struct construction constr, GtkLabel *Rules, GtkLabel *Info, GtkLabel *turn, struct for_clicked *needed)
{

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
  //struct Piece* board = constr.board;

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
  if (player_turn == WHITETURN) { whiteplayerturn(player1, player2, turn);} // Prints who's turn it is
  else{ blackplayerturn(player1, player2, turn); }

  // Show Board
  update_board(constr);

  //struct for_clicked *needed = malloc(sizeof(struct for_clicked));
  needed->player1 = player1;
  needed->player2 = player2;
  needed->turn = turn;
  needed->Info = Info;
  needed->currentW = currentW;
  needed->nbWhite = nbWhite;
  needed->currentB = currentB;
  needed->nbBlack = nbBlack;
  needed->x_kingw = x_kingw;
  needed->y_kingw = y_kingw;
  needed->x_kingb = x_kingb;
  needed->y_kingb = y_kingb;
  needed->player_turn = player_turn; // team's turn
  needed->white_rock = white_rock;
  needed->black_rock = black_rock;
  needed->white_kingstatus = white_kingstatus;
  needed->black_kingstatus = black_kingstatus;
  printf("init [ok]\n");
  return;
}


#endif
