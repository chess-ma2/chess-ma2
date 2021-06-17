/**
 * @author Antoine
 * @date Start 13/04/2021
 * @details Contain function to manipulate MCTS_NODE
 */

//Safety guard
#ifndef AI_MONTECARLO_TREE_MCTS_C
#define AI_MONTECARLO_TREE_MCTS_C

#include "mctsn.h"
#include "../../tree/mcts.c"
void print_mctsn_node(char *pref, unsigned char height, MCTSN_Node * node)
{
    if (height == 0 || node == NULL)
        return;

    printf("%s-> %lu/%lu/%lu =  %lu and %i |  %i\n",
           pref, node->win, node->draw, node->loose, node->play,
           node->node_network_value, node->child_nb);

    display(node->board);
    if (node->child_nb != 0 && node->child != NULL)
    {
        printf("%s  Child:\n", pref);

        char *subpref = malloc(sizeof(char) * (3 + strlen(pref)));
        sprintf(subpref, "%s%s", pref, "  |");

        for (int i = 0; i < node->child_nb; i++) {
            print_mctsn_node(subpref, height - 1, *(node->child + i));
        }
    }
    printf("%s\n", pref);
}

unsigned long clear_mctsn_child(MCTSN_Node * node)
{
    if (node == NULL || node->child == NULL)
        return 0;
    unsigned long clear = node->child_nb;

    //Recursively call theirs child.
    for (unsigned char count = 0; count < node->child_nb; count++)
    {
        clear += clear_mctsn_child(*(node->child + count));
        free((*(node->child + count))->board);
        //free((*(node->child + count)));
    }
    //free(node->child);
    //Update own properties
    node->child_nb = 0;
    node->child = NULL;
    node->status = MCTSN_STATUS_NONE;
    return clear;
}

unsigned long clear_mctsn_brothers(MCTSN_Node * node)
{
    if (node->father == NULL)
        return 0;

    MCTSN_Node * father = node->father;
    unsigned long clear = father->child_nb;//-1+1;-Child+Father.

    //Clear child of father (<=> brothers) except node.
    for (unsigned char count = 0; count < father->child_nb; count++)
    {
        //Not clean own node
        if (*(father->child + count) == node)
            continue;

        clear += clear_mctsn_child(*(father->child + count));
        free((father->child + count));
    }
    //No update of father properties because is auto free.

    //Recursively call father
    clear += clear_mctsn_brothers(father->father);

    //Free & auto update own pointer
    free(father);
    node->father = NULL;

    return clear;
}
//End safety guard
#endif
