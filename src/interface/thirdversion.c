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
#include "thirdversion.h"

#ifndef THIRDVERSION_C
#define THIRDVERSION_C


/*
 * @author Anna
 * @date 29/04/2021
 * @details Clicked for move
*/

void click4move_3(GtkButton *button, gpointer user_data)
{
  struct for_clicked *needed = user_data;

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
    needed->black_kingstatus, needed->white_rock, needed->black_rock,needed->x_kingb,
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
    gtk_entry_set_text(needed->Ori_Coord, "");
    gtk_entry_set_text(needed->New_Coord, "");
    char *infoo = malloc(700 * sizeof(char));
    strcpy(infoo, needed->player1->name);
    strcat(infoo, " ,it's your turn to play (Black)");
    gtk_label_set_text( needed->turn, infoo);
    free(infoo);
    return;
  }
  //Other chess piece movements
  //printf("from x=%c y=%i to x=%c and y=%i\n", (char)(x +65), y + 1, (char)(des_x + 65), des_y+1 );
  //printf("for valid move %i %i %i %i\n", x-1, y-1,des_x-1, des_y-1);
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

         needed->nbWhite = removedpiece(x-1 , y-1, des_x-1, des_y-1, needed->constr.board, needed->currentB, needed->currentW, needed->nbBlack, needed->nbWhite);

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
              gtk_label_set_text(needed->Info, "New Turn \n Please select the chess piece you want to move (ex: A3)");

              return;
          }

          // Check for checkmates _________________________________________
          struct checking res = check4checkmates_2(needed->player_turn, needed->constr.board, needed->white_kingstatus,
             needed->black_kingstatus, needed->x_kingb, needed->y_kingb, needed->x_kingw, needed->y_kingw,
             des_x, des_y,  needed->player1, needed->player2, needed->Info, needed->Window, needed->EndWindow);

          needed->white_kingstatus = res.white_kingstatus;
          needed->black_kingstatus = res.black_kingstatus;


          if (res.returned == 1)
          {
            gtk_entry_set_text(needed->Ori_Coord, "");
            gtk_entry_set_text(needed->New_Coord, "");
            //gtk_window_unfullscreen(GTK_WINDOW(needed->Window));
            gtk_widget_show(needed->EndWindow);
            gtk_widget_hide(needed->Window);
            return;
          }

          // Update board
          update_board(needed->constr);
    } // end switch
    gtk_entry_set_text(needed->Ori_Coord, "");
    gtk_entry_set_text(needed->New_Coord, "");

    sleep(2);

    // AI turn
    struct finalmove * move = get_right_move_ia(needed->constr.board,needed->currentW,needed->currentB, WHITETURN, 2, needed->nbWhite, needed->nbBlack);
    x = move->x;
    y = move->y;
    des_y = move->ydes;
    des_x = move->xdes;

    //Rock
    struct res_rock res2 = rock_sub(* needed->player_turn, needed->constr.board, needed->white_kingstatus,
      needed->black_kingstatus, needed->white_rock, needed->black_rock,needed->x_kingb,
      needed->y_kingb, needed->x_kingw, needed->y_kingw, x, y, des_x, des_y);

    * needed->player_turn = res2.player_turn;
    needed->x_kingb = res2.x_kingb;
    needed->y_kingb = res2.y_kingb;
    needed->x_kingw = res2.x_kingw;
    needed->y_kingw = res2.y_kingw;

    if (res2.continuee == 1) {
      // TURN FINISHED
      gtk_entry_set_text(needed->Ori_Coord, "");
      gtk_entry_set_text(needed->New_Coord, "");
      gtk_label_set_text(needed->Info, "New Turn");
      char *infoo = malloc(700 * sizeof(char));
      strcpy(infoo, needed->player1->name);
      strcat(infoo, " ,it's your turn to play (Black)");
      gtk_label_set_text( needed->turn, infoo);
      free(infoo);
      return;
    }

    needed->nbBlack = removedpiece(x , y, des_x, des_y, needed->constr.board, needed->currentW, needed->currentB, needed->nbWhite, needed->nbBlack);
    needed->constr.board = pieceMove(x, y, des_x, des_y, needed->constr.board); // Move piece

    if(needed->constr.board[(y-1)*8+(x-1)].color == WHITE && needed->constr.board[(y-1)*8+(x-1)].type == KING) //change position of the king to help check/pat/checkmat
      {
        needed->x_kingw = des_x - 1;
        needed->y_kingw = des_y - 1;
        needed->white_rock = CANT_ROCK;
      }


            // Check for checkmates _________________________________________
            struct checking res3 = check4checkmates_2(needed->player_turn, needed->constr.board, needed->white_kingstatus,
               needed->black_kingstatus, needed->x_kingb, needed->y_kingb, needed->x_kingw, needed->y_kingw,
               des_x, des_y,  needed->player1, needed->player2, needed->Info, needed->Window, needed->EndWindow);

            needed->white_kingstatus = res3.white_kingstatus;
            needed->black_kingstatus = res3.black_kingstatus;


            if (res3.returned == 1)
            {
              gtk_entry_set_text(needed->Ori_Coord, "");
              gtk_entry_set_text(needed->New_Coord, "");
              //gtk_window_unfullscreen(GTK_WINDOW(needed->Window));
              gtk_widget_show(needed->EndWindow);
              gtk_widget_hide(needed->Window);
              return;
            }

      // Update board
      update_board(needed->constr);

      gtk_entry_set_text(needed->Ori_Coord, "");
      gtk_entry_set_text(needed->New_Coord, "");
      char *infoo = malloc(700 * sizeof(char));
      strcpy(infoo, needed->player1->name);
      strcat(infoo, " ,it's your turn to play (Black)");
      gtk_label_set_text( needed->turn, infoo);
      free(infoo);
}


#endif
