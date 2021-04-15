/**
 * @author Antoine
 * @date Start 13/04/2021
 * @details Contain base of structure of MC TS.
 */

//Safety guard
#ifndef MONTECARLO_TREE_MCTS_H
#define MONTECARLO_TREE_MCTS_H

#include <stdio.h>

/**
 * @author Antoine
 * @date 14/04/2021
 * @details Alias of MCTS_NODE
 */
typedef struct MCTS_NODE MCTS_NODE;

/**
 * @author Antoine
 * @date Start 13/04/2021
 * @details Represent a node of tree.
 * @struct MCTS_NODE - Monte Carlo Search Tree
 *
 * @param father Father of node, NULL if root.
 *
 * @param win count of win found.
 * @param draw count of draw found.
 * @param loose count of loose found.
 * @param play count of game played.
 *
 * @param child_nb count of move possible from current board.
 * @param child_explore count of child already explored.
 *
 * @param child_move represent the move in question,
 *      each move in 4char, "A1A2" and at the end '0'.
 * @param child child node of move generate, NULL if not generated.
 */
struct MCTS_NODE
{
    MCTS_NODE * father;

    unsigned long win;
    unsigned long draw;
    unsigned long loose;
    unsigned long play;

    unsigned char child_nb;
    unsigned char child_explore;

    char * child_move;
    MCTS_NODE * child;
};


/**
 * @author Antoine
 * @date Start 14/04/2021
 * @details Generate a tree for represent the tree at a moment.
 *
 * @param pref prefix of each line of parent, can be '0'.
 * @param height left at maximum,
 *      if it's 0 no print and decreased at each layer.
 * @param node MCTS_NODE source, can't be NULL.
 *
 * @return NOTHING, but print in default terminal.
 */
void print_mcts_node(char *pref, unsigned char height, MCTS_NODE * node);

/**
 * @author Antoine
 * @date Start 14/04/2021
 * @details The goal is to free every child of node recursively.
 *      But the node give is not clear!
 *
 * @param node the node of question where childs are clear
 *
 * @return NOTHING.
 */
void clear_mcts_childs(MCTS_NODE * node);

/**
 * @author Antoine
 * @date Start 14/04/2021
 * @details The goal is to free parent and brother of the tree
 *
 * @param node the node of question where parent and brothers need to be free.
 *
 * @return NOTHING.
 */
void clear_mcts_brothers(MCTS_NODE * node);

//End safety guard
#endif
