/**
 * @author Marine Marie Anna Antoine
 * @date Start 15/04/2021
 * @details For finds move list of possible for IA
 */

//Safety Guard
#ifndef AI_COMMON_MOVES_CHESS_MOVE_H
#define AI_COMMON_MOVES_CHESS_MOVE_H

#include "../../../common/c/rules/pieces.c"

/**
 * @author Antoine
 * @date 15/04/2021
 * @details Alias of Moves
 */
typedef struct Moves Moves;


/**
 * @author Marine Marie Anna Antoine
 * @date Start 15/04/2021
 * @details For represent a move
 *
 * @param x_start x of start of move
 * @param y_start y of start of move
 * @param x_end x of end of move
 * @param y_end y of end of move
 */
struct Moves
{
    unsigned char x_start;
    unsigned char y_start;

    unsigned char x_end;
    unsigned char y_end;
};

/**
 * @author NA
 * @date Start 15/04/2021
 * @details Main Function who is call for find every move possible
 *
 * @param board The board of the game.
 * @param color Color of team who is currently turn.
 * @param count Counter of moves find.
 *
 * @return Moves array of size of param counter.
 */
Moves* find_chess_moves(Piece* board, Color color, unsigned char* count);

/**
 * @author Antoine & Marie
 * @date Start 15/04/2021
 * @details Function who is call for find every move of pawn
 *
 * @param board The board of the game.
 * @param x X pos of pawn.
 * @param y Y pos of pawn.
 * @param count Counter of moves find.
 *
 * @return Moves array of size of param counter.
 */
Moves* find_chess_moves_pawn(Piece* board, unsigned char x, unsigned char y,
                             unsigned char* count);

/**
 * @author Antoine & Marie
 * @date Start 15/04/2021
 * @details Function who is call for find every move of knight
 *
 * @param board The board of the game.
 * @param x X pos of knight.
 * @param y Y pos of knight.
 * @param count Counter of moves find.
 *
 * @return Moves array of size of param counter.
 */
Moves* find_chess_moves_knight(Piece* board, unsigned char x, unsigned char y,
                             unsigned char* count);

/**
 * @author Antoine & Marie
 * @date Start 15/04/2021
 * @details Function who is call for find every move of king, include rock.
 *
 * @param board The board of the game.
 * @param x X pos of pawn.
 * @param y Y pos of pawn.
 * @param count Counter of moves find.
 *
 * @return Moves array of size of param counter.
 */
Moves* find_chess_moves_king(Piece* board, unsigned char x, unsigned char y, unsigned char* count);


/**
 * @author Marine
 * @date Start 15/04/2021
 * @details Function called to find every move possible for the bishop
 *
 * @param board The board of the game.
 * @param x X pos of pawn.
 * @param y Y pos of pawn.
 * @param count Counter of moves find.
 *
 * @return Moves array of size of param counter.
 */
Moves* find_chess_moves_bishop(Piece* board, unsigned char x, unsigned char y,
                               unsigned char* count);

/**
 * @author Marine
 * @date Start 15/04/2021
 * @details Function called to find every move possible for the rook
 *
 * @param board The board of the game.
 * @param x X pos of pawn.
 * @param y Y pos of pawn.
 * @param count Counter of moves find.
 *
 * @return Moves array of size of param counter.
 */
Moves* find_chess_moves_rook(Piece* board, unsigned char x, unsigned char y,
                             unsigned char* count);

/**
 * @author Marine
 * @date Start 15/04/2021
 * @details Function called to find every move possible for the queen
 *
 * @param board The board of the game.
 * @param x X pos of pawn.
 * @param y Y pos of pawn.
 * @param count Counter of moves find.
 *
 * @return Moves array of size of param counter.
 */
Moves* find_chess_moves_queen(Piece* board, unsigned char x, unsigned char y,
                              unsigned char* count);

//End safety Guard
#endif
