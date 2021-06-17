/**
 * @author Antoine
 * @date Start 02/05/2021
 * @details Source of file who is algorithm of evolution specialized for chess.
 */
#ifndef AI_MONTECARLO_NETWORK_CHESS_EVALUATE_C
#define AI_MONTECARLO_NETWORK_CHESS_EVALUATE_C

#include "evaluate.h"

NEvaluate *network_chess_dual(Network* network1, Network* network2)
{
    NEvaluate *nEvaluate = malloc(sizeof(NEvaluate));
    nEvaluate->accuracy1 = 0;
    nEvaluate->accuracy2 = 0;
    nEvaluate->won = 1;

    //Dual
    for (int i = 0; i < 100; ++i) {
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

        MCTSN_Node * father2 = malloc(sizeof (MCTSN_Node));
        father2->status = MCTSN_STATUS_NONE;
        father2->father = NULL;

        father2->board = init_board();
        father2->team = 1;
        father2->height = 0;

        father2->win = 0;
        father2->draw = 0;
        father2->loose = 0;
        father2->play = 0;

        father2->child_nb = 0;
        father2->node_network_value = 0;
        father2->child = NULL;

        unsigned long paths = 500;
        PATH_EXPLORE *pa = network_mctsn_generate_path(father, network1, paths, 0);
        PATH_EXPLORE *pa2 = network_mctsn_generate_path(father2, network2, paths, 0);
        if (pa->win > pa2->win)
            nEvaluate->accuracy1 += 1;
        else
            nEvaluate->accuracy2 += 1;

        free(father);
        free(father2);
        free(pa);
        free(pa2);
    }
    if (nEvaluate->accuracy2 > nEvaluate->accuracy1)
        nEvaluate->won = 2;
    return nEvaluate;
}

Network *network_chess_init_table(unsigned int count)
{
    Network * network = malloc(sizeof(Network) * count);
    for (int i = 0; i < count; i++)
    {
        network_network_init((network+i), 150, 901, 100, 100);
        network_random_fill((network+i), network_random_uniform_gen, -1, 1);
    }

    return network;
}

MCTSN_Node * network_chess_find_node(MCTSN_Node * node, Network * network)
{
    if (node == NULL || network == NULL || node->child_nb < 1)
	    return NULL;

    int max = 0;
    int *weights = malloc(sizeof(node->child_nb));
    for (int i = 0; i < node->child_nb; i++)
    {
        int v = network_chess_get_weight(*(node->child + i), network);
        max += v;
        *(weights + i) = v;
    }

    int r = network_random_uniform_gen(0,max);
    int i = -1;
    while (0 <= r)
    {
        r -= *(weights + i);
            i += 1;
    }

    free(weights);
    return *(node->child + i);
}

unsigned int network_chess_get_weight(MCTSN_Node * node, Network * network)
{
    network_chess_load_input(node, network);
    network_network_update_output(network, network_activation_sigmoid);


    unsigned int result = 1;
    for (int i = 0; i < network->output->neurons_count; i++)
    {
     //   printf("Neuron: %i - %f\n", result, (network->output->neurons+i)->output);
        if ((network->output->neurons+i)->output > 0.5)
            result += 1;
    }
    return result;
}

void network_chess_load_input(MCTSN_Node *node, Network * network)
{
    for(int i = 0; i < 64; i++)
    {
        Piece p = node->board[i];
        for (int j = 0; j < 8; j++)
            (network->input->neurons + (j*64 + i))->output = (p.type == j);
    }
    (network->input->neurons + 900)->output = (node->team);
}
#endif //AI_MONTECARLO_NETWORK_CHESS_EVALUATE_C
