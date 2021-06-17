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
#include "thirdV_init.h"

#ifndef THIRDV_INIT_C
#define THIRDV_INIT_C

/*
 * @author Anna
 * @date 16/06/2021
 * @details IA move for MiniMax
*/

void IA_move(struct for_clicked *needed)
{
  // Get move from IA
  struct finalmove * move = get_right_move_ia(needed->constr.board,needed->currentW,needed->currentB, WHITETURN, 2, needed->nbWhite, needed->nbBlack);
  int x = move->x;
  int y = move->y;
  int des_y = move->ydes;
  int des_x = move->xdes;

  // Move Piece and update lists
  needed->nbBlack = removedpiece(x , y, des_x, des_y, needed->constr.board, needed->currentW, needed->currentB, needed->nbWhite, needed->nbBlack);
  needed->constr.board = pieceMove(x, y, des_x, des_y, needed->constr.board); // Move piece

  // Update board
  update_board(needed->constr);
  gtk_entry_set_text(needed->Ori_Coord, "");
  gtk_entry_set_text(needed->New_Coord, "");

  // Black player's turn to play
  char *infoo = malloc(700 * sizeof(char));
  strcpy(infoo, needed->player1->name);
  strcat(infoo, " ,it's your turn to play (Black)");
  gtk_label_set_text( needed->turn, infoo);
  free(infoo);

  *needed->player_turn = BLACKTURN;
}

/*
 * @author Anna
 * @date 16/06/2021
 * @details Main Game function (from version1 originaly)
*/

void init_gtk3(struct Player *player1, struct Player *player2, struct construction constr, GtkLabel *Rules, GtkLabel *Info, GtkLabel *turn, struct for_clicked *needed, GtkWidget *EndWindow)
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

  player1->team_color = 1; // Player 1 is black
  player2->team_color = 0; // Player 2 is white

  player1->name = getNAME(player1->email);
  player2->name = getNAME(player2->email);
  //____________________________________________________________________________

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
  needed->constr = constr;

  // IA first move
  IA_move(needed);

  return;
}

#endif
