#include "minimax.h"
#include "MINImove.c"
#include "../../common/c/rules/plate.c"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#ifndef MINIMAX_C
#define MINIMAX_C


int get_min_from_list(int nb_children,struct node *children)
{
    int min = children[nb_children-1].score;
    nb_children--;
    while (nb_children>=0)
    {
        if (children[nb_children].score < min)
        {
            min = children[nb_children].score;
        }
        nb_children--;
    }
    return min;
}

int get_max_from_list(int nb_children,struct node *children)
{
    int max = children[nb_children-1].score;
    nb_children--;
    while (nb_children>=0)
    {
        if (children[nb_children].score > max)
        {
            max = children[nb_children].score;
        }
        nb_children--;
    }
    return max;
}

struct finalmove * get_right_move_ia(struct Piece *board, enum turn player_turn, int nb_List, int depth)
{
    struct finalmove * final = malloc(sizeof(struct finalmove));
    //struct currentpiece *current_List = create_whiteList();
    //struct currentpiece *current_ListB = create_blackList();

    //struct tree * T = create_tree(board, player_turn, current_List, nb_List, current_ListB, 16, depth);
    //struct node * root = T->root;
    return final;
}

struct tree * update_values(struct tree * T, int color, int depth)
{
    struct node * root = T->root;
    if (color==BLACK)
    {
        get_min_from_list(root->nb_children, root->children);
    }
    else{
        get_max_from_list(root->nb_children,root->children);
    }
    return T;
}

#endif
