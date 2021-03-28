#ifndef CHECK_AND_PAT_H
#define CHECK_AND_PAT_H


/*

File .h containing all the functions  and structures relating to the check and pat 
The main piece is the king
By Marie Maturana
Start the 2021-03-23

*/

int checkmat_secondcondition(int x_king, int y_king, int can_rock, struct Piece *board) ;

int othermove_pat(struct Piece *board);

int kingcheck_place(int x_king, int y_king, int x_piece, int y_piece, struct Piece *board);

int piece_to_place(int x_place, int y_place, struct Piece *board);

int checkmat_firstcondition(int x_king, int y_king, struct Piece *board); 

int check_mat(int x_king, int y_king, int can_rock, struct Piece *board);

int pat(int x_king, int y_king, struct Piece *board);



#endif
