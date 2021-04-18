/**
 * @author Marine Anna
 * @date Start 15/04/2021
 * @details For finds move list of possible for IA
 */

//Safety Guard
#ifndef MINIMOVE_H
#define MINIMOVE_H

#include "../../common/c/rules/pieces.c"
#include "../../common/c/rules/check_and_pat.c"

/**
 * @author Marine
 * @date Start 16/04/2021
 */
struct Moves
{
    unsigned char x_pos;
    unsigned char y_pos;
};

/**
 * @author Marine
 * @date Start 16/04/2021
 * @details Function that define if coordinates are in the bounds 1 if yes
 *
 * @param x X pos of pawn.
 * @param y Y pos of pawn.
 *
 * @return 1 if in the bounds, 0 if out of bounds
 */
int out_of_bounds( intx, int y);

/**
 * @author Marine
 * @date Start 16/04/2021
 * @details says if the destination place is possible
 *
 * @param x X pos of pawn.
 * @param y Y pos of pawn.
 * @param color color of the player
 *
 * @return 1 if possible, 0 otherwise
 */
int is_obstacle(int x, int y, Piece* board,int color);

/**
 * @author Marine
 * @date Start 18/04/2021
 * @details return if the move is causing a danger for king
 *
 * @param xinit X pos of pawn.
 * @param yinit Y pos of pawn.
 * @param xtest X possible pos of pawn
 * @param ytest Y possible of pawn
 * @param board the board
 *
 * @return 1 if possible, 0 otherwise
 */
int testCHECK(int xinit, int yinit, int xtest, int ytest, Piece* board);


/**
 * @author Marine
 * @date Start 15/04/2021
 * @details Function that is called tofind every move for pawn
 *
 * @param board The board of the game.
 * @param x X pos of pawn.
 * @param y Y pos of pawn.
 * @param color 0 if black, 1 if white.
 *
 * @return array of size of param counter, with destination coordinates
 */
struct Moves* find_chess_moves_pawn(Piece* board, int x, int y, int color);

/**
 * @author Marine
 * @date Start 15/04/2021
 * @details Function that is called to find every move for knight
 *
 * @param board The board of the game.
 * @param x X pos of knight.
 * @param y Y pos of knight.
 * @param color 0 if black, 1 if white.
 *
 * @return array of size of param counter, with destination coordinates
 */
struct Moves* find_chess_moves_knight(Piece* board, int x, int y, int color);

/**
 * @author Antoine & Marie
 * @date Start 15/04/2021
 * @details Function called to find every move of king, including rock.
 *
 * @param board The board of the game.
 * @param x X pos of pawn.
 * @param y Y pos of pawn.
 * @param color 0 if black, 1 if white.
 *
 * @return array of size of param counter, with destination coordinates
 */
struct Moves* find_chess_moves_king(Piece* board, int x, int y, int color);


/**
 * @author Marine
 * @date Start 15/04/2021
 * @details Function called to find every move possible for the bishop
 *
 * @param board The board of the game.
 * @param x X pos of pawn.
 * @param y Y pos of pawn.
 * @param color 0 if black, 1 if white.
 *
 * @return array of size of param counter, with destination coordinates
 */
struct Moves* find_chess_moves_bishop(Piece* board, int x, int y, int color);

/**
 * @author Marine
 * @date Start 15/04/2021
 * @details Function called to find every move possible for the rook
 *
 * @param board The board of the game.
 * @param x X pos of pawn.
 * @param y Y pos of pawn.
 * @param color 0 if black, 1 if white.
 *
 * @return array of size of param counter, with destination coordinates
 */
struct Moves* find_chess_moves_rook(Piece* board, int x, int y, int color);

/**
 * @author Marine
 * @date Start 15/04/2021
 * @details Function called to find every move possible for the queen
 *
 * @param board The board of the game.
 * @param x X pos of pawn.
 * @param y Y pos of pawn.
 * @param color 0 if black, 1 if white.
 *
 * @return array of size of param counter, with destination coordinates
 */
struct Moves* find_chess_moves_queen(Piece* board, int x, int y, int color);

//End safety Guard
#endif
