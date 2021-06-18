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
#include "../tree/mctsn.c"
#include "../tree/mctsn_explore.h"


/**
 * @author Antoine
 * @date 6/05/2021
 * @details Alias for MCTS_Node Structure
 */
typedef struct MCTS_Node MCTS_Node;

/**
 * @author Antoine
 * @date 3/05/2021
 * @details Function to make dual for train between network
 * @param network1 First network
 * @param network2 Second network
 * @return Result of dual
 */
NEvaluate *network_chess_dual(Network* network1, Network* network2);

/**
 * @author Antoine
 * @date Start 4/05/2021
 * @details Initialize array of network
 * @param count Size of array
 * @return Array of network
 */
Network *network_chess_init_table(unsigned int count);

/**
 * @author Antoine
 * @date Start 06/05/2021
 * @details Get a child with network
 * @param node Node father to find
 * @param network network where is applied
 * @return Child choice
 */
MCTSN_Node *find_child(MCTSN_Node * node, Network * network);

/**
 * @author Antoine
 * @date Start 07/05/2021
 * @details Get weight for a node
 * @param node node evaluate
 * @param network network applied
 * @return weight found
 */
unsigned int network_chess_get_weight(MCTSN_Node * node, Network * network);

/**
 * @author Antoine
 * @date Start 08/05/2021
 * @param node for board details
 * @param network network where input is load
 */
void network_chess_load_input(MCTSN_Node *node, Network * network);


#endif //AI_MONTECARLO_NETWORK_CHESS_EVALUATE_H
