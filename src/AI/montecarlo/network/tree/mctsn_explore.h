/**
 * @author Antoine
 * @date Start 16/05/2021
 * @details Contain function to manipulate MCTS_NODE
 * @note This work is inspired from Marie Work
 *  and adapted for network compatibility
 */

//Safety guard
#ifndef AI_MONTECARLO_TREE_MCTS_EXPLORE_H
#define AI_MONTECARLO_TREE_MCTS_EXPLORE_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#include "mctsn.c"
#include "../structure/network.c"
#include "../chess/evaluate.h"
#include "../../tree/create_childs.c"
#include "../../tree/mcts.c"
#include "../../tree/check_and_pat_for_AI.c"
#include "../../../../common/c/rules/check_and_pat.c"
#include "../../../../common/c/rules/pieces.c"
#include "../../../../common/c/rules/plate.c"

/**
 * @author Antoine
 * @date 26/05/2021
 * @details Alias for structure PATH_EXPLORE
 */
typedef struct PATH_EXPLORE PATH_EXPLORE;

/**
 * @author Antoine
 * @date 20/05/2021
 * @details Structure for get upper result of path
 */
struct PATH_EXPLORE
{
    unsigned long leaf;
    unsigned long win;
    unsigned long draw;
    unsigned long loose;
};

/**
 * @author Antoine
 * @date Start 16/05/2021
 * @details Generate childs for MCTSN_Node
 * @param node Node were childs is add
 * @param network Network (optional) where is compute values
 */
void network_mctsn_generate_child(MCTSN_Node *node, Network * network);

/**
 * @author Antoine
 * @date Start 17/05/2021
 * @details Generate X paths of tree
 * @param node Node where we start
 * @param network network for compute (can be NULL)
 * @param paths Count of path generate
 * @param original_color Team of start
 * @return PATH_EXPLORE with result of path search
 */
PATH_EXPLORE * network_mctsn_generate_path(MCTSN_Node * node,
                                           Network * network,
                                 unsigned long paths, int original_color);

/**
 * @author Antoine
 * @date Start 20/05/2021
 * @details Shortcut, generate a choice of this algorithm from a board
 *  and output the preferred choice
 * @param board Board of start
 * @param network Network for run value (can be NULL)
 * @param color For the team play
 * @return Board choice
 */
struct Piece * network_mctsn_choice(struct Piece * board,
        Network * network, int color);
//End safety guard
#endif
