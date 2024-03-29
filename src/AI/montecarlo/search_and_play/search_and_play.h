/**
 * @author Marie
 * @date Start 15/04/2021
 * @details Contain functions for the AI
 */

#ifndef SEARCH_AND_PLAY_H
#define SEARCH_AND_PLAY_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "../tree/mcts.c"

/**
 * @author Marie
 * @date Start 15/04/2021
 * @details go down to a leaf of the tree
 */

struct MCTS_Node *select_action(struct MCTS_Node *node, int color);

/**
 * @author Marie
 * @date Start 15/04/2021
 * @details Select the "best" child with the exploration and the value
 */

struct MCTS_Node *selected(struct MCTS_Node *node);

/**
 * @author Marie
 * @date Start 15/04/2021
 * @details continue a game to a winning ou equality issue
 */

struct MCTS_Node *roll_out(struct MCTS_Node *node, int color_team);

/**
 * @author Marie
 * @date Start 15/04/2021
 * @details update the value of a node to help to choose a child
 */

struct MCTS_Node *update_value(struct MCTS_Node *node, float value);
/**
 * @author Marie
 * @date Start 15/04/2021
 * @details choose a winning child
 */

struct MCTS_Node *winning_Node(struct MCTS_Node *node);

/**
 * @author Marie
 * @date Start 15/04/2021
 * @details choose a random child
 */

struct MCTS_Node *random_choose(struct MCTS_Node *node);

/**
 * @author Marie
 * @date Start 15/04/2021
 * @details choose the best child between all the child after the training
 */

struct MCTS_Node *chosen_best(struct MCTS_Node *node); 




/**
 * @author Marie
 * @date Start 15/04/2021
 * @details chosen node for the situation of just the two king are on the plate
 */

struct MCTS_Node *chose_for2kings(struct MCTS_Node *node);

/**
 * @author Marie
 * @date Start 15/04/2021
 * @details say if just the two kings are one the place
 */

int is2kings(struct MCTS_Node *node);

/**
 * @author Marie
 * @date Start 15/04/2021
 * @details are the kings on the plate ?
 */

int iskings(struct MCTS_Node *node);

#endif
