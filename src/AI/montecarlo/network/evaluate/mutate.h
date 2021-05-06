/**
 * @author Antoine
 * @date Start 23/04/2021
 * @details Header of file for mutate network.
 */
#ifndef AI_MONTECARLO_NETWORK_MUTATE_H
#define AI_MONTECARLO_NETWORK_MUTATE_H

#include "random.c"
#include "../structure/network.c"

/**
 * @author Antoine
 * @date Start 30/04/2021
 * @details Mutate Network with a probability
 * @param network Network need to be mutate.
 */
void network_mutate_network(Network * network);

/**
 * @author Antoine
 * @date Start 30/04/2021
 * @details Mutate Layer with a probability
 * @param layer Layer need to be mutate.
 * @param count Amount of neurons in previous layer.
 */
void network_mutate_layer(Layer * layer, unsigned int count);

/**
 * @author Antoine
 * @date Start 30/04/2021
 * @details Mutate Neuron with a probability
 * @param neuron Neuron need to be mutate.
 * @param count Amount of weights.
 */
void network_mutate_neuron(Neuron * neuron, unsigned int count);

/**
 * @author Antoine
 * @date Start 30/04/2021
 * @details Mutate double with a probability
 * @param d Double need to be mutate.
 */
void network_mutate_double(double * d);

#endif //AI_MONTECARLO_NETWORK_MUTATE_H
