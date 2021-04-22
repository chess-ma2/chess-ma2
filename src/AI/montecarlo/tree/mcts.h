/**
 * @author Marie
 * @date Start 15/04/2021
 * @details .h - Contain bases, informations and structures for MCTS
 */

#ifndef MCTS_H
#define MCTS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/**
 * @author Marie
 * @date Start 15/04/2021
 * @details structures of a node
 */

enum King_status
{
 NOTHING = 0,
 CHECK,
 PAT,
 CHECK_AND_MAT,
}


/**
 * @author Marie
 * @date Start 15/04/2021
 * @details structures of a node
 */


struct MCTS_Node
{
  int leaf;
  
  int terminus;
  
  int AI;

  int nb_child; 

  MCTS_Node * child;
  
  unsigned long nb_visit;
  
  float value;
  
  MCTS_Node *father;

  Piece board;

  King_status AKing_status;

  int x;
  int y;
  int x_des;
  int y_des;

  
};

/**
 * @author Marie
 * @date Start 22/04/2021
 * @details create the tree with the first node and all the childs
 */

MCTS_Node *create_tree(Piece *board, int color) //not good

/**
 * @author Marie
 * @date Start 22/04/2021
 * @details create the fisrt node with the good args
 */

MCTS_Node *first_node(Piece *board, MCTS_Node *first)

/**
 * @author Marie
 * @date Start 20/04/2021
 * @details create childs of the father/node with the good args
 */

void expand_childs(MCTS_Node *node, Piece *board, int color_team);

/**
 * @author Marie
 * @date Start 20/04/2021
 * @details free the tree/node
 */

void clean_mtcs(MCTS_Node *node);

/**
 * @author Marie
 * @date Start 20/04/2021
 * @details print the tree/node
 */

void print_mtcs(MCTS_Node *node);


#endif
