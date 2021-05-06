/**
 * @author Antoine
 * @date Start 22/04/2021
 * @details Header of representation of Network in Neuronal Network.
 */
 #ifndef AI_MONTECARLO_NETWORK_NETWORK_H
#define AI_MONTECARLO_NETWORK_NETWORK_H

#include "layer.c"

/**
 * @author Antoine
 * @date Start 22/04/2021
 * @details Alias for structure Network.
 */
typedef struct Network Network;

/**
 * @author Antoine
 * @date Start 22/04/2021
 * @details Structure for represent a Network in Neuronal Network.
 * @param input Layer Input of NN.
 * @param hidden Array of hidden layers.
 * @param output Layer Output of NN.
 * @param hidden_count size of array of hidden layers.
 */
struct Network
{
    Layer * input;
    Layer * hidden;
    Layer * output;
    unsigned char hidden_count;
};

/**
 * @author Antoine
 * @date Start 22/04/2021
 * @details Permit to init internal structure Network with empty values.
 * @param network pointer where Network would be init.
 * @param hidden_count number of hidden layer full connected.
 * @param input_size Size of Input Layer.
 * @param hidden_size Size of Hidden Layer.
 * @param output_size Size of Output Layer.
 */
void network_network_init(Network * network, unsigned char hidden_count,
                               unsigned int input_size,
                               unsigned int hidden_size,
                               unsigned int output_size);

/**
 * @author Antoine
 * @date Start 22/04/2021
 * @details Permit to copy a Network in a new memory space
 * @param reference Original network where values will be come.
 * @param network Network lcoation where is copy
 */
void network_network_copy(Network *reference, Network *network);

/**
 * @author Antoine
 * @date Start 22/04/2021
 * @details Permit to free in memory a Network from system.
 * @param network Network target to be free.
 */
void network_network_free(Network * network);

/**
 * @author Antoine
 * @date Start 22/04/2021
 * @details Make compute of output for Neurons
 *      NOTE: Input is not updated here, he need to be change before.
 * @param network Network will be has own output updated.
 * @param activation Function of activation
 *      with double in param and return a double.
 */
void network_network_update_output(Network * network,
                                   double (*activation)(double));

#endif //AI_MONTECARLO_NETWORK_NETWORK_H
