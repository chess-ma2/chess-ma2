/**
 * @author Marie
 * @date Start 15/04/2021
 * @details .c - Contain bases, informations and structures for MCTS
 */

#ifndef MCTS_C
#define MCTS_C

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mcts.h"
#include "../../../common/c/rules/pieces.h"
#include "../../../common/c/rules/check_and_pat.h"


/**
 * @author Marie
 * @date Start 22/04/2021
 * @details create the tree with the first node and all the childs
 */

MCTS_Node *create_tree(Piece *board, int color) //not good
{
  MCTS_Node *first = malloc(sizeof(struct MCTS_Node));

  expand_childs(MCTS_Node *node, Piece *board, int color_team); 
  
}

/**
 * @author Marie
 * @date Start 22/04/2021
 * @details create childs of the father/node with the good args
 */

MCTS_Node *first_node(Piece *board, MCTS_Node *first)
{
  first->leaf = 1;
  first->terminus = 1;
  first->AI = 0;
  first->nb_child = 0;
  first->child = NULL;
  first->nb_visit = 0;
  first->value = 0;
  first->father = NULL;
  first->board = board;
  first->AKing_status = NOTHING;
  first->x = -1;
  first->y = -1;
  first->x_des = -1;
  first->y_des = -1;
  
}

/**
 * @author Marie
 * @date Start 20/04/2021
 * @details create childs of the father/node with the good args
 */

void expand_childs(MCTS_Node *node, Piece *board, int color_team)
{
  node->leaf = 0;

  int advers_color_team = 0;

  if( color_team == 0)
    {
      advers_color_team = 1;
    }
  
  struct coordonates_king *a_place_king = malloc(sizeof(struct coordonates_king));
  a_place_king = king_position(board, advers_color_team, kingplace);

  if(pat( a_place_king->x_king , a_place_king->y_king , board))
    {
      node->AKing_status = PAT;
       node->leaf = 1;
    }

  if(check_mat( a_place_king->x_king , a_place_king->y_king , advers_color_team  , board))
    {
      node->AKing_status = CHECK_AND_MAT;
      node->leaf = 1;
    }

  struct tab *list_for_child = malloc(sizeof(struct tab));
  list_of_child = possible_moves(board, color_team);
  int index = list_of_child->index;

  node->nb_child = index;

  if(index == 0)
    {
      node->terminus = 1;
      node->leaf = 1;
    }
    
  struct coordonates_moves *list_of_moves = list_of_child->list_of_moves;

  MCTS_Node *list = malloc(sizeof(struct MCTS_Node));

  int AI_or_not = node->AI;
  int AI_new_child = 0; 

  if(AI_or_not == 1)
   {
     AI_new_child = 0; 
   }

   if(AI_or_not == 0)
   {
     AI_new_child = 1; 
   }

  for(int i = 0; i < index; i++)
    {

      Piece *board2 = malloc(sizeof(struct Piece));

      for( int i = 0; i < 64; i++)
	{
	  board2[i].type = board[i].type;
	  board2[i].color = board[i].color;
	}

      board2 = pieceMove( list_of_moves[i]->x , list_of_moves[i]->y , list_of_moves[i]->x_des  , list_of_moves[i]->y_des , board2);
	
      MCTS_Node *nb_child = malloc(sizeof(struct MCTS_Node));
      nb_child->leaf = 1;
      nb_child->terminus = 1;
      nb_child->AI = AI_new_child;
      nb_child->nb_child = 0;
      nb_child->child = NULL;
      nb_child->nb_visit = 0;
      nb_child->value = 0;
      nb_child->father = node;
      nb_child->board = board2;
      nb_child->AKing_status = NOTHING;
      nb_child->x = list_of_moves[i]->x;
      nb_child->y = list_of_moves[i]->y;
      nb_child->x_des = list_of_moves[i]->x_des;
      nb_child->y_des = list_of_moves[i]->y_des;

      list[i]-> nb_child; 
      
    }

  node->child = list;
  
}

/**
 * @author Marie
 * @date Start 20/04/2021
 * @details free the tree/node
 */

void clean_mtcs(MCTS_Node *node)
{
  //TODO
}

/**
 * @author Marie
 * @date Start 20/04/2021
 * @details print the tree/node
 */

void print_mtcs(MCTS_Node *node)
{
    //TODO
}
