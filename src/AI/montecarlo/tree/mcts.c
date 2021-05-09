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
#include "create_childs.h"
#include "../../../common/c/rules/pieces.h"
#include "../../../common/c/rules/check_and_pat.h"


/**
 * @author Marie
 * @date Start 22/04/2021
 * @details create the tree with the first node and all the childs
 */

struct MCTS_Node *create_tree(struct Piece *board, int color) //not good
{
  struct MCTS_Node *first = malloc(sizeof(struct MCTS_Node));
  first = first_node(board , first);

  first = expand_childs(first, board, color);

  return first;
}

/**
 * @author Marie
 * @date Start 22/04/2021
 * @details create childs of the father/node with the good args
 */

struct MCTS_Node *first_node(struct Piece *board, struct MCTS_Node *first)
{
  first->leaf = 1;
  first->terminus = 0;
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

  return first; 
  
}

/**
 * @author Marie
 * @date Start 20/04/2021
 * @details create childs of the father/node with the good args
 */

struct MCTS_Node *expand_childs(struct MCTS_Node *node, struct Piece *board, int color_team)
{
  node->leaf = 0;

  int advers_color_team = 0;

  if( color_team == 0)
    {
      advers_color_team = 1;
    }
  
  struct coordonates_king *a_place_king = malloc(sizeof(struct coordonates_king));
  a_place_king = king_position(board, advers_color_team, a_place_king);

  if(pat( a_place_king->x_king , a_place_king->y_king , board))
    {
      node->AKing_status = PAT;
       node->leaf = 1;
    }

  if(check_mat( a_place_king->x_king , a_place_king->y_king , advers_color_team  , board))
    {
      node->AKing_status = CHECKMATE;
      node->leaf = 1;
      node->terminus = 1 ; 
    }

  struct tab *list_for_child = malloc(sizeof(struct tab));
  list_for_child = possible_moves(board, color_team);
  int index = list_for_child->index;

  node->nb_child = index;

  if(index == 0)
    {
      node->leaf = 1;
    }
    
  struct coordonates_moves *list_of_moves = list_for_child->list_of_moves;

  struct MCTS_Node *list = malloc( index * sizeof(struct MCTS_Node));

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

      struct Piece * board2 = calloc(8*8, sizeof(struct Piece));

      struct MCTS_Node *nb_child = malloc(sizeof(struct MCTS_Node));

      for( int i = 0; i < 64; i++)
	{
	  board2[i].type = board[i].type;
	  board2[i].color = board[i].color;
	}

      board2 = pieceMove( list_of_moves[i].x , list_of_moves[i].y , list_of_moves[i].x_des  , list_of_moves[i].y_des , board2);
      
      nb_child->leaf = 1;
      nb_child->terminus = 0;
      nb_child->AI = AI_new_child;
      nb_child->nb_child = 0;
      nb_child->child = NULL;
      nb_child->nb_visit = 0;
      nb_child->value = 0;
      nb_child->father = node;
      nb_child->board = board2;
      nb_child->AKing_status = NOTHING;
      nb_child->x = list_of_moves[i].x;
      nb_child->y = list_of_moves[i].y;
      nb_child->x_des = list_of_moves[i].x_des;
      nb_child->y_des = list_of_moves[i].y_des;

      list[i] = *nb_child;
      
    }

  node->child = list;

  return node; 
  
}

/**
 * @author Marie
 * @date Start 20/04/2021
 * @details free the tree/node
 */

void clean_mtcs(struct MCTS_Node *node)
{
  int nchild = node->nb_child;

  for( int i = 0; i < nchild ; i++)
    {
      node = &node->child[i];
      clean_mtcs(node);
      free(node); 
    }
}

/**
 * @author Marie
 * @date Start 20/04/2021
 * @details print the node's info 
 */

void print_node(struct MCTS_Node *node)
{
  printf("Feuille : %d \n", node->leaf);
  printf("Terminus : %d \n", node->terminus);
  printf("Jouer par une AI : %d \n", node->AI);
  printf("Nombre de visite : %lu \n", node->nb_visit);
  printf("Nombre de fils :  %d \n", node->nb_child); 
  printf("Valeur du noeud : %f \n", node->value);

  if(node->father == NULL)
    {
      printf("Père : Racine de l'arbre.\n");
    }

  else 
    {
      printf("Père : J'ai un père.\n");
    }
  printf("Statue du roi adverse : %d \n", (int)node->AKing_status);

  display(node->board);

  printf("---MOVE---\n");
  
  printf("x de départ : %d \n", node->x);
  printf("y de départ : %d \n", node->y);
  printf("x d'arrivée : %d \n", node->x_des);
  printf("y d'arrivée : %d \n", node->y_des);
}

/**
 * @author Marie
 * @date Start 20/04/2021
 * @details print the node and his childs 
 */

void print_node_and_child(struct MCTS_Node *node)
{
  printf("--------------------THE NODE--------------------\n");

  print_node(node);

  int nchild = node->nb_child;

  for( int i = 0; i < nchild ; i++)
    {
      printf("--------------------CHILD N°%d--------------------\n", i+1);
      print_node(&node->child[i]); 
    }
  
}


/**
 * @author Marie
 * @date Start 20/04/2021
 * @details print the mcts 
 */

void print_mcts(struct MCTS_Node *node)
{
  while(node->child != NULL)
    {
      print_node(node);
      for( int i = 0; i < node->nb_child ; i++)
	{
	  return print_mcts(&node->child[i]);
	}
    }


  
}


/**
 * @author Marie
 * @date Start 19/04/2021
 * @details print the board
 */

void display(struct Piece *board)
{
  printf("   ");
  
  for(int y = 0; y < 8; y++)
    {
      printf(" %c:   ",y+'A'); //print letter on the top of the place
    }
  printf("\n");
  for(int y = 0; y < 8; y++) 
    {
      printf("%d: ",y+1); //print coordonates next to the plate

      for(int x = 0; x < 8; x++)
	{
	  if(board[y*8+x].type != NONE)
	    {
	      printf("(%d|%d)", board[y*8+x].color,board[y*8+x].type ); //print the color and the type of the piece
	    }
	  else  //if nothing is on the place, "  " is print
	    {
	      printf("     ");
	    }
	  printf(" ");
	}
      printf("\n");
    }

}


#endif
