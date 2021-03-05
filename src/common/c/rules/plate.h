#ifndef PLATE_H
#define PLATE_H
#include "pieces.h"


/*

File .h containing all the functions relating to the chess plate and structure about the game.
By Marie Maturana & Antoine
Start the 2021-03-04

*/



//turn of the player
enum turn{
	    BLACKTURN = 0,
	    WHITETURN = 1,
};


/**
 * @author Antoine
 * @date Start 05/03/2021
 * @details Prototype of function who allow to generate a new grid.
 * @return board of size 64 who represent each Piece in 8*8
 */
struct Piece *init_board (); 

#endif
