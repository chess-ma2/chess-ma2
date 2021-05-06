/**
 * @author Antoine
 * @date Start 26/04/2021
 * @details Header of file who is algorithm of evolution specialized for XOR.
 */
#ifndef AI_MONTECARLO_NETWORK_XOR_EVALUATE_H
#define AI_MONTECARLO_NETWORK_XOR_EVALUATE_H

#include "../evaluate/evaluate.c"
#include "../evaluate/random.c"
#include "../structure/network.c"
#include "../structure/activation.c"


//Dual for xor is tests 4 tests, each 25% of accuracy
/**
 * @author Antoine
 * @date Start 26/04/2021
 * @details Test two XOR network by tests and find the best of two.
 *      For XOR is 4 tests, 25% each.
 * @param network1 Network 1 tested.
 * @param network2 Network 2 tested.
 * @return NEvaluate structure who is best, in equality return N°1
 */
NEvaluate *network_xor_dual(Network* network1, Network* network2);

/**
 * @author Antoine
 * @date Start 27/04/2021
 * @details Initialize an array of network
 *      to init a population of XOR network.
 * @param count Size of target array will be return.
 * @return An array of network sized for XOR.
 */
Network *network_xor_init_table(unsigned int count);

#endif //AI_MONTECARLO_NETWORK_XOR_EVALUATE_H
