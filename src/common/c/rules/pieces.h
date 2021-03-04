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


#endif
