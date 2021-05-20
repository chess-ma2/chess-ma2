#include "minimax.h"
#include "MINImove.c"
#include "../../common/c/rules/plate.c"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#ifndef MINIMAX_C
#define MINIMAX_C

//QUESTIONS A POSER A ANNA pour la finalisation et les tests
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

struct finalmove * get_move (struct tree * T)
{
    struct node * root = T->root;
    int color = root->MiniMax;
    int nb_children= root->nb_children;
    int idxmove=nb_children;
    
    if (color==1)//1 =MINI? si oui faire ca
    {
        nb_children--;
        while (nb_children>=0)
        {
            if (children[nb_children].score < children[idxmove].score)
            {
                idxmove= children[nb_children].score;
            }
            nb_children--;
        }
    }
    else
    {
        nb_children--;
        while (nb_children>=0)
        {
            if (children[nb_children].score > children[max].score)
            {
                max = children[nb_children].score;
            }
            nb_children--;
        }
    }
    
}

struct finalmove * get_right_move_ia(struct Piece *board, enum turn player_turn, int nb_List, int depth)
{
    struct finalmove * final = malloc(sizeof(struct finalmove));
    //struct currentpiece *current_List = create_whiteList();
    //struct currentpiece *current_ListB = create_blackList();

    //struct tree * T = create_tree(board, player_turn, current_List, nb_List, current_ListB, 16, depth);
    //struct node * root = T->root;
    T= update_values(T,1);
    struct finalmove * move = get_move(T);
    return move;
}

struct tree * update_values(struct tree * T, int color)
{
    struct node * root = T->root;
    for (int i=0; i<root->nb_children; i++)
    {
        if (nb_children>0)
        {
            root = update_values(root,color);
            //ALPHABETA
            //si mini et valeur maxi alors virer 
        }
    }
    if (color==BLACK)
    {
        root.score = get_min_from_list(root->nb_children, root->children);
    }
    else
    {
        root.score = get_max_from_list(root->nb_children,root->children);
    }
    return T;
}
//essai de alpha beta
//NOTE IL FAUT AJOUTER AU NOEUDS DES VALEURS MAX ET MIN


#endif
