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
            //printf("min is %i \n", min);
        }
        children = children->next;
        //printf("next score is is %i \n", children->score);
        nb_children--;
    }
    return min;
}

int get_max(int nb_children,struct node *children)
{
    int max = children->score;
    //printf("nb child %i\n", nb_children);
    while (nb_children > 0)
    {
        if (children->score > max)
        {
            max = children->score;
            //printf("max is %i \n", max);
        }
        children = children->next;
        //printf("next score is is %i \n", children->score);
        nb_children--;
        //printf("aft \n");
    }
    //printf("before max \n");
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

    //display_board_special(root->board);
    //printf("score = %i",root->score);
    final->x = root->xbeg;
    final->y = root->ybeg;
    final->xdes = root->x;
    final->ydes = root->y;

    return final;

}

struct finalmove * get_right_move_ia(struct Piece *board,struct currentpiece *current_List, struct currentpiece *current_ListB, enum turn player_turn, int depth, int nbw,int nbb)
{
    struct tree * T = create_tree(board, player_turn, current_List, nbw,current_ListB, nbb,  depth);
    //pretty_print(T, 2);
    //printdfs(T);
    printf("tree created\n");
    struct node * root = T->root;
    root = update_values(root);
    struct finalmove * move = get_move(T);
    free(T);
    return move;
}

struct node * update_values(struct node * root)
{
    //struct node * root = T->root;

    //printf("score is %i nb childr %i\n", root->score, root->nb_children);
    struct node * trans = root->childn1;
    for (int i=0; i<root->nb_children; i++)
    {
        //here updating values of every children before the roots one
        root = update_values(trans);
        trans = trans -> next;
            //ALPHABETA
            //si mini et valeur maxi alors virer
    }
    //printf("testing \n" );
    if (root->nb_children > 0) {
    if (root->MiniMax==0)
    {
        //printf("before min \n");
        root->score = get_min(root->nb_children, root->childn1);
        //printf("after min \n");
    }
    else
    {
        //printf("before max\n");
        root->score = get_max(root->nb_children,root->childn1);
        //printf("after max \n");
    }
  }
    return root;
}
//essai de alpha beta
//NOTE IL FAUT AJOUTER AU NOEUDS DES VALEURS MAX ET MIN


#endif
