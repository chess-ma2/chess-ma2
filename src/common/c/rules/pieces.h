/**
 * @author Marie and Antoine
 * @date Start 04/03/2021
 * @details File .h containing all the functions and the structures relating to the chess pieces and their movements.
 */

#ifndef PIECES_H
#define PIECES_H


/**
 * @author Marie and Antoine
 * @date Start 04/03/2021
 * @details Possibility of the type of a Piece
 */
enum Type  
{
    NONE = 0,
    PAWN,
    ROOK,
    BISHOP,
    KNIGHT,
    QUEEN,
    KING,
};


/**
 * @author Antoine and Marie 
 * @date 15/04/2021
 * @details Alias of Color
 */
typedef enum Color Color;


/**
 * @author Antoine and Marie 
 * @date 15/04/2021
 * @details differents colors
 */

enum Color 
{  
	    BLACK = 0,
	    WHITE = 1,
};

/**
 * @author Antoine and Marie
 * @date 15/04/2021
 * @details Alias of Piece
 */
typedef struct Piece Piece;

/**
 * @author Antoine and Marie
 * @date Start 05/03/2021
 * @details Structure who represent a Piece.
 * @param type represent with enum Type the type of Piece.
 * @param color represent the color of the piece,
 *      please ignore this last arg if type is None.
 */
struct Piece
{
  enum Type type;
  enum Color color;
};




/**
 * @author Marie
 * @date Start 04/03/2021
 * @details Make the movement of the piece
 * @return the new board after the move
 */

struct Piece *pieceMove(int x, int y, int des_x, int des_y, struct Piece *board);


/**
 * @author Marie
 * @date Start 04/03/2021
 * @details Make the movement of the piece when it is the Rock movement 
 * @return the new board after the move after the rock
 */

struct Piece *pieceMove_Rock(int x, int y, int des_x, int des_y, struct Piece *board);

/**
 * @author Marie
 * @date Start 04/03/2021
 * @details Valid if the movement of the piece is possible 
 * @return if the move is possible or not
 */

int isValidMove(int x, int y, int des_x, int des_y, struct Piece *board);

/**
 * @author Marie
 * @date Start 04/03/2021
 * @details Valid if the movement of the pawn is possible 
 * @return if the move of the pawn is possible or not
 */

int isValidMove_Pawn(int x, int y, int des_x, int des_y, int color_piece, struct Piece *board);

/**
 * @author Marie
 * @date Start 11/03/2021
 * @details Valid if the movement of the rook is possible 
 * @return if the move of the rook is possible or not
 */

int isValidMove_Rook(int x, int y, int des_x, int des_y, struct Piece *board);

/**
 * @author Marie
 * @date Start 11/03/2021
 * @details Valid if the movement of the bishop is possible 
 * @return if the move of the bishop is possible or not
 */

int isValidMove_Bishop(int x, int y, int des_x, int des_y, struct Piece *board);


/**
 * @author Marie
 * @date Start 08/03/2021
 * @details Valid if the movement of the knight is possible 
 * @return if the move of the knight is possible or not
 */


int isValidMove_Knight(int x, int y, int des_x, int des_y);

/**
 * @author Marie
 * @date Start 11/03/2021
 * @details Valid if the movement of the queen is possible 
 * @return if the move of the queen is possible or not
 */

int isValidMove_Queen(int x, int y, int des_x, int des_y, struct Piece *board);

/**
 * @author Marie
 * @date Start 07/03/2021
 * @details Valid if the movement of the king is possible 
 * @return if the move of the king is possible or not
 */

int isValidMove_King(int x, int y, int des_x, int des_y);

/**
 * @author Marie
 * @date Start 12/03/2021
 * @details Valid if the movement of the rock is possible 
 * @return if the move of the rock is possible or not
 */

int isValidMove_Rock(int x, int y, int des_x, int des_y, int color_piece, struct Piece *board);


#endif
