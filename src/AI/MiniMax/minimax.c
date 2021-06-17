#include "minimax.h"
#include "MINImove.c"
#include "tree.c"
#include "../../common/c/rules/plate.c"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#ifndef MINIMAX_C
#define MINIMAX_C


int get_min(int nb_children,struct node *children)
{
    int min = children->score;
    while (nb_children>=0)
    {
        if ( children->score < min)
        {
            min = children->score;
        }
        children = children->next;
        nb_children--;
    }
    return min;
}

int get_max(int nb_children,struct node *children)
{
    int max = children->score;
    while (nb_children > 0)
    {
        if (children->score > max)
        {
            max = children->score;
        }
        children = children->next;
        nb_children--;
    }
    return max;
}

struct finalmove * get_move (struct tree * T)
{
    struct finalmove * final = malloc(sizeof(struct finalmove));
    struct node * root = T->root;
    int color = root->MiniMax;
    int nb_children= root->nb_children;
    int idx=0;

    if (color==1) //==blanc donc > 0 ?
    {
        idx = get_max( nb_children, root->childn1);
    }

    else
    {
        idx = get_min( nb_children, root->childn1);
    }
    root = root -> childn1;
    while (root->score != idx && root != NONE )
    {
        root = root->next;
    }

    final->x = root->xbeg;
    final->y = root->ybeg;
    final->xdes = root->x;
    final->ydes = root->y;

    return final;

}

struct finalmove * get_right_move_ia(struct Piece *board,struct currentpiece *current_List, struct currentpiece *current_ListB, enum turn player_turn, int depth, int nbw,int nbb)
{
    struct tree * T = create_tree(board, player_turn, current_List, nbw,current_ListB, nbb,  depth);
    struct node * root = T->root;
    root = update_values(root);
    struct finalmove * move = get_move(T);
    free(T);
    return move;
}

struct node * update_values(struct node * root)
{
    struct node * trans = root->childn1;
    for (int i=0; i<root->nb_children; i++)
    {
        //here updating values of every children before the roots one
        root = update_values(trans);
        trans = trans -> next;
            //ALPHABETA
            //si mini et valeur maxi alors virer
    }
    if (root->nb_children > 0) {
    if (root->MiniMax==0)
    {
        root->score = get_min(root->nb_children, root->childn1);
    }
    else
    {
        root->score = get_max(root->nb_children,root->childn1);
    }
  }
    return root;
}
//essai de alpha beta
//NOTE IL FAUT AJOUTER AU NOEUDS DES VALEURS MAX ET MIN


#endif
