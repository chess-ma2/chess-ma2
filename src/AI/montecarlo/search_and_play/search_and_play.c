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

struct MCTS_Node *select_action(struct MCTS_Node *node, int color)
{
  node->terminus = 0;

  while(node->leaf == 0)
    {
      node = select(node);
    }

  struct MCTS_Node *final = malloc(sizeof(struct MCTS_Node));
  
  final = roll_out(node, color);
  
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

struct MCTS_Node *roll_out(struct MCTS_Node *node, int color_team)
{  
  struct MCTS_Node *final = malloc(sizeof(struct MCTS_Node));
  node = expand_childs(node, node->board);

  final = node; 

  while(final->terminus == 0)
    {

      if (!iskings(final))
	{
	  break; 
	}
      
      if (is2kings(final))
	{
	  final = chose_for2kings(final);
	  break; 
	}
      
      node = final; 

      if( final->nb_child != 0)
	{
	  final = winning_Node(node); 

	  if( final == NULL)
	    {
	      final = random_choose(node); 
	    }
	}
      final = expand_childs(final, final->board);
      
    }

  
  final = update_value(final, final->value); 
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

  if (nb_child == 1)
    {
      return 0; 
    }

  int random = (rand() % (nb_child));; 

  return &node->child[random];
}


/**
 * @author Marie
 * @date Start 15/04/2021
 * @details choose the best child between all the child after the training
 */

struct MCTS_Node *chosen_best(struct MCTS_Node *node)
{
  printf("1\n");
  struct MCTS_Node *best = malloc(sizeof(struct MCTS_Node));

  printf("1\n");
   
  best = node;

  printf("1\n");

  if( node->nb_child != 0)
    {

      printf("1\n");
       
      best = &node->child[0];

      printf("1\n");
      
      float best_value =  (node->child[0].value)/(float)(node->child[0].nb_visit);

      printf("1\n");

      float inter = 0.0;

      printf("1\n");

      for(int i = 1; i < node->nb_child ; i++)
	{

	  if(node->child[i].nb_visit != 0)
	    { 
	      inter = (node->child[i].value)/(float)(node->child[i].nb_visit);

	      printf("1\n");

	      if(inter > best_value)
		{
		  best = &node->child[i];
		  best_value = inter; 
		}
	    }
	}
    }
  
  return best; 
}

/**
 * @author Marie
 * @date Start 15/04/2021
 * @details chosen node for the situation of just the two king are on the plate
 */

struct MCTS_Node *chose_for2kings(struct MCTS_Node *node)
{

  int advers_color_team = 0;
  int AI_or_not = node->AI;
  int AI_new_child = 0; 

  if( node->color_player == 0)
    {
      advers_color_team = 1;
    }

  if(AI_or_not == 1)
    {
      AI_new_child = 0; 
    }

  if(AI_or_not == 0)
    {
      AI_new_child = 1; 
    }
  
  node->nb_child = 1;
  node->child = NULL;

  struct MCTS_Node *new_child = malloc(sizeof(struct MCTS_Node));

  new_child->leaf = 1;
  new_child->terminus = 1;
  new_child->AI = AI_new_child;
  new_child->color_player = advers_color_team;  
  new_child->nb_child = 0;
  new_child->child = NULL;
  new_child->nb_visit = 0;
  new_child->value = 0;
  new_child->father = node;
  new_child->board = node->board;
  new_child->AKing_status = NOTHING;
  new_child->x = -1;
  new_child->y = -1;
  new_child->x_des = -1;
  new_child->y_des = -1;

  node->child = new_child;
    

  return new_child; 
}


/**
 * @author Marie
 * @date Start 15/04/2021
 * @details say if just the two kings are one the place
 */

int is2kings(struct MCTS_Node *node)
{
  struct Piece *board = node->board;

   for(int y = 0; y < 8; y++)
    {
      for( int x = 0; x < 8; x++)
	{
	  if(board[y*8+x].type != KING)
	    {
	      return 0; 
	    }
	}
    }

   return 1;
}


/**
 * @author Marie
 * @date Start 15/04/2021
 * @details are the kings on the plate ?
 */

int iskings(struct MCTS_Node *node)
{

  int i = 0; 
  struct Piece *board = node->board;

   for(int y = 0; y < 8; y++)
    {
      for( int x = 0; x < 8; x++)
	{
	  if(board[y*8+x].type == KING)
	    {
	      i +=1;
	    }
	}
    }

   return i == 2;
}
