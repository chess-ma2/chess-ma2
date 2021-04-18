#include "minimax.c"
#include "MINImove.c"
#include "../../common/c/rules/plate.c"


#ifndef TESTING_C
#define TESTING_C


int main()
{
    struct Piece* board = init_board();
    int x='A';
    int y=1;

    //juste pour tester compilation
    find_chess_moves_pawn( board, x, y, color);

    find_chess_moves_knight(board, x, y, color);

    find_chess_moves_king( board, x, y, color);

    find_chess_moves_bishop( board, x, y, color);

    find_chess_moves_rook( board, x, y, color);

    find_chess_moves_queen( board, x, y, color);

  return 0;
}

#endif
