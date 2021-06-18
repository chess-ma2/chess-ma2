/**
 * @author Antoine
 * @date Start 16/05/2021
 * @details Contain function to manipulate MCTS_NODE
 * @note This work is inspired from Marie Work
 *  and adapted for network compatibility
 */

//Safety guard
#ifndef AI_MONTECARLO_TREE_MCTS_EXPLORE_C
#define AI_MONTECARLO_TREE_MCTS_EXPLORE_C

#include "mctsn_explore.h"

void network_mctsn_generate_child(MCTSN_Node *node, Network * network)
{

    //printf("Gen child\n");
    if (node == NULL || node->child_nb != 0)
        return;

    struct tabm *moves = possible_moves(node->board, node->team);
  //  printf("MGen child\n");

    node->child_nb = moves->index;

    MCTSN_Node ** father = malloc(sizeof (MCTSN_Node*)*node->child_nb);
 //   printf("FGen child\n");

    for (int i = 0; i < node->child_nb; ++i)
    {
   //     printf("SUBC FGen child\n");

        MCTSN_Node * child = malloc(sizeof (MCTSN_Node));
    //    printf("SUBA FGen child\n");

        child->status = MCTSN_STATUS_NONE;
        child->father = node;

        child->board = (moves->list_of_moves+i)->board;
        child->team = !node->team;
        child->height = 1+ node->height;
        child->win = 0;
        child->draw = 0;
        child->loose = 0;
        child->play = 0;

        child->child_nb = 0;
        if (network == NULL)
            child->node_network_value = 1;
        else
        {
            child->node_network_value =
                    network_chess_get_weight(node, network);
       //     printf("Value found for board: %i\n", child->node_network_value);
        }
        child->child = NULL;
        *(father+i) = child;
    }
    node->child = father;
   // printf("BFGen child\n");

    free(moves);
   // printf("End gen %i\n", node->child_nb);
}

PATH_EXPLORE * network_mctsn_generate_path(MCTSN_Node * node, Network * network,
                                 unsigned long paths, int original_color)
{
   // printf("Height explore: %i\n", node->height);
    if (node == NULL)
        return NULL;

    PATH_EXPLORE * pa = malloc(sizeof (PATH_EXPLORE));
    pa->draw = 0;
    pa->win = 0;
    pa->loose = 0;
    pa->leaf = 0;

    if (node->height > 50)
    {
        pa->draw = 1;
        pa->leaf = 1;
        node->status = MCTSN_STATUS_FORCED_DRAW;
        return pa;
    }

    int xbking = -1;
    int ybking = -1;
    int xwking = -1;
    int ywjing = -1;

    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            if (node->board[y*8+x].type == KING)
            {
                if (node->board[y*8+x].color == BLACK)
                {
                    xbking = x;
                    ybking = y;
                }
                else
                {
                    xwking = x;
                    ywjing = y;
                }
            }
        }
    }
    if (check_mat(xbking, ybking, 0, node->board) || xbking == -1)
    {
        //printf("White Victory\n");
       // sleep(3);
        pa->win = (1 == original_color ? 1 : 0);
        pa->loose = (1 == original_color ? 0 : 1);
        pa->leaf = 1;
        node->status = (1 == original_color ? MCTSN_STATUS_FORCED_WIN : MCTSN_STATUS_FORCED_LOOSE);
        return pa;
    }
    else if (check_mat(xwking, ywjing, 1, node->board) || xwking == -1)
    {
       // printf("Black Victory\n");
      //  sleep(3);
        pa->win = (0 == original_color ? 1 : 0);
        pa->loose = (0 == original_color ? 0 : 1);
        pa->leaf = 1;
        node->status = (0 == original_color ? MCTSN_STATUS_FORCED_WIN : MCTSN_STATUS_FORCED_LOOSE);
        return pa;
    }
  /*  else if (check_mat(xbking, ybking, 0, node->board) == 1
    || check_mat(xwking, ywjing, 1, node->board) == 1
    || check_mat(xbking, ybking, 1, node->board) == 1
       || check_mat(xwking, ywjing, 0, node->board) == 1)
    {
        printf("Found checkmate! %i %i %i %i\n",
               check_mat(xbking, ybking, 0, node->board),
               check_mat(xwking, ywjing, 1, node->board),
               check_mat(xbking, ybking, 1, node->board),
               check_mat(xwking, ywjing, 0, node->board));


        display(node->father->board);

        display(node->board);
        exit(5);
        return NULL;
    }
*/

    if (node->child == NULL)
        network_mctsn_generate_child(node, network);


    if (node->child_nb == 0)
    {
        //Pat
        pa->draw = 1;
        pa->leaf = 1;
        node->status = MCTSN_STATUS_FORCED_DRAW;
        return pa;
    }


    unsigned long * explo = malloc(sizeof(long) * node->child_nb);
    int sum = 0;
    for (int i = 0; i < node->child_nb; ++i) {
        *(explo + i) = 0;
        MCTSN_Node *child = *(node->child+i);
        sum += child->node_network_value;
    }


    while (paths > 0)
    {
        int r = rand()%sum;
        int isum = 0;
        int i = node->child_nb;

        while ( i > 0 && isum+r < sum)
        {
            MCTSN_Node *child = *(node->child+i-1);
            isum += child->node_network_value;
            i -= 1;
        }
        *(explo+i) += 1;
        paths -= 1;

    }
   // printf("Launch sub %i\n", node->height);
    for (int i = 0; i < node->child_nb; ++i) {
        if (*(explo+i) != 0) {
       //     printf("Launch subexplore, h:%i hi:%i  i:%i\n", node->height, (*(node->child + i))->height, i);
            PATH_EXPLORE * pan = network_mctsn_generate_path(*(node->child+i), network,
                                        *(explo + i), original_color);
            pa->draw += pan->draw;
            pa->win += pan->win;
            pa->loose += pan->loose;
            pa->leaf += pan->leaf;
            free(pan);
        }
    }
    if (node->height > 2)
        clear_mctsn_child(node);

    node->win += pa->win;
    node->draw += pa->draw;
    node->loose += pa->loose;
    node->play += pa->leaf;
    free(explo);
    return pa;
}

struct Piece * network_mctsn_choice(struct Piece * board, Network * network, int color)
{
    MCTSN_Node * father = malloc(sizeof (MCTSN_Node));
    father->status = MCTSN_STATUS_NONE;
    father->father = NULL;

    father->board = board;
    father->team = color;
    father->height = 0;

    father->win = 0;
    father->draw = 0;
    father->loose = 0;
    father->play = 0;

    father->child_nb = 0;
    father->node_network_value = 0;
    father->child = NULL;

    network_mctsn_generate_path(father, network, 1500, color);

    if (father->child_nb == 0 || father->child == NULL)
    {
    //    printf("No child found!\n");
        return NULL;
    }

    struct Piece * best = NULL;
    float ratio = 0;
    for (int i = 0; i < father->child_nb; ++i) {
        MCTSN_Node *child = *(father->child +i);
       // printf("Data: %lu/%lu/%lu = %lu\n",
      //         child->win, child->draw, child->loose, child->play);

        if (child->play != 0
        && ((float )child->win) / ((float)child->play) > ratio)
        {
            ratio = ((float )child->win) / ((float)child->play) ;
            best = child->board;
         //   printf("Found better %f at %i\n", ratio, i);
         //   print_mctsn_node("", 2, father);
         //   display(best);
        }
    }
   // printf("Best Ratio is %f\n", ratio);
   // clear_mctsn_child(father);
    return best;

}
//End safety guard
#endif
