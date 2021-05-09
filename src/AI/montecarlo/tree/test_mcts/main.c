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

  struct MCTS_Node *node = create_tree(board, color_of_IA);

  print_node_and_child(node);

  free(node); 

  return 0; 
} 
