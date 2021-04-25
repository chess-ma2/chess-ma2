/**
 * @author Marie
 * @date Start 15/04/2021
 * @details Contain functions for the AI
 */

#ifndef SEARCH_AND_PLAY_H
#define SEARCH_AND_PLAY_H

#include <stdlib.h>
#include <stdio.h>
#include <math.c>
#include <string.h>
#include "../tree/mcts.h"

/**
 * @author Marie
 * @date Start 15/04/2021
 * @details go down to a leaf of the tree
 */

void select_action(MCTS_Node *node);

/**
 * @author Marie
 * @date Start 15/04/2021
 * @details Select the "best" child with the exploration and the value
 */

MCTS_Node *select(MCTS_Node *node);

/**
 * @author Marie
 * @date Start 15/04/2021
 * @details continue a game to a winning ou equality issue
 */

void roll_out(MCTS_Node *node);

/**
 * @author Marie
 * @date Start 15/04/2021
 * @details update the value of a node to help to choose a child
 */

void update_value(MCTS_Node *node, float value);

/**
 * @author Marie
 * @date Start 15/04/2021
 * @details choose a winning child
 */

MCTS_Node *winning_Node(MCTS_Node *node);

/**
 * @author Marie
 * @date Start 15/04/2021
 * @details choose a random child
 */

MCTS_Node *random_choose(MCTS_Node *node); 

#endif
