/**
 * @author Marie Maturana 
 * @date Start 15/05/2021
 * @details File .h containing all the functions relating to the check, pat and checkmat for create the mcts
 */

#ifndef CHECK_AND_PAT_FOR_AI_H
#define CHECK_AND_PAT_FOR_AI_H

/**
 * @author Marie Maturana 
 * @date Start 15/05/2021
 * @details see if an other movement can be make for stop the checkmat
 * @return  1 if an othen movement can be make / 0 else
 */

int checkmat_secondcondition_AI(int x_king, int y_king,int color, struct Piece *board) ;

/**
 * @author Marie Maturana 
 * @date Star t15/05/2021
 * @details create new board to see if the king in in check at this place
 * @return  1 if king in check / 0 else
 */

int checkking_and_aroud_AI(int place_king_x, int place_king_y, int x_place, int y_place,struct Piece *board);

/**
 * @author Marie Maturana 
 * @date Start 27/03/2021
 * @details check if other movement can be make in the king is in pat
 * @return  1 other moves possible / 0 else
 */

int othermove_pat1_AI(struct Piece *board);

int othermove_pat2_AI(int x_place, int y_place,struct Piece *board);

/**
 * @author Marie Maturana 
 * @date Start 15/05/2021
 * @details see if the king is in check at this place
 * @return 1 if king in check / 0 else
 */

int kingcheck_place_AI(int x_king, int y_king, int x_piece, int y_piece, struct Piece *board);

/**
 * @author Marie Maturana 
 * @date Start 15/05/2021
 * @details test for all the pieces if the king is in check at this place
 * @return 1 if king in check around himself / 0 else
 */

int piece_to_place_AI(int x_place, int y_place, struct Piece *board);

/**
 * @author Marie Maturana 
 * @date Start 15/05/2021
 * @details test if the king is in check all around himself and at his place
 * @return 1 if king in check around himself / 0 else
 */

int checkmat_firstcondition_AI(int x_king, int y_king, struct Piece *board);

/**
 * @author Marie Maturana 
 * @date Start 15/05/2021
 * @details test if the king is in check and for that test the 2 conditions
 * @return 1 if king in checkmate / 0 else
 */

int check_mat_AI(int x_king, int y_king,int color, struct Piece *board);

/**
 * @author Marie Maturana 
 * @date Start 15/05/2021
 * @details test if the king is in pat => check all around him and not other moves
 * @return 1 if king in pat / 0 else
 */

int pat_AI(int x_king, int y_king, struct Piece *board);



#endif
