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
        printf("%c%i\n",m[a].x_pos,m[a].y_pos);
    }
    //free(m);
}

int main()
{
    struct Piece* board = init_board();
    struct currentpiece *current_List = create_whiteList();
    struct tree * Tree = create_tree(board, WHITETURN, current_List, 16, 2);
    pretty_print(Tree);
    free_tree(Tree);
    //free(board);

    /*int x='A';
    int y=7;
    int color = 1;//white

    printmoves(find_chess_moves_pawn( board, x, y, color));
    printf("printpawnok\n");
    printmoves(find_chess_moves_knight(board, x, y, color));
    printf("printkinghtok\n");
    printmoves(find_chess_moves_king( board, x, y, color));
    printf("prtinfkingok\n");
    printmoves(find_chess_moves_bishop( board, x, y, color));
    printf("prtinfBISHOPok\n");
    printmoves(find_chess_moves_rook( board, x, y, color));
    printf("prtinfROOKok\n");
    printmoves(find_chess_moves_queen( board, x, y, color));
    printf("prtinfQUEENok\n");*/

    free(board);


  return 0;
}

#endif
