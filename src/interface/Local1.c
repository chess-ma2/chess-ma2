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


/*
 * @author Anna
 * @date 23/05/2021
 * @details Quit Game
 */
void exitgame(GtkButton *button, gpointer user_data)
{
    gtk_main_quit();
}

/*
 * @author Anna
 * @date 25/04/2021
 * @details Subfunction that checks for checkmates
*/
struct checking check4checkmates_2(enum turn *player_turn, struct Piece *board,
  enum king_status white_kingstatus, enum king_status black_kingstatus,
  int x_kingb, int y_kingb, int x_kingw, int y_kingw, int des_x, int des_y,
   struct Player *pl1, struct Player *pl2, GtkLabel *Info)
  {
    int returned = 0; // Return 0 if no change has been done
    //___________________________ Black team's turn
    if(*player_turn == BLACKTURN)
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
            char *name = "";
            strcpy(name, pl1->name);
            char *white = " (Black), won this game well done!";
            strcat(name, white);
            gtk_label_set_text(Info, name);
          }
          else
          {
            update_victory(pl2->email);
            update_loss(pl1->email);
            char *name="";
            strcpy(name, pl2->name);
            char *white = " (Black), won this game well done!";
            strcat(name, white);
            gtk_label_set_text(Info, name);
          }
          returned = 1; // End of game
        }
        *player_turn = WHITETURN;
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
            char *name = "";
            strcpy(name, pl1->name);
            char *white = " (White), won this game well done!";
            strcat(name, white);
            gtk_label_set_text(Info, name);
          }
          else
          {
            update_victory(pl2->email);
            update_loss(pl1->email);
            char *name = "";
            strcpy(name, pl2->name);
            char *white = " (White), won this game well done!";
            strcat(name, white);
            gtk_label_set_text(Info, name);
          }
          returned = 1;
        }
        *player_turn = BLACKTURN;
      }

    if((*player_turn == WHITETURN && pat(x_kingb, y_kingb, board)) || (*player_turn == BLACKTURN && pat(x_kingw, y_kingw, board)))
      {
        gtk_label_set_text(Info, "\n It's a draw!! \n");
        update_victory(pl1->email);
        update_victory(pl2->email);
        returned = 1;
      }

  struct checking res = { WHITETURN, white_kingstatus, black_kingstatus, returned };
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
  struct res_rock res = rock_sub(* needed->player_turn, needed->constr.board, needed->white_kingstatus,
    needed->black_kingstatus, needed->white_rock, needed->black_rock,needed-> x_kingb,
    needed->y_kingb, needed->x_kingw, needed->y_kingw, x, y, des_x, des_y);

  * needed->player_turn = res.player_turn;
  needed->x_kingb = res.x_kingb;
  needed->y_kingb = res.y_kingb;
  needed->x_kingw = res.x_kingw;
  needed->y_kingw = res.y_kingw;

  if (res.continuee == 1) {
    // TURN FINISHED
    gtk_entry_set_text(needed->Ori_Coord, "");
    gtk_entry_set_text(needed->New_Coord, "");
    gtk_label_set_text(needed->Info, "New Turn");
    playerturn_print(needed->player_turn, needed->player1, needed->player2, needed->turn);
    return;
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

          if (*needed->player_turn == WHITETURN) {
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
          if((*needed->player_turn == BLACKTURN && piece_to_place(needed->x_kingb, needed->y_kingb, needed->constr.board) == 1 ) // is in check around
          || (*needed->player_turn == WHITETURN && piece_to_place(needed->x_kingw, needed->y_kingw, needed->constr.board) == 1))
            {
              printf("impossible \n");
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
            //  gtk_label_set_text(needed->Info, "New Turn \n Please select the chess piece you want to move (ex: A3)");
            //  playerturn_print(needed->player_turn, needed->player1, needed->player2, needed->turn);
            //  return;
          }

          // Check for checkmates _________________________________________
          struct checking res = check4checkmates_2(needed->player_turn, needed->constr.board, needed->white_kingstatus,
             needed->black_kingstatus, needed->x_kingb, needed->y_kingb, needed->x_kingw, needed->y_kingw,
             des_x, des_y,  needed->player1, needed->player2, needed->Info);

          needed->white_kingstatus = res.white_kingstatus;
          needed->black_kingstatus = res.black_kingstatus;


          if (res.returned == 1)
          {
            printf("check mate\n");
            gtk_entry_set_text(needed->Ori_Coord, "");
            gtk_entry_set_text(needed->New_Coord, "");
            gtk_widget_show(needed->EndWindow);
            gtk_widget_hide(needed->Window);
          }

          // Update board
          update_board(needed->constr);
    } // end switch
    gtk_entry_set_text(needed->Ori_Coord, "");
    gtk_entry_set_text(needed->New_Coord, "");
    playerturn_print(needed->player_turn, needed->player1, needed->player2, needed->turn);
    
}


#endif
