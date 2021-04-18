/**
 * @author Marine
 * @date Start 15/04/2021
 * @details For finds move list of possible for IA
 */

//TO DO NEED TO ADD THE CHECKING FOR THE KING
//NEED to make a copy of the board with the new move to check king check

//Safety Guard
#ifndef MINIMOVE_C
#define MINIMOVE_C

#include "MINImove.h"

int out_of_bounds( int x,  int y)
{
    if (x<( int)A || x>( int)H || y<1 || y>8)
    {
        return 0;
    }
    return 1;
}

int is_obstacle(int x, int y, Piece* board,int color)
{
    struct Piece piece = board[y*8+x];
    if (piece.type!=NONE && piece.color!=color)
    {
        return 0;
    }
    return 1;
}

int testCHECK(int xinit, int yinit, int xtest, int ytest, Piece* board)
{
    //changes coordinates to make the test
    board[xtest+ytest*8].type=board[xinit+yinit*8].type;
    board[xtest+ytest*8].color=board[xinit+yinit*8].color;
    board[xinit+yinit*8].type=NONE;
    
    if (check_mat(xtest, ytest+1, color,board))
    {
        //resset the orignal values
        board[xinit+yinit*8].type=board[xtest+ytest*8].type;
        board[xtest+ytest*8].type=NONE;
        return 1;
    }
    //resset the orignal values
    board[xinit+yinit*8].type=board[xtest+ytest*8].type;
    board[xtest+ytest*8].type=NONE;
    return 0;
}

struct Moves* find_chess_moves_pawn(Piece* board,  int x,  int y,int color)
{
    struct Moves* moves=malloc(sizeof(struct Moves));
    
    //CHECK INTIAL PLACE +2
    if ((color==0 && y==2)|| (color==1 && y==7))
    {
        if (is_obstacle(x,y+2*(-1)*color,color) && out_of_bounds(xtest,y+2*(-1)*color))
        {
            if (!testCHECK(x, y, x, y+2*(-1)*color, Piece* board))
            {
                moves++;
                moves=malloc(sizeof(struct Moves));
                moves.x_pos = x;
                moves.y_pos = y+2*(-1)*color;
                
            }
        }
    }
    
    //CHECK +1 FRONT MOVE
    if (is_obstacle(x,y+1*(-1)*color,color) && out_of_bounds(x,y+1*(-1)*color) && !testCHECK(x, y, x, y+1*(-1)*color, Piece* board))
    {
        moves++;
        moves=malloc(sizeof(struct Moves));
        moves.x_pos = x;
        moves.y_pos = y+1*(-1)*color;
    }
    
    //CHECK EAT MOVE right diag
    if (is_obstacle(x+1,y+1*(-1)*color,color) && out_of_bounds(x+1,y+1*(-1)*color) && !testCHECK(x, y, x+1, y+1*(-1)*color, Piece* board))
    {
        moves++;
        moves=malloc(sizeof(struct Moves));
        moves.x_pos = x+1;
        moves.y_pos = y+1*(-1)*color;
    }
    
    //CHECK EAT MOVE left diag
    if (is_obstacle(x-1,y+1*(-1)*color,color) && out_of_bounds(x-1,y+1*(-1)*color) && !testCHECK(x, y, x-1, y+1*(-1)*color, Piece* board))
    {
        moves++;
        moves=malloc(sizeof(struct Moves));
        moves.x_pos = x-1;
        moves.y_pos = y+1*(-1)*color;
    }
    
    
    return moves;
}

struct Moves* find_chess_moves_knight(Piece* board,  int x,  int y,int color)
{
    struct Moves* moves;
    
    //shape * dest
    //      *
    //      x
    
    if (is_obstacle(x+1,y+2,color) && out_of_bounds(x+1,y+2) && !testCHECK(x, y, x+1, y+2, Piece* board))
    {
        //check if king is in danger
        moves++;
        moves=malloc(sizeof(struct Moves));
        moves.x_pos = x+1;
        moves.y_pos = y+2;
    }
    
    //shape dest *
    //           *
    //           x
    
    if (is_obstacle(x-1,y+2,color) && out_of_bounds(x-1,y+2) && !testCHECK(x, y, x-1, y+2, Piece* board))
    {
        //check if king is in danger
        moves++;
        moves=malloc(sizeof(struct Moves));
        moves.x_pos = x-1;
        moves.y_pos = y+2;
    }

    
    //shape   dest  *  *
    //                 x
    if (is_obstacle(x-2,y+2,color) && out_of_bounds(x-2,y+2) && !testCHECK(x, y, x-2, y+2, Piece* board))
    {
        //check if king is in danger
        moves++;
        moves=malloc(sizeof(struct Moves));
        moves.x_pos = x-2;
        moves.y_pos = y+2;
    }
    
    
    //shape *  *  dest
    //      x
    if (is_obstacle(x+2,y+2,color) && out_of_bounds(x+2,y+2) && !testCHECK(x, y, x+2, y+2, Piece* board))
    {
        //check if king is in danger
        moves++;
        moves=malloc(sizeof(struct Moves));
        moves.x_pos = x+2;
        moves.y_pos = y+2;
    }
    
    
    //shape x
    //      *
    //      * dest
    if (is_obstacle(x+1,y-2,color) && out_of_bounds(x+1,y-2) && !testCHECK(x, y, x+1, y-2, Piece* board))
    {
        //check if king is in danger
        moves++;
        moves=malloc(sizeof(struct Moves));
        moves.x_pos = x+1;
        moves.y_pos = y-2;
    }
    
    
    //shape     x
    //          *
    //      dest
    if (is_obstacle(x-1,y-2,color) && out_of_bounds(x-1,y-2) && !testCHECK(x, y, x-1, y-2, Piece* board))
    {
        //check if king is in danger
        moves++;
        moves=malloc(sizeof(struct Moves));
        moves.x_pos = x-1;
        moves.y_pos = y-2;
    }
    
    
    //shape      x
    //           *  *   dest
    if (is_obstacle(x+2,y-1,color) && out_of_bounds(x+2,y-1) && !testCHECK(x, y, x+2, y-1, Piece* board))
    {
        //check if king is in danger
        moves++;
        moves=malloc(sizeof(struct Moves));
        moves.x_pos = x+2;
        moves.y_pos = y-1;
    }
    
    
    //shape          x
    //        dest * *
    if (is_obstacle(x-2,y-1,color) && out_of_bounds(x-2,y-1) && !testCHECK(x, y, x-2, y-1, Piece* board))
    {
        //check if king is in danger
        moves++;
        moves=malloc(sizeof(struct Moves));
        moves.x_pos = x-2;
        moves.y_pos = y-1;
    }
    
    return moves;
}

struct Moves* find_chess_moves_king(Piece* board, int x, int y,int color)
{
    
    struct Moves* moves;
    //to do check 9 moves possible
    //^
    if (is_obstacle(x,y+1,color) && out_of_bounds(x,y+1) && !testCHECK(x, y, x, y+1, Piece* board))
    {
        moves++;
        moves=malloc(sizeof(struct Moves));
        moves.x_pos = x;
        moves.y_pos = y+1;
    }
    //v
    if (is_obstacle(x,y-1,color) && out_of_bounds(x,y-1) && !testCHECK(x, y, x, y-1, Piece* board))
    {
        moves++;
        moves=malloc(sizeof(struct Moves));
        moves.x_pos = x;
        moves.y_pos = y-1;
    }
    //>
    if (is_obstacle(x+1,y,color) && out_of_bounds(x+1,y) && !testCHECK(x, y, x+1, y, Piece* board))
    {
        moves++;
        moves=malloc(sizeof(struct Moves));
        moves.x_pos = x+1;
        moves.y_pos = y;
    }
    //<
    if (is_obstacle(x-1,y,color) && out_of_bounds(x-1,y) && !testCHECK(x, y, x-1, y, Piece* board))
    {
        moves++;
        moves=malloc(sizeof(struct Moves));
        moves.x_pos = x-1;
        moves.y_pos = y;
    }
    //^>
    if (is_obstacle(x+1,y+1,color) && out_of_bounds(x+1,y+1) && !testCHECK(x, y, x+1, y+1, Piece* board))
    {
        moves++;
        moves=malloc(sizeof(struct Moves));
        moves.x_pos = x+1;
        moves.y_pos = y+1;
    }
    //v>
    if (is_obstacle(x+1,y-1,color) && out_of_bounds(x+1,y-1) && !testCHECK(x, y, x+1, y-1, Piece* board))
    {
        moves++;
        moves=malloc(sizeof(struct Moves));
        moves.x_pos = x+1;
        moves.y_pos = y-1;
    }
    //^<
    if (is_obstacle(x-1,y+1,color) && out_of_bounds(x-1,y+1) && !testCHECK(x, y, x-1, y+1, Piece* board))
    {
        moves++;
        moves=malloc(sizeof(struct Moves));
        moves.x_pos = x-1;
        moves.y_pos = y+1;
    }
    //v<
    if (is_obstacle(x-1,y-1,color) && out_of_bounds(x-1,y-1) && !testCHECK(x, y, x-1, y-1, Piece* board))
    {
        moves++;
        moves=malloc(sizeof(struct Moves));
        moves.x_pos = x-1;
        moves.y_pos = y-1;
    }
    
    return NULL;
}


struct Moves* find_chess_moves_rook(Piece* board, int x, int y,int color)
{
    
    struct Moves* moves;
    int xmv=1; //x movement
    int ymv=1; //y movement
    
    //>>>>>move
    while ((is_obstacle(x+xmv,y,color) && out_of_bounds(x+xmv,y) && board[8*y+x+xmv-1].color!=color)
    {
        if (!testCHECK(x, y, x+xmv, y, Piece* board))
        {
        moves++;
        moves=malloc(sizeof(struct Moves));
        moves.x_pos = x+xmv;
        moves.y_pos = y;
        xmv++;
        }
    }
    //<<<<<move
    xmv=1;
    while ((is_obstacle(x-xmv,y,color) && out_of_bounds(x-xmv,y) && board[8*y+x-xmv+1].color!=color)
    {
        if (!testCHECK(x, y, x-xmv, y, Piece* board))
        {
        moves++;
        moves=malloc(sizeof(struct Moves));
        moves.x_pos = x-xmv;
        moves.y_pos = y;
        xmv++;
        }
    }
           
    //^^^^^move
    while ((is_obstacle(x,y+ymv,color) && out_of_bounds(x,y+ymv) && board[8*(y+ymv-1)+x].color!=color)
    {
        if (!testCHECK(x, y, x, y+ymv, Piece* board))
        {
        moves++;
        moves=malloc(sizeof(struct Moves));
        moves.x_pos = x;
        moves.y_pos = y+ymv;
        ymv++;
        }
    }
           
    //vvvvvmove
    ymv=1;
    while ((is_obstacle(x,y-ymv,color) && out_of_bounds(x,y-ymv) && board[8*(y+ymv+1)+x].color!=color)
    {
        if (!testCHECK(x, y, x, y-ymv, Piece* board))
        {
        moves++;
        moves=malloc(sizeof(struct Moves));
        moves.x_pos = x;
        moves.y_pos = y-ymv;
        ymv++;
        }
    }
    
    return moves;
}


struct Moves* find_chess_moves_bishop(Piece* board, int x, int y,int color)
{
    struct Moves* moves;
    int xmv=1; //x movement
    int ymv=1; //y movement
    //^>
    while ((is_obstacle(x+xmv,y+ymv,color) && out_of_bounds(x+xmv,y+ymv) && board[8*(y+ymv-1)+x+xmv-1].color!=color)
    {
        if (!testCHECK(x, y, x+xmv, y+ymv, Piece* board))
        {
        moves++;
        moves=malloc(sizeof(struct Moves));
        moves.x_pos = x+xmv;
        moves.y_pos = y+ymv;
        xmv++;
        ymv++;
        }
    }
    //^<
    xmv=1;
    ymv=1;
           
    while ((is_obstacle(x-xmv,y+ymv,color) && out_of_bounds(x-xmv,y+ymv) && board[8*(y+ymv-1)+x+xmv+1].color!=color)
    {
        if (!testCHECK(x, y, x-xmv, y+ymv, Piece* board))
        {
        moves++;
        moves=malloc(sizeof(struct Moves));
        moves.x_pos = x-xmv;
        moves.y_pos = y+ymv;
        xmv++;
        ymv++;
        }
    }
    
    //v>
    xmv=1;
    ymv=1;
    while ((is_obstacle(x+xmv,y-ymv,color) && out_of_bounds(x+xmv,y-ymv) && board[8*(y+ymv+1)+x+xmv-1].color!=color)
    {
        if (!testCHECK(x, y, x+xmv, y-ymv, Piece* board))
        {
        moves++;
        moves=malloc(sizeof(struct Moves));
        moves.x_pos = x+xmv;
        moves.y_pos = y-ymv;
        xmv++;
        ymv++;
        }
    }
    //v<
    xmv=1;
    ymv=1;
    while ((is_obstacle(x-xmv,y-ymv,color) && out_of_bounds(x-xmv,y-ymv) && board[8*(y+ymv+1)+x+xmv+1].color!=color)
    {
        if (!testCHECK(x, y, x-xmv, y-ymv, Piece* board))
        {
        moves++;
        moves=malloc(sizeof(struct Moves));
        moves.x_pos = x-xmv;
        moves.y_pos = y-ymv;
        xmv++;
        ymv++;
        }
    }
           
    return moves;
}

struct Moves* find_chess_moves_queen(Piece* board, int x, int y,int color)
{
    struct Moves* moves;
    int xmv=1; //x movement
    int ymv=1; //y movement
    
    //ROOK's moves
    //>>>>>move
    
    //>>>>>move
    while ((is_obstacle(x+xmv,y,color) && out_of_bounds(x+xmv,y) && board[8*y+x+xmv-1].color!=color)
    {
        if (!testCHECK(x, y, x+xmv, y, Piece* board))
        {
        moves++;
        moves=malloc(sizeof(struct Moves));
        moves.x_pos = x+xmv;
        moves.y_pos = y;
        xmv++;
        }
    }
    //<<<<<move
    xmv=1;
    while ((is_obstacle(x-xmv,y,color) && out_of_bounds(x-xmv,y) && board[8*y+x-xmv+1].color!=color)
    {
        if (!testCHECK(x, y, x-xmv, y, Piece* board))
        {
        moves++;
        moves=malloc(sizeof(struct Moves));
        moves.x_pos = x-xmv;
        moves.y_pos = y;
        xmv++;
        }
    }
           
    //^^^^^move
    while ((is_obstacle(x,y+ymv,color) && out_of_bounds(x,y+ymv) && board[8*(y+ymv-1)+x].color!=color)
    {
        if (!testCHECK(x, y, x, y+ymv, Piece* board))
        {
        moves++;
        moves=malloc(sizeof(struct Moves));
        moves.x_pos = x;
        moves.y_pos = y+ymv;
        ymv++;
        }
    }
           
    //vvvvvmove
    ymv=1;
    while ((is_obstacle(x,y-ymv,color) && out_of_bounds(x,y-ymv) && board[8*(y+ymv+1)+x].color!=color)
    {
        if (!testCHECK(x, y, x, y-ymv, Piece* board))
        {
        moves++;
        moves=malloc(sizeof(struct Moves));
        moves.x_pos = x;
        moves.y_pos = y-ymv;
        ymv++;
        }
    }
    
           
    //BISHOP's moves
    xmv=1;
    ymv=1;
    
           
    //^>
    while ((is_obstacle(x+xmv,y+ymv,color) && out_of_bounds(x+xmv,y+ymv) && board[8*(y+ymv-1)+x+xmv-1].color!=color)
    {
        if (!testCHECK(x, y, x+xmv, y+ymv, Piece* board))
        {
            moves++;
            moves=malloc(sizeof(struct Moves));
            moves.x_pos = x+xmv;
            moves.y_pos = y+ymv;
            xmv++;
            ymv++;
            }
    }
    //^<
    xmv=1;
    ymv=1;
                  
    while ((is_obstacle(x-xmv,y+ymv,color) && out_of_bounds(x-xmv,y+ymv) && board[8*(y+ymv-1)+x+xmv+1].color!=color)
    {
        if (!testCHECK(x, y, x-xmv, y+ymv, Piece* board))
        {
            moves++;
            moves=malloc(sizeof(struct Moves));
            moves.x_pos = x-xmv;
            moves.y_pos = y+ymv;
            xmv++;
            ymv++;
        }
    }
           
    //v>
    xmv=1;
    ymv=1;
    while ((is_obstacle(x+xmv,y-ymv,color) && out_of_bounds(x+xmv,y-ymv) && board[8*(y+ymv+1)+x+xmv-1].color!=color)
    {
        if (!testCHECK(x, y, x+xmv, y-ymv, Piece* board))
        {
            moves++;
            moves=malloc(sizeof(struct Moves));
            moves.x_pos = x+xmv;
            moves.y_pos = y-ymv;
            xmv++;
            ymv++;
        }
    }
    //v<
    xmv=1;
    ymv=1;
    while ((is_obstacle(x-xmv,y-ymv,color) && out_of_bounds(x-xmv,y-ymv) && board[8*(y+ymv+1)+x+xmv+1].color!=color)
    {
        if (!testCHECK(x, y, x-xmv, y-ymv, Piece* board))
        {
            moves++;
            moves=malloc(sizeof(struct Moves));
            moves.x_pos = x-xmv;
            moves.y_pos = y-ymv;
            xmv++;
            ymv++;
        }
    }
           
    return moves;
}

//End safety Guard
#endif
