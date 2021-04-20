/**
 * @author Marie
 * @date Start 15/04/2021
 * @details Contain bases, informations and structures for MCTS
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
};

void expand_sons(MCTS_Node node); 


#endif
