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
#include "../tree/mcts.c"
#include "search_and_play.c"


struct special_tuple
{

  struct MCTS_Node *tree;
  struct coordonates_moves *coordonates;
  
};


/**
 * @author Marie
 * @date Start 16/05/2021
 * @details main function to call the IA
 */

struct special_tuple *the_monte_carlo(struct special_tuple *tree_and_coordonates, struct Piece *board, int color_team, struct MCTS_Node *tree);

/**
 * @author Marie
 * @date Start 27/04/2021
 * @details fonction which create the tree, training, and find the "best" child
 */

struct MCTS_Node *create_treem(struct Piece *board, int color_team, struct MCTS_Node *node);

/**
 * @author Marie
 * @date Start 27/04/2021
 * @details fonction which update the tree
 */

struct MCTS_Node *update_tree(struct Piece *board, int color_team, struct MCTS_Node *node);

/**
 * @author Marie
 * @date Start 27/04/2021
 * @details return the coordonates of the best child
 */

struct coordonates_moves *coordonates_by_mc(struct coordonates_moves *chosen_coordonates, struct MCTS_Node *node);

/**
 * @author Marie
 * @date Start 27/04/2021
 * @details return the coordonates of the best child
 */

int board_equels(struct Piece *board, struct Piece *board2);

struct MCTS_Node *select_good_node(struct Piece *board, struct MCTS_Node *node);

#endif
