#ifndef PIECES_H
#define PIECES_H


/*

File .h containing all the functions
 and structures relating to the chess pieces and their movements.
By Marie Maturana and Antoine
Start the 2021-03-04

*/



//Possibility of the type of a Piece
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


//Possibility of the colour of the Piece
enum Color 
{  
	    BLACK = 0,
	    WHITE = 1,
};


/**
 * @author Antoine
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



struct Piece *pieceMove(int x, int y, int des_x, int des_y, struct Piece *board);

struct Piece *pieceMove_Rock(int x, int y, int des_x, int des_y, struct Piece *board);

int isValidMove(int x, int y, int des_x, int des_y, struct Piece *board);

int isValidMove_Pawn(int x, int y, int des_x, int des_y, int color_piece, struct Piece *board);

int isValidMove_Rook(int x, int y, int des_x, int des_y, struct Piece *board);

int isValidMove_Bishop(int x, int y, int des_x, int des_y, struct Piece *board);

int isValidMove_Knight(int x, int y, int des_x, int des_y);

int isValidMove_Queen(int x, int y, int des_x, int des_y, struct Piece *board);

int isValidMove_King(int x, int y, int des_x, int des_y);

int isValidMove_Rock(int x, int y, int des_x, int des_y, int color_piece, struct Piece *board);


#endif
