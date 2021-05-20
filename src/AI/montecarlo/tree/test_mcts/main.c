/**
 * @author Marie
 * @date Start 19/04/2021
 * @details test for the file create_childs.c/.h 
 */


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../../../../common/c/rules/plate.h"
#include "../mcts.h"

/**
 * @author Marie
 * @date Start 19/04/2021
 * @details main function to test if the list of moves for child nodes 
 */


int main()
{
  struct Piece *board = init_board();

  int color_of_IA = 1;

  struct MCTS_Node *node = create_mcts(board, color_of_IA);

  print_node_and_child(node);

  if(node->nb_child != 0)
    {
      node = &node->child[0];
      expand_childs( node, node->board); 
    } 

  free(node); 

  return 0; 
} 
