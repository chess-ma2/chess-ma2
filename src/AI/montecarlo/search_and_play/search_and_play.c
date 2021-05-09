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
#include "search_and_play.h"

/**
 * @author Marie
 * @date Start 15/04/2021
 * @details go down to a leaf of the tree
 */

struct MCTS_Node *select_action(struct MCTS_Node *node, struct Piece *board, int color)
{
  node->terminus = 0;

  while(node->leaf == 0)
    {
      node = select(node);
    }

  printf("je suis choisi\n");

  print_node(node);

  printf("stop\n");

  struct MCTS_Node *final = malloc(sizeof(struct MCTS_Node));

  printf("stop\n");
  
  final = roll_out(node, board, color);

  printf("stop\n");
  
  return final; 
}

/**
 * @author Marie
 * @date Start 15/04/2021
 * @details Select the "best" child with the exploration and the value
 */

struct MCTS_Node *select(struct MCTS_Node *node)
{
  struct MCTS_Node *select_Node = malloc(sizeof( struct MCTS_Node));
  float bestValue = -100000;
  float c = sqrtf(2.0);

  for( int i = 0; i < node->nb_child ; i++)
    {

      if( node->child[i].nb_visit != 0)
	{
	  node->child[i].value = (node->child[i].value/node->child[i].nb_visit) + c * (sqrtf((logf(node->nb_visit + 1))/node->child[i].nb_visit)); 
	}
      else if (node->child[i].nb_visit == 0)
	{
	  float nb = 0;
	  nb =  (float)rand() / (float)RAND_MAX;
	  node->child[i].value = nb +  c * (sqrtf(logf(node->nb_visit + 1)));
	}

      if(node->child->value >= bestValue)
	{
	  select_Node = &node->child[i];
	  bestValue = node->child[i].value; 
	}
    }

  select_Node->father = node;
  return select_Node; 
}

/**
 * @author Marie
 * @date Start 15/04/2021
 * @details continue a game to a winning ou equality issue
 */

struct MCTS_Node *roll_out(struct MCTS_Node *node, struct Piece *board, int color_team)
{

  print_node(node);
  
  struct MCTS_Node *final = malloc(sizeof(struct MCTS_Node));

  node = expand_childs(node, board, color_team);

  print_node_and_child(node); 

  while(node->terminus == 0)
    {
      

      printf("coucou\n");
      
      node = winning_Node(node); 

      if( node == NULL)
	{
	  node = random_choose(node); 
	}

      //print_node(node); 
	  
    }
  
  final = update_value(node, node->value); 
  return final; 

}

/**
 * @author Marie
 * @date Start 15/04/2021
 * @details update the value of a node to help to choose a child
 */

struct MCTS_Node *update_value(struct MCTS_Node *node, float value)
{
  while( node->father != NULL)
    {
      node->nb_visit += 1;
      node->value = node->value + value;
      value = value*0.9; 
      node = node->father; 
    }

  return node; 
}

/**
 * @author Marie
 * @date Start 15/04/2021
 * @details choose a winning child
 */

struct MCTS_Node *winning_Node(struct MCTS_Node *node)
{
  for( int i = 0; i < node->nb_child ; i++)
    {
      if(node->child[i].AKing_status == CHECKMATE)
	{
	  print_node(&node->child[i]);
	  return &node->child[i]; 
	}
    }
  return NULL; 
}

/**
 * @author Marie
 * @date Start 15/04/2021
 * @details choose a random child
 */

struct MCTS_Node *random_choose(struct MCTS_Node *node)
{
  int nb_child = node->nb_child;

  int random = (rand() % (nb_child-1));

  print_node(&node->child[random]);

  return &node->child[random];
}


/**
 * @author Marie
 * @date Start 15/04/2021
 * @details choose the best child between all the child after the training
 */

struct MCTS_Node *chosen_best(struct MCTS_Node *node)
{
  struct MCTS_Node *best = malloc(sizeof(struct MCTS_Node));

  if( node->nb_child != 0)
    {

      best = &node->child[0];
      
      float best_value =  (node->child[0].value)/(float)(node->child[0].nb_visit);

      float inter = 0.0;

      for(int i = 1; i < node->nb_child ; i++)
	{
	  inter = (node->child[i].value)/(float)(node->child[i].nb_visit);

	  if(inter > best_value)
	    {
	      best = &node->child[i];
	      best_value = inter; 
	    }
	}
    }

  print_node(best);
  
  return best; 
}
