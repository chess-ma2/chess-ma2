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
    nEvaluate->won = 0;

    //Dual

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

MCTS_Node * network_chess_find_node(MCTS_Node * node, Network * network)
{
    if (node == NULL || network == NULL || node->nb_child < 1)
	return NULL;

    int max = 0;
    int *weights = malloc(sizeof(node->nb_child));
    for (int i = 0; i < node->nb_child; i++)
    {
	int v = network_chess_get_weight((node->child + i), network);
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
    return (node->child + i);
}

int network_chess_get_weight(MCTS_Node * node, Network * network)
{
    network_chess_load_input(node, network);
    network_network_update_output(network, network_activation_sigmoid);

    int result = 0;
    for (int i = 0; i < network->output->neurons_count; i++)
    {
	if (network->output->neurons->output > 0.5)
	    result += 1;
    }
    return result;
}

void network_chess_load_input(MCTS_Node *node, Network * network)
{
    for(int i = 0; i < 64; i++)
    {
	Piece p = node->board[i];
	for (int j = 0; j < 8; j++)
	    (network->input->neurons + (j*64 + i))->output = (p.type == j);
    }
    (network->input->neurons + 896)->output = 0;//TODO ROCK
    (network->input->neurons + 897)->output = 0;//TODO ROCK
    (network->input->neurons + 898)->output = 0;//TODO ROCK
    (network->input->neurons + 899)->output = 0;//TODO ROCK
    (network->input->neurons + 900)->output = (node->AI);
}
#endif //AI_MONTECARLO_NETWORK_CHESS_EVALUATE_C
