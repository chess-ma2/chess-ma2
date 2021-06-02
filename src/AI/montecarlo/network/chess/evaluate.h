/**
 * @author Antoine
 * @date Start 02/05/2021
 * @details Header of file who is algorithm of evolution specialized for chess.
 */
#ifndef AI_MONTECARLO_NETWORK_CHESS_EVALUATE_H
#define AI_MONTECARLO_NETWORK_CHESS_EVALUATE_H

#include "../evaluate/evaluate.c"
#include "../evaluate/random.c"
#include "../structure/network.c"
#include "../structure/activation.c"
#include "../../tree/mcts.h"

typedef struct MCTS_Node MCTS_Node;

NEvaluate *network_chess_dual(Network* network1, Network* network2);

Network *network_chess_init_table(unsigned int count);

MCTS_Node *find_child(MCTS_Node * node, Network * network);

int network_chess_get_weight(MCTS_Node * node, Network * network);

void network_chess_load_input(MCTS_Node *node, Network * network);


#endif //AI_MONTECARLO_NETWORK_CHESS_EVALUATE_H
