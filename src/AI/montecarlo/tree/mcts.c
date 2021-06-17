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
#include "check_and_pat_for_AI.h"


/**
 * @author Marie
 * @date Start 22/04/2021
 * @details create the tree with the first node and all the childs
 */

struct MCTS_Node *create_mcts(struct Piece *board, int color) //not good
{
  struct MCTS_Node *first = malloc(sizeof(struct MCTS_Node));
  first = first_node(board , first, color);

  first = expand_childs(first, board);

  return first;
}

/**
 * @author Marie
 * @date Start 22/04/2021
 * @details special move function for AI
 */

struct Piece *pieceMove_AI(int x, int y, int des_x, int des_y, struct Piece *board)
{ 
  struct Piece piece = board[y*8+x];
  struct Piece piece_des = board[des_y*8+des_x];

      
  board[des_y*8 + des_x] = piece ;//move the piece
  board[y*8+ x].type = NONE;
  board[y*8+ x].color = 0;

  if( piece_des.type != NONE ) //catch an adverse piece
    {
      piece_des.type = NONE; //the adverse piece disappear 
    }
      
  return board; //return the finally board
}


/**
 * @author Marie
 * @date Start 22/04/2021
 * @details create childs of the father/node with the good args
 */

struct MCTS_Node *first_node(struct Piece *board, struct MCTS_Node *first, int color)
{
    
  first->leaf = 1;
  first->terminus = 0;
  first->AI = 0;
  first->color_player = color; 
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

struct MCTS_Node *expand_childs(struct MCTS_Node *node, struct Piece *board)
{
  node->leaf = 0;

  int advers_color_team = 0;

  if( node->color_player == 0)
    {
      advers_color_team = 1;
    }
  
  struct coordonates_king *a_place_king = malloc(sizeof(struct coordonates_king));
  a_place_king = king_position(board, advers_color_team, a_place_king);

  struct coordonates_king *my_place_king = malloc(sizeof(struct coordonates_king));
  my_place_king = king_position(board, node->color_player, my_place_king);
  

  if(pat_AI( a_place_king->x_king , a_place_king->y_king , board))
    {
      node->AKing_status = PAT;
      node->terminus = 1 ;
      node->leaf = 1;
    }

  if(check_mat_AI(a_place_king->x_king , a_place_king->y_king , advers_color_team  , board))
    {
      node->AKing_status = CHECKMATE;
      node->leaf = 1;
      node->terminus = 1 ;
      node->value = 1;
    }

  if(pat_AI( my_place_king->x_king , my_place_king->y_king , board))
    {
      node->terminus = 1 ;
      node->leaf = 1;
    }

  if(check_mat_AI(my_place_king->x_king , my_place_king->y_king , node->color_player , board))
    {
      node->leaf = 1;
      node->terminus = 1 ;
    }

  struct tab *list_for_child = malloc(sizeof(struct tab));
  list_for_child = possible_moves(board, advers_color_team);
  int index = list_for_child->index;

  node->nb_child = index;

  if(index == 0)
    {
      node->leaf = 1;
    }
    
  struct coordonates_moves *list_of_moves = list_for_child->list_of_moves;

  struct MCTS_Node *list = calloc( index , sizeof(struct MCTS_Node));

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
      struct MCTS_Node *child = malloc(sizeof(struct MCTS_Node));
      
      child->leaf = 1;
      child->terminus = 0;
      child->AI = AI_new_child;
      child->color_player = advers_color_team; 
      child->nb_child = 0;
      child->child = NULL;
      child->nb_visit = 0;
      child->value = 0;
      child->father = node;
      child->board = list_of_moves[i].board;
      child->AKing_status = NOTHING;
      child->x = list_of_moves[i].x;
      child->y = list_of_moves[i].y;
      child->x_des = list_of_moves[i].x_des;
      child->y_des = list_of_moves[i].y_des;

      list[i] = *child;
      
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

  if( node != NULL)
    {
      int nchild = node->nb_child;
     
      
      for( int i = 0; i < nchild ; i++)
	{
	 
	  clean_mtcs( &node->child[i]);
	  free(&node->child[i]);
	 
	}

      

      free(node->board);
 
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
  printf("Couleur du joueur : %d \n", node->color_player);
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
