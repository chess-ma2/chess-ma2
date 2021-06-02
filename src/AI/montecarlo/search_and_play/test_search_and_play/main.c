/**
 * @author Marie
 * @date Start 29/04/2021
 * @details test for see if the AI is working
 */


#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "../../../../common/c/rules/plate.h"
#include "../../../../common/c/rules/check_and_pat.h"
#include "../../tree/create_childs.h"
#include "../monte_carlo_method.h"
#include "../../tree/mcts.h"





/**
 * @author Marie
 * @date Start 19/04/2021
 * @details main function to test my beautiful montecarlo
 */


int main()
{
  //-----------------------------------necessary variables-----------------------------------

  srand(time(NULL));
  
  struct Piece *board = init_board(); //positionate de pieces one the piece cf funtion on plate.c

  //---------------------------------------------------------------------------------------------------------

  display(board); //display the first board with any movements

  //-------------------------------------START OF THE GAME---------------------------------------------------
  
  printf("\n\n");
  
  struct MCTS_Node *node = malloc(sizeof(struct MCTS_Node));
  node = first_node(board, node, 1);
  node = expand_childs(node, board);
  node = select_action(node, 1);

  print_node_and_child(node); 
  
  free(board);

  return 0; //end of the main function
   
} 
