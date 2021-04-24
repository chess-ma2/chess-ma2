#include "minimax.c"
#include "MINImove.c"
#include "../../common/c/rules/plate.c"


#ifndef TESTING_C
#define TESTING_C


void printmoves (struct tab* moves)
{
    struct Moves * m=moves->moves;
    printf("%i\n",moves->numberofmoves);
    for (int a=0; a<moves->numberofmoves; a++)
    {
        printf("%i%i\n",m[a].x_pos,m[a].y_pos);
    }
    //free(m);
}

int main()
{
    struct Piece* board = init_board();
    struct currentpiece *current_List = create_whiteList();
    struct tree * Tree = create_tree(board, WHITETURN, current_List, 16, 2);
    int color = 1;//white
    print_tree(Tree);
    free_tree(Tree);
    //free(board);

    int x='A';
    int y=2;

    //juste pour tester compilation
    printmoves(find_chess_moves_pawn( board, x, y, color));
    //printf("printTREEok\n");
    printmoves(find_chess_moves_knight(board, x, y, color));
    //printf("printTREEok\n");
    printmoves(find_chess_moves_king( board, x, y, color));

    printmoves(find_chess_moves_bishop( board, x, y, color));

    printmoves(find_chess_moves_rook( board, x, y, color));

    printmoves(find_chess_moves_queen( board, x, y, color));



  return 0;
}

#endif
