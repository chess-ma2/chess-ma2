#ifndef PLATE_H
#define PLATE_H
#include "pieces.h"


/**
 * @author Antoine and Marie
 * @date Start 04/03/2021
 * @details File .h containing all the functions relating to the chess plate and init this last.
 */



/**
 * @author Marie
 * @date Start 04/03/2021
 * @details infos to know the turn of the player
 */
enum turn{
	    BLACKTURN = 0,
	    WHITETURN = 1,
};


/**
 * @author Marie
 * @date Start 04/03/2021
 * @details status of the king during the game
 * @details can be in check or checkmate or nothing
 */
enum king_status{
		 NOTHING= 0,
		 CHECKMATE,
		 CHECK,
		 PAT, 
};



/**
 * @author Marie
 * @date Start 04/03/2021
 * @details if you can rock because you can do that 1 time
 */
enum rock{
	    CANT_ROCK = 0,
	    CAN_ROCK = 1,
};

/**
 * @author Antoine and Marie
 * @date Start 04/03/2021
 * @details Prototype of function who allow to generate a new grid.
 * @return board of size 64 who represent each Piece in 8*8
 */
struct Piece *init_board (); 

#endif
