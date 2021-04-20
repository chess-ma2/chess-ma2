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

/**
 * @author Marie
 * @date Start 15/04/2021
 * @details go down to a leaf of the tree
 */

void select_action(MCTS_Node node)
{
  node.terminus = 1;

  while(node.leaf == 0)
    {
      node = select(node); 
    }
  roll_out(node); 
}

/**
 * @author Marie
 * @date Start 15/04/2021
 * @details Select the "best" child with the exploration and the value
 */

MCTS_Node select(MCTS_Node node)
{
  MCTS_Node selec_Node = malloc(sizeof( struct MCTS_Node));
  float bestValue = -100000;
  float c = sqrtf(2.0);

  for( int i = 0; i < node->nb_child ; i++)
    {
      MCTS_Node child = malloc(sizeof(struct MCTS_Node));

      if( child->nb_visit != 0)
	{
	  child->value = (child.value/child.nb_visit) + c * (sqrtf((logf(node->nb_visit + 1))/child.nb_visit)); 
	}
      else 
	{
	  child->value = (Rand() % 1) +  c * (sqrtf(logf(node->nb_visit + 1))); 
	}

      if(child.value >= bestValue)
	{
	  selec_Node = child;
	  bestValue = child.value; 
	}
    }
  child.father = node;
  return child; 
}

/**
 * @author Marie
 * @date Start 15/04/2021
 * @details continue a game to a winning ou equality issue
 */

void roll_out(MCTS_Node node)
{
  MCTS_Node child = malloc(sizeof(struct MCTS_Node)); 

  if( node.terminus == 0)
    {
      child = expand_sons(node);

      if( child != NULL)
	{
	  child = random_choose(node); 
	}

      if(child.terminus == 0)
	{
	  roll_out(child); 
	}
      else
	{
	  update_value(child, child->value); 
	}
    }

}

/**
 * @author Marie
 * @date Start 15/04/2021
 * @details update the value of a node to help to choose a child
 */

void update_value(MCTS_Node node, float value)
{
  node.nb_visit += 1;
  node.sommeGains = sommeGains + valeur;

  if( node.father != NULL)
    {
      update_value(node->father, value*0.9); 
    }
}

/**
 * @author Marie
 * @date Start 15/04/2021
 * @details choose a winning child
 */

MCTS_Node winning_Node(MCTS_Node node)
{
  for( int i = 0; i < node->nb_child ; i++)
    {
      if(node.child[i].AKing_status == CHECK_AND_MAT)
	{
	  return child; 
	}
    }
  return NULL; 
}

/**
 * @author Marie
 * @date Start 15/04/2021
 * @details choose a random child
 */

MCTS_Node random_choose(MCTS_Node node)
{
  int nb_child = node->nb_child;

  int random = (Rand() % (nb_child-1));

  return node.child[random];
}


