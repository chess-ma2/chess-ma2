/**
 * @author Marie
 * @date Start 15/04/2021
 * @details optimate functions to create list of childs
 */


#ifndef CREATE_CHILDS_H
#define CREATE_CHILDS_H


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../../../common/c/rules/pieces.c"


/**
 * @author Marie
 * @date Start 16/04/2021
 * @details struct for the moves 
 */

struct coordonates_moves
{
  int x;
  int y;
  int x_des;
  int y_des;
  struct Piece *board; 
};


/**
 * @author Marie
 * @date Start 16/04/2021
 * @details coordonates of the king  
 */

struct coordonates_king
{
  int x_king;
  int y_king;
};


/**
 * @author Marie
 * @date Start 16/04/2021
 * @details struct for the list of move and index 
 */

struct tabm
{
  int index;
  struct coordonates_moves *list_of_moves;
};


/**
 * @author Marie
 * @date Start 16/04/2021
 * @details find the king's position
 */

struct coordonates_king *king_positionm(Piece *board, int color_team, struct coordonates_king *kingplace);

/**
 * @author Marie
 * @date Start 16/04/2021
 * @details test if the king is in check if a move is possible
 */

int isInCheck(Piece *board, int color_team, int x, int y, int x_des, int y_des);

/**
 * @author Marie
 * @date Start 16/04/2021
 * @details find all the possible moves
 */

struct tabm *possible_moves(Piece *board, int color_team);


/**
 * @author Marie
 * @date Start 16/04/2021
 * @details find all the possible moves
 */

struct tabm *possible_moves(Piece *board, int color_team);

/**
 * @author Marie
 * @date Start 16/04/2021
 * @details find all the possible moves for a pawn
 */

struct tabm *possible_moves_pawn(Piece *board, int color_team,int x, int y, struct tabm *tab_struct);

/**
 * @author Marie
 * @date Start 16/04/2021
 * @details find all the possible moves for a queen
 */

struct tabm *possible_moves_queen(Piece *board, int color_team,int x, int y ,struct tabm *tab_struct);

/**
 * @author Marie
 * @date Start 16/04/2021
 * @details find all the possible moves for a king
 */

struct tabm *possible_moves_king(Piece *board, int color_team,int x, int y, struct tabm *tab_struct);

/**
 * @author Marie
 * @date Start 16/04/2021
 * @details find all the possible moves for a knight
 */

struct tabm *possible_moves_knight(Piece *board, int color_team,int x, int y, struct tabm *tab_struct);

/**
 * @author Marie
 * @date Start 16/04/2021
 * @details find all the possible moves for a rook
 */

struct tabm *possible_moves_rook(Piece *board, int color_team,int x, int y, struct tabm *tab_struct);

/**
 * @author Marie
 * @date Start 16/04/2021
 * @details find all the possible moves for a bishop
 */

struct tabm *possible_moves_bishop(Piece *board, int color_team,int x, int y, struct tabm *tab_struct);


#endif
