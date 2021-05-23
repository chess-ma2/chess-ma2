/**
 * @author Marie
 * @date Start 15/04/2021
 * @details Contain functions for the AI
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "../tree/mcts.h"
#include "../tree/create_childs.h"
#include "monte_carlo_method.h"

/**
 * @author Marie
 * @date Start 27/04/2021
 * @details fonction which create the tree, training, and find the "best" child
 */

struct MCTS_Node *create_tree(struct Piece *board, int color_team, struct MCTS_Node *node)
{
  node = first_node(board, node, color_team);
  node = expand_childs(node, board);

  for(int i = 0 ; i < 5000 ; i++)
    {
      node = select_action(node, color_team);
      
    }

  return node;
}

/**
 * @author Marie
 * @date Start 27/04/2021
 * @details return the coordonates of the best child
 */

struct coordonates_moves *coordonates_by_mc(struct Piece *board, int color_team, struct coordonates_moves *chosen_coordonates, struct MCTS_Node *node)
{
 

  chosen_coordonates->x = node->x;
  chosen_coordonates->y = node->y;
  chosen_coordonates->x_des = node->x_des;
  chosen_coordonates->y_des = node->y_des;

  return chosen_coordonates; 
  
}



/**
 * @author Marie
 * @date Start 27/04/2021
 * @details return the coordonates of the best child
 */

struct MCTS_Node *select_good_node(struct Piece *board, struct MCTS_Node *node)
{
  
  for( int i = 0; i < node->nb_child; i++)
    {
      if (node->child[i].board == board)
	{
	  return &node->child[i]; 
	}
    }

  return node;
}
