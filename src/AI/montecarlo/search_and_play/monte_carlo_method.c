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
 * @details the function to call the IA in the game
 */

struct special_tuple *the_monte_carlo(struct special_tuple *tree_and_coordonates, struct Piece *board, int color_team, struct MCTS_Node *tree)
{

  printf("tableau de la partie\n");
  display(board);
  printf("\n\n");
  printf("tableau de la racine de l'arbre\n");
  display(tree->board);
  printf("\n\n");

  tree = expand_childs(tree, board);

  tree = select_good_node(board, tree);

  printf("tableau de la racine de l'arbre après la selection\n");
  display(tree->board);
  printf("\n\n");

  tree = update_tree(tree->board, 0, tree);

  tree = chosen_best(tree);

  printf("coup choisi \n");
  display(tree->board);
  printf("\n\n");

  struct coordonates_moves *coordonates = malloc(sizeof(struct coordonates_moves)); 
  coordonates = coordonates_by_mc(coordonates, tree);

  tree_and_coordonates->tree = tree;
  tree_and_coordonates->coordonates = coordonates; 


  return tree_and_coordonates; 

}


/**
 * @author Marie
 * @date Start 27/04/2021
 * @details fonction which create the tree, training, and find the "best" child
 */

struct MCTS_Node *create_tree(struct Piece *board, int color_team, struct MCTS_Node *node)
{
  
  node = first_node(board, node, color_team);
  node = expand_childs(node, board);

  for(int i = 0 ; i < 2000 ; i++)
    {
      node = select_action(node, color_team);
      
    }

  return node;
}


/**
 * @author Marie
 * @date Start 27/04/2021
 * @details fonction which update the tree
 */

struct MCTS_Node *update_tree(struct Piece *board, int color_team, struct MCTS_Node *node)
{

  for(int i = 0 ; i < 500 ; i++)
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

struct coordonates_moves *coordonates_by_mc(struct coordonates_moves *chosen_coordonates, struct MCTS_Node *node)
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


int board_equels(struct Piece *board, struct Piece *board2)
{
    for( int i = 0; i < 64; i++)
      {
	if (board2[i].type != board[i].type || board2[i].color != board[i].color)
	  {
	    return 0;
	  }
      }

    return 1; 
}

struct MCTS_Node *select_good_node(struct Piece *board, struct MCTS_Node *node)
{

  printf("selection commence");

  print_node(node); 
  
  for( int i = 0; i < node->nb_child; i++)
    {
      display(node->child[i].board);
      
      if (board_equels(node->child[i].board, board) == 1)
	{
	  
	  display(node->child[i].board);
	  node->child[i].father = NULL; 
	  return &node->child[i]; 
	}
    }

  return node;
}
