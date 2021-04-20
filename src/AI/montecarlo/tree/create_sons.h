/**
 * @author Marie
 * @date Start 15/04/2021
 * @details optimate functions to create son list
 */


#ifndef CREATE_SONS_H
#define CREATE_SONS_H


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../../../common/c/rules/pieces.h"
#include "../../../common/c/rules/check_and_plate.h"

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
};


/**
 * @author Marie
 * @date Start 16/04/2021
 * @details struct for the list of move and index 
 */

struct tab
{
  int index;
  coordonates_moves list_of_move[];
};


/**
 * @author Marie
 * @date Start 16/04/2021
 * @details find all the possible moves
 */

struct coordonates_moves *possible_moves(Piece *board, int color_team);

/**
 * @author Marie
 * @date Start 16/04/2021
 * @details find all the possible moves for a pawn
 */

struct tab possible_moves_pawn(Piece *board, int color_team, struct tab tab_struct);

/**
 * @author Marie
 * @date Start 16/04/2021
 * @details find all the possible moves for a queen
 */

struct tab possible_moves_queen(Piece *board, int color_team, struct tab tab_struct);

/**
 * @author Marie
 * @date Start 16/04/2021
 * @details find all the possible moves for a king
 */

struct tab possible_moves_king(Piece *board, int color_team, struct tab tab_struct);

/**
 * @author Marie
 * @date Start 16/04/2021
 * @details find all the possible moves for a knight
 */

struct tab possible_moves_knight(Piece *board, int color_team, struct tab tab_struct);

/**
 * @author Marie
 * @date Start 16/04/2021
 * @details find all the possible moves for a rook
 */

struct tab possible_moves_rook(Piece *board, int color_team, struct tab tab_struct);

/**
 * @author Marie
 * @date Start 16/04/2021
 * @details find all the possible moves for a bishop
 */

struct tab possible_moves_bishop(Piece *board, int color_team, struct tab tab_struct);


#endif
