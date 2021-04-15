/**
 * @author Antoine
 * @date Start 13/04/2021
 * @details Contain function to manipulate MCTS_NODE
 */

//Safety guard
#ifndef MONTECARLO_TREE_MCTS_C
#define MONTECARLO_TREE_MCTS_C

#include "mcts.h"

void print_mcts_node(char *pref, unsigned char height, MCTS_NODE * node)
{
    if (height == 0)
        return;

    printf("%s-> %lu/%lu/%lu | %lu -  %i/%i\n",
           pref, node->win, node->draw, node->loose, node->play,
           node->child_explore, node->child_nb);
    printf("%s  Child:\n", pref);

    char * subpref;
    vfprintf(subpref, "%s%s", pref, "  |");

    for (int i = 0; i < node->child_explore; i++)
    {
        print_mcts_node(subpref, height - 1, (node->child + i));
    }

    printf("%s\n", pref);
}

void clear_mcts_childs(MCTS_NODE * node)
{

}

void clear_mcts_brothers(MCTS_NODE * node)
{

}
//End safety guard
#endif
