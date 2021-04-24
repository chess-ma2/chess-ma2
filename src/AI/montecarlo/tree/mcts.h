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
#include "../../../common/c/rules/plate.h"
#include "../../../common/c/rules/pieces.h"


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

  struct MCTS_Node * child;
  
  unsigned long nb_visit;
  
  float value;
  
  struct MCTS_Node *father;

  struct Piece *board;

  enum king_status AKing_status;

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

struct MCTS_Node *create_tree(Piece *board, int color); //not good

/**
 * @author Marie
 * @date Start 22/04/2021
 * @details create the fisrt node with the good args
 */

struct MCTS_Node *first_node(Piece *board, struct MCTS_Node *first);

/**
 * @author Marie
 * @date Start 20/04/2021
 * @details create childs of the father/node with the good args
 */

struct MCTS_Node *expand_childs(struct MCTS_Node *node, Piece *board, int color_team);

/**
 * @author Marie
 * @date Start 20/04/2021
 * @details free the tree/node
 */

void clean_mtcs(struct MCTS_Node *node);

/**
 * @author Marie
 * @date Start 20/04/2021
 * @details print the node's info 
 */

void print_node(struct MCTS_Node *node);

/**
 * @author Marie
 * @date Start 20/04/2021
 * @details print the node and his childs
 */

void print_mtcs(struct MCTS_Node *node);



/**
 * @author Marie
 * @date Start 19/04/2021
 * @details print the board
 */

void display(struct Piece *board);

#endif
