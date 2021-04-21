/**
 * @author Marie
 * @date Start 19/04/2021
 * @details test for the file create_childs.c/.h 
 */


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../../../../common/c/rules/plate.h"
#include "../create_childs.h"


/**
 * @author Marie
 * @date Start 19/04/2021
 * @details print function to print elt of a list 
 */

void print_tab(struct coordonates_moves *tab, int size)
{

  printf("nb coups = %d \n", size);
  
    for (int i = 0 ; i < size ; i++)
    {
      printf("( %d, %d, %d, %d )\n", tab[i].x , tab[i].y , tab[i].x_des , tab[i].y_des);
    }
}


/**
 * @author Marie
 * @date Start 19/04/2021
 * @details main function to test if the list of moves for child nodes 
 */


int main()
{
  struct Piece *board = init_board();

  struct tab *all_moves = possible_moves(board, 1);

  print_tab(all_moves->list_of_moves ,all_moves->index); 
} 
