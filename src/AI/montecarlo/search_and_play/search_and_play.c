/**
 * @author Marie
 * @date Start 15/04/2021
 * @details Contain functions for the AI
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
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
  
  node = roll_out(node, color);
  
  return node; 
}

/**
 * @author Marie
 * @date Start 15/04/2021
 * @details Select the "best" child with the exploration and the value
 */

struct MCTS_Node *select(struct MCTS_Node *node)
{
  srand(time(NULL));
  
  struct MCTS_Node *select_Node = malloc(sizeof( struct MCTS_Node));
  float bestValue = -100000;
  float c = sqrtf(2.0);

  for( int i = 0; i < node->nb_child ; i++)
    {

      if( node->child[i].nb_visit != 0)
	{
	  node->child[i].value = (node->child[i].value/node->child[i].nb_visit) + (sqrtf(node->nb_visit + 1)/node->child[i].nb_visit) ;
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

  int i = 0; 

  while(final->terminus == 0)
    {
      i += 1; 

      if (!iskings(final))
	{
	  final = chose_for2kings(final);
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

      if( final->nb_child == 0)
	{
	  final = chose_for2kings(final);
	  break; 
	}

      if( final->father->board == final->board)
	{
	  final = chose_for2kings(final);
	  break; 
	}

      if( i == 400)
	{
	  final = chose_for2kings(final);
	  break; 
	}
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

  printf("%d\n" , node->nb_child); 

  struct MCTS_Node *best = malloc(sizeof(struct MCTS_Node));
   
  best = node;

  if( node->nb_child != 0)
    {
       
      best = &node->child[0];
      
      float best_value = 0.00;

      printf("%f\n" , best_value);

      float inter = 0.0;

      for(int i = 0; i < node->nb_child ; i++)
	{

	  if(node->child[i].nb_visit != 0)
	    { 
	      inter = (node->child[i].value)/(float)(node->child[i].nb_visit);

	      printf("%d\n", i);
	      printf("%f\n" , node->child[i].value);
	      printf("%f\n" , (float)node->child[i].nb_visit);
	      printf("%f\n" , inter);
	      
	      if(inter > best_value)
		{
		  printf("%d\n" , i); 
		  best = &node->child[i];
		  best_value = inter; 
		}
	    }
	}
    }

  else
    {
      return chose_for2kings(node);
    }
    
  best->father = NULL; 
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
	  if(board[y*8+x].type != KING || board[y*8+x].type != NONE )
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
