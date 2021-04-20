/**
 * @author Antoine
 * @date Start 13/04/2021
 * @details Contain function to manipulate MCTS_NODE
 */

//Safety guard
#ifndef AI_MONTECARLO_TREE_MCTS_C
#define AI_MONTECARLO_TREE_MCTS_C

#include "mcts.h"

void print_mcts_node(char *pref, unsigned char height, MCTS_Node * node)
{
    if (height == 0)
        return;

    printf("%s-> %lu/%lu/%lu | %lu -  %i/%i\n",
           pref, node->win, node->draw, node->loose, node->play,
           node->child_explore, node->child_nb);
    printf("%s  Child:\n", pref);

    char * subpref = malloc(sizeof(char)*(3+ strlen(pref)));
    sprintf(subpref, "%s%s", pref, "  |");

    for (int i = 0; i < node->child_explore; i++)
    {
        print_mcts_node(subpref, height - 1, (node->child + i));
    }

    printf("%s\n", pref);
}

unsigned long clear_mcts_child(MCTS_Node * node)
{
    unsigned long clear = node->child_explore;

    //Recursively call theirs child.
    for (unsigned char count = 0; count < node->child_explore; count++)
    {
        clear += clear_mcts_child((node->child + count));
        free((node->child + count));
    }

    //Update own properties
    node->child_explore = 0;
    node->status = MCTS_STATUS_NONE;
    return clear;
}

unsigned long clear_mcts_brothers(MCTS_Node * node)
{
    if (node->father == NULL)
        return 0;

    MCTS_Node * father = node->father;
    unsigned long clear = father->child_explore;//-1+1;-Child+Father.

    //Clear child of father (<=> brothers) except node.
    for (unsigned char count = 0; count < father->child_explore; count++)
    {
        //Not clean own node
        if ((father->child + count) == node)
            continue;

        clear += clear_mcts_child((father->child + count));
        free((father->child + count));
    }
    //No update of father properties because is auto free.

    //Recursively call father
    clear += clear_mcts_brothers(father->father);

    //Free & auto update own pointer
    free(father);
    node->father = NULL;

    return clear;
}
//End safety guard
#endif
