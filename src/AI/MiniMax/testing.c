#include "minimax.c"
//#include "MINImove.c"
#include "../../common/c/rules/plate.c"


#ifndef TESTING_C
#define TESTING_C


int main()
{
    struct Piece* board = init_board();
    struct currentpiece *current_List = create_whiteList();
    struct tree * Tree = create_tree(board, WHITETURN, current_List, 16, 2);
    print_tree(Tree);
    free_tree(Tree);
    free(board);

    /*int x='A';
    int y=1;

    //juste pour tester compilation
    find_chess_moves_pawn( board, x, y, color);

    find_chess_moves_knight(board, x, y, color);

    find_chess_moves_king( board, x, y, color);

    find_chess_moves_bishop( board, x, y, color);

    find_chess_moves_rook( board, x, y, color);

    find_chess_moves_queen( board, x, y, color);*/



  return 0;
}

#endif
