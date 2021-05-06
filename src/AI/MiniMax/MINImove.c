/**
 * @author Marine
 * @date Start 15/04/2021
 * @details For finds move list of possible for IA
 */


//Safety Guard
#ifndef MINIMOVE_C
#define MINIMOVE_C

#include "MINImove.h"
#include "minimax.h"


int out_of_bounds( int x,  int y)
{
    if (x< 0 || x>7 || y<0 || y>7)
    {
        return 0;
    }
    return 1;
}

int is_obstacle(int x, int y, Piece* board,int color)
{
    struct Piece piece = board[x+y*8];
    if (piece.type!=NONE && piece.color!=color)
    {
        return 1;
    }
    return 0;
}

int is_free(int x, int y, Piece * board)
{
    return board[y*8+x].type==NONE;
}

// ERROR SOLVING: TYPES
struct Moves * king_position( Piece * board,int color)
{
    struct Moves * pos= malloc(sizeof(struct Moves));
    int x=0;
    int y=0;
    pos->x_pos=x;
    pos->y_pos=y;
    for (x=0;x<8;x++)
    {
        for(y=0;y<8;y++)
        {
            if (board[x+8*y].type == KING && board[x+8*y].color==color)
            {
                pos->x_pos=x;
                pos->y_pos=y;
                return pos;
            }
        }
    }

    return pos;
}

int testCHECK(int xinit, int yinit, int xtest, int ytest, Piece* board,int color)
{
    //changes coordinates to make the test
    //display_board_special(board);
    char type= board[xtest+ytest*8].type;
    board[xtest+ytest*8].type=board[xinit+yinit*8].type;
    board[xtest+ytest*8].color=board[xinit+yinit*8].color;
    board[xinit+yinit*8].type=NONE;
    struct Moves * king = king_position(board,color);


    if (check_mat(king->x_pos, king->y_pos, color,board))
    {
        //resset the orignal values
        board[xinit+yinit*8].type=board[xtest+ytest*8].type;
        board[xtest+ytest*8].type=type;
        return 1;
    }
    //resset the orignal values
    board[xinit+yinit*8].type=board[xtest+ytest*8].type;
    board[xtest+ytest*8].type=type;
    free(king);
    return 0;
}

struct tab* find_chess_moves_pawn(Piece* board, int x, int y,int color)
{
    struct tab* table= malloc(sizeof(struct tab));
    int number=0;
    table->moves=malloc(sizeof(struct Moves));
    struct Moves * global_moves = table->moves;
    struct Moves* moves=malloc(sizeof(struct Moves));
    table->numberofmoves=0;
    //CHECK INTIAL PLACE +2
    if ((color==0 && y==1)|| (color==1 && y==6))
    {
        if (is_free(x,y+2-4*color,board) && out_of_bounds(x,y+2-4*color) )
        {
            if (!testCHECK(x, y, x, y+2-4*color,board,color))
            {
            moves->x_pos = x;
            moves->y_pos = y+2-4*color;
            global_moves[number] = *moves;
            number++;
            }
        }
    }
    //CHECK +1 FRONT MOVE
    if (is_free(x,y+1-2*color,board) && out_of_bounds(x,y+1-2*color))
    {
        if (!testCHECK(x, y, x, y+1-2*color,board,color))
        {
        moves->x_pos = x;
        moves->y_pos = y+1-2*color;
        global_moves[number] = *moves;
        number++;
        }
    }

    //CHECK EAT MOVE right diag
    if (out_of_bounds(x+1,y+1-2*color) && is_obstacle(x+1,y+1-2*color,board,color))
    {
        if (!testCHECK(x, y, x+1, y+1-2*color,board,color))
        {
        moves->x_pos = x+1;
        moves->y_pos = y+1-2*color;
        global_moves[number] = *moves;
        number++;
        }
    }

    //CHECK EAT MOVE left diag
    if (out_of_bounds(x-1,y+1-2*color) && !testCHECK(x, y, x-1, y+1-2*color, board,color))
    {
        if (!testCHECK(x, y, x-1, y+1-2*color, board,color))
        {
        moves->x_pos = x-1;
        moves->y_pos = y+1-2*color;
        global_moves[number] = *moves;
        number++;
        }
    }
    free(moves);
    table->numberofmoves=number;
    return table;
}

struct tab* find_chess_moves_knight(Piece* board,  int x,  int y,int color)
{
    //display_board_special(board);
    struct tab* table= malloc(sizeof(struct tab));
    int number=0;
    table->moves=malloc(sizeof(struct Moves));
    struct Moves * global_moves = table->moves;
    struct Moves * moves =malloc(sizeof(struct Moves));
    table->numberofmoves=0;

    //shape * dest
    //      *
    //      x

    if ((is_obstacle(x+1,y-2,board,color) ||  is_free(x+1,y-2,board)) && out_of_bounds(x+1,y-2) && !testCHECK(x, y, x+1, y-2, board,color))
    {
        moves->x_pos = x+1;
        moves->y_pos = y-2;
        global_moves[number] = *moves;
        number++;
    }

    //shape dest *
    //           *
    //           x

    if ((is_obstacle(x-1,y-2,board,color) ||  is_free(x-1,y-2,board)) && out_of_bounds(x-1,y-2) && !testCHECK(x, y, x-1, y-2, board,color))
    {
        moves->x_pos = x-1;
        moves->y_pos = y-2;
        global_moves[number] = *moves;
        number++;
    }


    //shape   dest  *  *
    //                 x
    if ((is_obstacle(x-2,y-1,board,color) || is_free(x-2,y-1,board)) && out_of_bounds(x-2,y-1) && !testCHECK(x, y, x-2, y-1, board,color))
    {

        moves->x_pos = x-2;
        moves->y_pos = y-1;
        global_moves[number] = *moves;
        number++;
    }


    //shape *  *  dest
    //      x
    if ((is_obstacle(x+2,y-1,board,color) ||  is_free(x+2,y-1,board)) && out_of_bounds(x+2,y-1) && !testCHECK(x, y, x+2, y-1, board,color))
    {
        moves->x_pos = x+2;
        moves->y_pos = y-1;
        global_moves[number] = *moves;
        number++;
    }


    //shape x
    //      *
    //      * dest
    if ((is_obstacle(x+1,y+2,board,color) ||  is_free(x+1,y+2,board)) && out_of_bounds(x+1,y+2) && !testCHECK(x, y, x+1, y+2,board,color))
    {
        moves->x_pos = x+1;
        moves->y_pos = y+2;
        global_moves[number] = *moves;
        number++;
    }


    //shape     x
    //          *
    //      dest
    if ((is_obstacle(x-1,y+2,board,color) ||  is_free(x-1,y+2,board)) && out_of_bounds(x-1,y+2) && !testCHECK(x, y, x-1, y+2, board,color))
    {
        moves->x_pos = x-1;
        moves->y_pos = y+2;
        global_moves[number] = *moves;
        number++;
    }


    //shape      x
    //           *  *   dest
    if (out_of_bounds(x+2,y-1) && !testCHECK(x, y, x+2, y+1, board,color))
    {
        if (is_obstacle(x+2,y+1,board,color) ||  is_free(x+2,y+1,board))
        {
        moves->x_pos = x+2;
        moves->y_pos = y+1;
        global_moves[number] = *moves;
        number++;
        }
    }


    //shape          x
    //        dest * *
    if ((is_obstacle(x-2,y+1,board,color)|| is_free(x-2,y+1,board)) && out_of_bounds(x-2,y+1) && !testCHECK(x, y, x-2, y+1, board,color))
    {
        moves->x_pos = x-2;
        moves->y_pos = y+1;
        global_moves[number] = *moves;
        number++;
    }

    free(moves);
    table->numberofmoves=number;
    return table;
}

struct tab* find_chess_moves_king(Piece* board, int x, int y,int color)
{
    struct tab* table= malloc(sizeof(struct tab));
    int number=0;
    table->moves=malloc(sizeof(struct Moves));
    struct Moves * global_moves = table->moves;
    struct Moves* moves= malloc(sizeof(struct Moves));
    //to do check 9 moves possible
    //^
    if ((is_obstacle(x,y-1,board,color) || is_free(x,y-1,board)) && out_of_bounds(x,y-1) && !testCHECK(x, y, x, y-1, board,color))
    {
        moves->x_pos = x;
        moves->y_pos = y-1;
        global_moves[number] = *moves;
        number++;
    }
    //v
    if ((is_obstacle(x,y+1,board,color) || is_free(x,y+1,board)) && out_of_bounds(x,y+1) && !testCHECK(x, y, x, y+1, board,color))
    {
        moves->x_pos = x;
        moves->y_pos = y+1;
        global_moves[number] = *moves;
        number++;
    }
    //>
    if ((is_obstacle(x+1,y,board,color) || is_free(x+1,y,board)) && out_of_bounds(x+1,y) && !testCHECK(x, y, x+1, y, board,color))
    {
        moves->x_pos = x+1;
        moves->y_pos = y;
        global_moves[number] = *moves;
        number++;
    }
    //<
    if ((is_obstacle(x-1,y,board,color) || is_free(x-1,y,board)) && out_of_bounds(x-1,y) && !testCHECK(x, y, x-1, y,board,color))
    {
        moves->x_pos = x-1;
        moves->y_pos = y;
        global_moves[number] = *moves;
        number++;
    }
    //^>
    if ((is_obstacle(x+1,y-1,board,color) || is_free(x+1,y-1,board)) && out_of_bounds(x+1,y-1) && !testCHECK(x, y, x+1, y-1,board,color))
    {
        moves->x_pos = x+1;
        moves->y_pos = y-1;
        global_moves[number] = *moves;
        number++;
    }
    //v>
    if ((is_obstacle(x+1,y+1,board,color) || is_free(x+1,y+1,board)) && out_of_bounds(x+1,y+1) && !testCHECK(x, y, x+1, y+1, board,color))
    {
        moves->x_pos = x+1;
        moves->y_pos = y+1;
        global_moves[number] = *moves;
        number++;
    }
    //^<
    if ((is_obstacle(x-1,y-1,board,color) || is_free(x-1,y-1,board)) && out_of_bounds(x-1,y-1) && !testCHECK(x, y, x-1, y-1,board,color))
    {
        moves->x_pos = x-1;
        moves->y_pos = y-1;
        global_moves[number] = *moves;
        number++;
    }

    //v<
    if ((is_obstacle(x-1,y+1,board,color) || is_free(x-1,y+1,board)) && out_of_bounds(x-1,y+1) && !testCHECK(x, y, x-1, y+1, board,color))
    {
        moves->x_pos = x-1;
        moves->y_pos = y+1;
        global_moves[number] = *moves;
        number++;
    }


    free(moves);
    table->numberofmoves=number;
    return table;
}


struct tab* find_chess_moves_rook(Piece* board, int x, int y,int color)
{

    struct tab* table= malloc(sizeof(struct tab));
    int number=0;
    table->moves=malloc(sizeof(struct Moves));
    struct Moves * global_moves = table->moves;
    struct Moves* moves= malloc(sizeof(struct Moves));;
    int xmv=1; //x movement
    int ymv=1; //y movement

    //>>>>>move
    while (is_free(x+xmv,y,board) && out_of_bounds(x+xmv,y))
    {
        if (!testCHECK(x, y, x+xmv, y, board,color))
        {
            moves->x_pos = x+xmv;
            moves->y_pos = y;
            global_moves[number] = *moves;
            number++;
        }
        xmv++;
    }
    if (is_obstacle(x+xmv,y,board,color) && !testCHECK(x, y, x+xmv, y, board,color) && out_of_bounds(x+xmv,y))
    {
        moves->x_pos = x+xmv;
        moves->y_pos = y;
        global_moves[number] = *moves;
    }
    //<<<<<move
    xmv=1;
    while (is_free(x-xmv,y,board) && out_of_bounds(x-xmv,y))
    {
        if (!testCHECK(x, y, x-xmv, y, board,color))
        {
        moves->x_pos = x-xmv;
        moves->y_pos = y;
        global_moves[number] = *moves;
        number++;
        }
        xmv++;
    }
    if (is_obstacle(x-xmv,y,board,color) && out_of_bounds(x-xmv,y) && !testCHECK(x, y, x-xmv, y, board,color))
    {
        moves->x_pos = x-xmv;
        moves->y_pos = y;
        global_moves[number] = *moves;
    }
    //^^^^^move
    while (is_free(x,y+ymv,board) && out_of_bounds(x,y+ymv))
    {
        if (!testCHECK(x, y, x, y+ymv, board,color))
        {
        moves->x_pos = x;
        moves->y_pos = y+ymv;
        global_moves[number] = *moves;
        number++;
        }
        ymv++;
    }

    if (is_obstacle(x,y+ymv,board,color) && !testCHECK(x, y, x, y+ymv, board,color) && out_of_bounds(x,y+ymv))
    {
        moves->x_pos = x;
        moves->y_pos = y+ymv;
        global_moves[number] = *moves;
    }
    //vvvvvmove
    ymv=1;
    while (is_free(x,y-ymv,board) && out_of_bounds(x,y-ymv))
    {
        if (!testCHECK(x, y, x, y-ymv, board,color))
        {
        moves->x_pos = x;
        moves->y_pos = y-ymv;
        global_moves[number] = *moves;
        number++;
        }
        ymv++;
    }
    if (is_obstacle(x,y-ymv,board,color) && out_of_bounds(x,y-ymv) && !testCHECK(x, y, x, y-ymv, board,color))
    {
        moves->x_pos = x;
        moves->y_pos = y-ymv;
        global_moves[number] = *moves;
    }
    free(moves);
    table->numberofmoves=number;
    return table;
}


struct tab* find_chess_moves_bishop(Piece* board, int x, int y,int color)
{
    struct tab* table= malloc(sizeof(struct tab));
    int number=0;
    table->moves=malloc(sizeof(struct Moves));
    struct Moves * global_moves = table->moves;
    struct Moves* moves= malloc(sizeof(struct Moves));;
    int xmv=1; //x movement
    int ymv=1; //y movement
    //^>
    while (is_free(x+xmv,y+ymv,board) && out_of_bounds(x+xmv,y+ymv))
    {
        if (!testCHECK(x, y, x+xmv, y+ymv,board,color))
        {
        moves->x_pos = x+xmv;
        moves->y_pos = y+ymv;
        global_moves[number] = *moves;
        number++;
        }
        xmv++;
        ymv++;
    }
    if (is_obstacle(x+xmv,y+ymv,board,color) && out_of_bounds(x+xmv,y+ymv) && !testCHECK(x, y, x+xmv, y+ymv,board,color))
    {
        moves->x_pos = x+xmv;
        moves->y_pos = y+ymv;
        global_moves[number] = *moves;
    }
    //^<
    xmv=1;
    ymv=1;

    while (is_free(x-xmv,y+ymv,board) && out_of_bounds(x-xmv,y+ymv))
    {
        if (!testCHECK(x, y, x-xmv, y+ymv, board,color))
        {
        moves->x_pos = x-xmv;
        moves->y_pos = y+ymv;
        global_moves[number] = *moves;
        number++;
        }
        xmv++;
        ymv++;
    }
    if (is_obstacle(x-xmv,y+ymv,board,color) && out_of_bounds(x+xmv,y+ymv) && !testCHECK(x, y, x-xmv, y+ymv, board,color))
    {
        moves->x_pos = x-xmv;
        moves->y_pos = y+ymv;
        global_moves[number] = *moves;
    }
    //v>
    xmv=1;
    ymv=1;
    while (is_free(x+xmv,y-ymv,board) && out_of_bounds(x+xmv,y-ymv))
    {
        if (!testCHECK(x, y, x+xmv, y-ymv, board,color))
        {
        moves->x_pos = x+xmv;
        moves->y_pos = y-ymv;
        global_moves[number] = *moves;
        number++;
        }
        xmv++;
        ymv++;
    }
    if (is_obstacle(x+xmv,y-ymv,board,color) && out_of_bounds(x+xmv,y+ymv) && !testCHECK(x, y, x+xmv, y-ymv, board,color))
    {
        moves->x_pos = x+xmv;
        moves->y_pos = y-ymv;
        global_moves[number] = *moves;
    }
    //v<
    xmv=1;
    ymv=1;
    while (is_free(x-xmv,y-ymv,board) && out_of_bounds(x-xmv,y-ymv))
    {
        if (!testCHECK(x, y, x-xmv, y-ymv, board,color))
        {
        moves->x_pos = x-xmv;
        moves->y_pos = y-ymv;
            global_moves[number] = *moves;
            number++;
        }
        xmv++;
        ymv++;
    }
    if (is_obstacle(x-xmv,y-ymv,board,color) && !testCHECK(x, y, x-xmv, y-ymv, board,color) && out_of_bounds(x-xmv,y-ymv))
    {
        moves->x_pos = x-xmv;
        moves->y_pos = y-ymv;
        global_moves[number] = *moves;
    }
    free(moves);
    table->numberofmoves=number;
    return table;
}

struct tab* find_chess_moves_queen(Piece* board, int x, int y,int color)
{

    struct tab* table= malloc(sizeof(struct tab));
    int number=0;
    table->moves=malloc(sizeof(struct Moves));
    struct Moves * global_moves = table->moves;
    struct Moves* moves= malloc(sizeof(struct Moves));;
    int xmv=1; //x movement
    int ymv=1; //y movement

    //ROOK's moves
    //>>>>>move

    //>>>>>move
    while ( is_free(x+xmv,y,board) && out_of_bounds(x+xmv,y))
    {
        if (!testCHECK(x, y, x+xmv, y, board,color))
        {
            moves->x_pos = x+xmv;
            moves->y_pos = y;
            global_moves[number] = *moves;
            number++;
        }
        xmv++;
    }
    if (is_obstacle(x+xmv,y,board,color) && !testCHECK(x, y, x+xmv, y, board,color) && out_of_bounds(x+xmv,y))
    {
        moves->x_pos = x+xmv;
        moves->y_pos = y;
        global_moves[number] = *moves;
    }
    //<<<<<move
    xmv=1;
    while (is_free(x-xmv,y,board) && out_of_bounds(x-xmv,y))
    {
        if (!testCHECK(x, y, x-xmv, y, board,color))
        {
        moves->x_pos = x-xmv;
        moves->y_pos = y;
        global_moves[number] = *moves;
        number++;
        }
        xmv++;
    }
    if (is_obstacle(x-xmv,y,board,color) && out_of_bounds(x-xmv,y) && !testCHECK(x, y, x-xmv, y, board,color))
    {
        moves->x_pos = x-xmv;
        moves->y_pos = y;
        global_moves[number] = *moves;
    }
    //^^^^^move
    while (is_free(x,y+ymv,board) && out_of_bounds(x,y+ymv))
    {
        if (!testCHECK(x, y, x, y+ymv, board,color))
        {
        moves->x_pos = x;
        moves->y_pos = y+ymv;
        global_moves[number] = *moves;
        number++;
        }
        ymv++;
    }

    if (is_obstacle(x,y+ymv,board,color) && !testCHECK(x, y, x, y+ymv, board,color) && out_of_bounds(x,y+ymv))
    {
        moves->x_pos = x;
        moves->y_pos = y+ymv;
        global_moves[number] = *moves;
    }
    //vvvvvmove
    ymv=1;
    while (is_free(x,y-ymv,board) && out_of_bounds(x,y-ymv))
    {
        if (!testCHECK(x, y, x, y-ymv, board,color))
        {
        moves->x_pos = x;
        moves->y_pos = y-ymv;
        global_moves[number] = *moves;
        number++;
        }
        ymv++;
    }
    if (is_obstacle(x,y-ymv,board,color) && out_of_bounds(x,y-ymv) && !testCHECK(x, y, x, y-ymv, board,color))
    {
        moves->x_pos = x;
        moves->y_pos = y-ymv;
        global_moves[number] = *moves;
    }

    //BISHOP's moves
    xmv=1;
    ymv=1;


    //^>
    while (is_free(x+xmv,y+ymv,board) && out_of_bounds(x+xmv,y+ymv))
    {
        if (!testCHECK(x, y, x+xmv, y+ymv,board,color))
        {
        moves->x_pos = x+xmv;
        moves->y_pos = y+ymv;
        global_moves[number] = *moves;
        number++;
        }
        xmv++;
        ymv++;
    }
    if (is_obstacle(x+xmv,y+ymv,board,color) && out_of_bounds(x+xmv,y+ymv) && !testCHECK(x, y, x+xmv, y+ymv,board,color))
    {
        moves->x_pos = x+xmv;
        moves->y_pos = y+ymv;
        global_moves[number] = *moves;
    }
    //^<
    xmv=1;
    ymv=1;

    while (is_free(x-xmv,y+ymv,board) && out_of_bounds(x-xmv,y+ymv))
    {
        if (!testCHECK(x, y, x-xmv, y+ymv, board,color))
        {
        moves->x_pos = x-xmv;
        moves->y_pos = y+ymv;
        global_moves[number] = *moves;
        number++;
        }
        xmv++;
        ymv++;
    }
    if (is_obstacle(x-xmv,y+ymv,board,color) && out_of_bounds(x+xmv,y+ymv) && !testCHECK(x, y, x-xmv, y+ymv, board,color))
    {
        moves->x_pos = x-xmv;
        moves->y_pos = y+ymv;
        global_moves[number] = *moves;
    }
    //v>
    xmv=1;
    ymv=1;
    while (is_free(x+xmv,y-ymv,board) && out_of_bounds(x+xmv,y-ymv))
    {
        if (!testCHECK(x, y, x+xmv, y-ymv, board,color))
        {
        moves->x_pos = x+xmv;
        moves->y_pos = y-ymv;
        global_moves[number] = *moves;
        number++;
        }
        xmv++;
        ymv++;
    }
    if (is_obstacle(x+xmv,y-ymv,board,color) && out_of_bounds(x+xmv,y-ymv) && !testCHECK(x, y, x+xmv, y-ymv, board,color))
    {
        moves->x_pos = x+xmv;
        moves->y_pos = y-ymv;
            global_moves[number] = *moves;
    }
    //v<
    xmv=1;
    ymv=1;
    while (is_free(x-xmv,y-ymv,board) && out_of_bounds(x-xmv,y-ymv))
    {
        if (!testCHECK(x, y, x-xmv, y-ymv, board,color))
        {
        moves->x_pos = x-xmv;
        moves->y_pos = y-ymv;
            global_moves[number] = *moves;
            number++;
        }
        xmv++;
        ymv++;
    }
    if (is_obstacle(x-xmv,y-ymv,board,color) && out_of_bounds(x-xmv,y-ymv) && !testCHECK(x, y, x-xmv, y-ymv, board,color))
    {

        moves->x_pos = x-xmv;
        moves->y_pos = y-ymv;
        global_moves[number] = *moves;
    }

    free(moves);
    table->numberofmoves=number;
    return table;
}

//End safety Guard
#endif
