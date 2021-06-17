/**
 * @author Antoine
 * @date Start 13/04/2021
 * @details Contain function to self test mctsn
 */

//Safety guard
#ifndef AI_MONTECARLO_TREE_MCTSN_TEST_C
#define AI_MONTECARLO_TREE_MCTSN_TEST_C

#define AUTO_PROMOTION
#include "mctsn.c"
//#include "../../../../common/c/rules/rules.c"
#include "../../../../common/c/rules/pieces.c"
#include "../../../../common/c/rules/check_and_pat.c"
#include "../../../../common/c/rules/plate.c"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#include "mctsn_explore.c"

void gen_clear()
{
    MCTSN_Node * father = malloc(sizeof (MCTSN_Node));
    father->status = MCTSN_STATUS_NONE;
    father->father = NULL;

    father->board = init_board();
    father->team = 1;
    father->height = 0;

    father->win = 0;
    father->draw = 0;
    father->loose = 0;
    father->play = 0;

    father->child_nb = 0;
    father->node_network_value = 0;
    father->child = NULL;

    network_mctsn_generate_child(father, NULL);

    print_mctsn_node("", 2, father);

    clear_mctsn_child(father);
    print_mctsn_node("", 2, father);
}

void export_network_output(Network * network)
{
    printf("Start export...\n");
    char * str = malloc(sizeof(char) * 200000);
    int i = 0;
    Layer *layer = (network->input);
    for (int j = 0; j < layer->neurons_count; ++j) {
        i += sprintf((str+i), "%f;", (layer->neurons + j)->output);
    }
    i+= sprintf((str+i), "\n");

    for (int k = 0; k < network->hidden_count; ++k) {
        Layer *layer = (network->hidden+k);
        for (int j = 0; j < layer->neurons_count; ++j) {
            i += sprintf((str+i), "%f;", (layer->neurons + j)->output);
        }
        i+= sprintf((str+i), "\n");
    }
    Layer *ou = (network->output);
    for (int j = 0; j < ou->neurons_count; ++j) {
        i += sprintf((str+i), "%f;", (ou->neurons + j)->output);
    }
    printf("File export...\n");

    *(str+i+1) = 0;
    FILE *fp = fopen("/home/antoine/network.csv", "w+");
    fprintf(fp, "%s", str);
    fclose(fp);
}
void gen_network()
{
    Network * network = network_chess_init_table(1);

    MCTSN_Node * father = malloc(sizeof (MCTSN_Node));
    father->status = MCTSN_STATUS_NONE;
    father->father = NULL;

    father->board = init_board();
    father->team = 1;
    father->height = 0;

    father->win = 0;
    father->draw = 0;
    father->loose = 0;
    father->play = 0;

    father->child_nb = 0;
    father->node_network_value = 0;
    father->child = NULL;

    network_mctsn_generate_child(father, network);

    print_mctsn_node("", 2, father);

    export_network_output(network);
}

void single_path()
{

    //Network * network = network_chess_init_table(1);

    MCTSN_Node * father = malloc(sizeof (MCTSN_Node));
    father->status = MCTSN_STATUS_NONE;
    father->father = NULL;

    father->board = init_board();
    father->team = 1;
    father->height = 0;

    father->win = 0;
    father->draw = 0;
    father->loose = 0;
    father->play = 0;

    father->child_nb = 0;
    father->node_network_value = 0;
    father->child = NULL;

    unsigned long paths = 5000;
    PATH_EXPLORE *pa = network_mctsn_generate_path(father, NULL, paths, 0);

    print_mctsn_node("", 2, father);

    printf("Result: %lu %lu %lu = %lu for exploration  \n",
           pa->win, pa->draw, pa->loose, pa->leaf);

    printf("Node clear: %lu\n",clear_mctsn_child(father));

  //  sleep(10);

    pa = network_mctsn_generate_path(father, NULL, paths, 0);

    printf("Result: %lu %lu %lu = %lu for exploration  \n",
           pa->win, pa->draw, pa->loose, pa->leaf );

  //  sleep(10);

}

void choice_try()
{
    display(network_mctsn_choice(init_board(), NULL, 0));
}

void heavy_try()
{
    struct Piece * board = init_board();
    for (int i = 0; i < 20; ++i) {
        printf("Tour %i par %i\n", i, (i+1)%2);
        display(board);
        board =network_mctsn_choice(board, NULL, (i+1)%2);
    }
    printf("Tour %i par %i\n", 20, (20+1)%2);
    display(board);
}

int main(){
    //srand(time(NULL));

    //single_path();
    //choice_try();
    heavy_try();
}
#endif

