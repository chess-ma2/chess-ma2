/**
 * @author Antoine
 * @date Start 13/04/2021
 * @details Contain base of structure of MC TS.
 */

//Safety guard
#ifndef AI_MONTECARLO_TREE_MCTS_H
#define AI_MONTECARLO_TREE_MCTS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * @author Antoine
 * @date 15/04/2021
 * @details Alias of MCTS_Status
 */
typedef enum MCTS_Status MCTS_Status;

/**
 * @author Antoine
 * @date 14/04/2021
 * @details Alias of MCTS_Node
 */
typedef struct MCTS_Node MCTS_Node;

/**
 * @author Antoine
 * @date Start 15/04/2021
 * @details Represent the current state of node
 * @enum MCTS_STATUS_NONE - Final status not currently assigned
 * @enum MCTS_STATUS_FULL_EXPLORE - Each child are fully explored
 *      (<=> status != MCTS_STATUS_NONE)
 * @enum MCTS_STATUS_FORCED_WIN - Each child are full explore and go to a win.
 * @enum MCTS_STATUS_FORCED_DRAW -Each child are full explore and go draw.
 * @enum MCTS_STATUS_FORCED_LOOSE -Each child are full explore and go loose.
 * @enum MCTS_STATUS_LEAF_WIN - Leaf of a game with Win.
 * @enum MCTS_STATUS_LEAF_Draw - Leaf of a game with Draw.
 * @enum MCTS_STATUS_LEAF_Loose - Leaf of a game with Loose.
 */
enum MCTS_Status
{
    MCTS_STATUS_NONE,
    MCTS_STATUS_FULL_EXPLORE,
    MCTS_STATUS_FORCED_WIN,
    MCTS_STATUS_FORCED_DRAW,
    MCTS_STATUS_FORCED_LOOSE,
    MCTS_STATUS_LEAF_WIN,
    MCTS_STATUS_LEAF_PAT,
    MCTS_STATUS_LEAF_LOOSE
};

/**
 * @author Antoine
 * @date Start 13/04/2021
 * @details Represent a node of tree.
 * @struct MCTS_NODE - Monte Carlo Search Tree
 *
 * @param status represent the current state of the node
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
 *      Please note:
 *             Generated is at the start, after first null each are null.
 */
struct MCTS_Node
{
    MCTS_Status status;
    MCTS_Node * father;

    unsigned long win;
    unsigned long draw;
    unsigned long loose;
    unsigned long play;

    unsigned char child_nb;
    unsigned char child_explore;

    char * child_move;
    MCTS_Node * child;
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
void print_mcts_node(char *pref, unsigned char height, MCTS_Node * node);

/**
 * @author Antoine
 * @date Start 14/04/2021
 * @details The goal is to free every child of node recursively.
 *      But the node give is not clear!
 *
 * @param node the node of question where child are clear
 *
 * @return count of node clear.
 */
unsigned long clear_mcts_child(MCTS_Node * node);

/**
 * @author Antoine
 * @date Start 14/04/2021
 * @details The goal is to free parent and brother of the tree
 *
 * @param node the node of question where parent and brothers need to be free.
 *
 * @return count of node clear.
 */
unsigned long clear_mcts_brothers(MCTS_Node * node);

//End safety guard
#endif
