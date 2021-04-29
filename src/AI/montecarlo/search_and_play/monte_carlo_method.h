/**
 * @author Marie
 * @date Start 15/04/2021
 * @details Contain functions for the AI
 */

#ifndef MONTE_CARLO_METHOD_H
#define MONTE_CARLO_METHOD_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "../tree/mcts.h"
#include "search_and_play.h"


/**
 * @author Marie
 * @date Start 27/04/2021
 * @details fonction which create the tree, training, and find the "best" child
 */

struct MCTS_Node *find_the_child(struct Piece *board, int color_team); 

/**
 * @author Marie
 * @date Start 27/04/2021
 * @details return the coordonates of the best child
 */

struct coordonates_moves *coordonates_by_mc(struct Piece *board, int color_team, struct coordonates_moves *chosen_coordonates); 

#endif