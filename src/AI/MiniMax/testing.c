#include "minimax.h"
#include "MINImove.c"
#include "../../common/c/rules/plate.c"

int main()
{
    struct Piece* board = init_board();
    int x='A';
    int y=1;
    
    find_chess_moves_pawn( board, x, y, color);

    find_chess_moves_knight(board, x, y, color);

    find_chess_moves_king( board, x, y, color);

    find_chess_moves_bishop( board, x, y, color);

    find_chess_moves_rook( board, x, y, color);

    find_chess_moves_queen( board, x, y, color);

  return 0;
}
