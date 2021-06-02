/**
 * @author Antoine
 * @date Start 23/04/2021
 * @details Header of file for cross network.
 */
#ifndef AI_MONTECARLO_NETWORK_CROSS_H
#define AI_MONTECARLO_NETWORK_CROSS_H

#include "random.c"
#include "../structure/network.c"

/**
 * @author Antoine
 * @date Start 30/04/2021
 * @details Cross Network with a probability
 * @param network Network need to be cross.
 * @param father1 Father 1 to be cross.
 * @param father2 Father 2 to be cross.
 */
void network_cross_network(Network * network,
                           Network * father1, Network * father2);

/**
 * @author Antoine
 * @date Start 30/04/2021
 * @details Mutate Layer with a probability
 * @param layer Layer need to be cross.
 * @param count Amount of neurons in previous layer.
 * @param father1 Father 1 to be cross.
 * @param father2 Father 2 to be cross.
 */
void network_cross_layer(Layer * layer, unsigned int count,
                         Layer * father1, Layer * father2);

/**
 * @author Antoine
 * @date Start 30/04/2021
 * @details Cross Neuron with a probability
 * @param neuron Neuron need to be cross.
 * @param count Amount of weights.
 * @param father1 Father 1 to be cross.
 * @param father2 Father 2 to be cross.
 */
void network_cross_neuron(Neuron * neuron, unsigned int count,
                          Neuron * father1, Neuron * father2);

/**
 * @author Antoine
 * @date Start 30/04/2021
 * @details cross double with a probability
 * @param d Double need to be cross.
 * @param father1 Father 1 to be cross.
 * @param father2 Father 2 to be cross.
 */
void network_cross_double(double * d, double * father1, double * father2);

#endif //AI_MONTECARLO_NETWORK_CROSS_H
