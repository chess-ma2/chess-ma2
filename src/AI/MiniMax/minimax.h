#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#ifndef MINIMAX_H
#define MINIMAX_H
// Include section _______________________________
#include "../../common/c/rules/check_and_pat.c"
#include "../../common/c/rules/pieces.c"
#include "../../common/c/rules/plate.c"
#include "../../common/c/game/added_functions.c"
#include "MINImove.c"
#include "queue.c"
#include "tree.c"

// Structure function ____________________________

struct finalmove{
    int x;
    int y;
    int xdes;
    int ydes;
};


// Function section _______________________________

int get_min(int nb_children,struct node *children);

int get_max(int nb_children,struct node *children);

struct finalmove * get_move (struct tree * T);

struct finalmove * get_right_move_ia(struct Piece *board, enum turn player_turn, int depth, struct tree * T);

struct node * update_values (struct node * T);

#endif
