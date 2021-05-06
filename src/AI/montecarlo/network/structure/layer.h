/**
 * @author Antoine
 * @date Start 16/04/2021
 * @details Header of representation of Layer in Neuronal Network.
 */
#ifndef AI_MONTECARLO_NETWORK_LAYER_H
#define AI_MONTECARLO_NETWORK_LAYER_H

#include "neuron.c"

/**
 * @author Antoine
 * @date Start 16/04/2021
 * @details Alias for structure Layer.
 */
typedef struct Layer Layer;

/**
 * @author Antoine
 * @date Start 16/04/2021
 * @details Structure for represent a Layer in Neuronal Network.
 * @param neurons Array of neurons of internal neurons of layer
 * @param neurons_count Count of size of array neurons.
 */
struct Layer
{
    Neuron * neurons;
    unsigned int neurons_count;
};

/**
 * @author Antoine
 * @date Start 16/04/2021
 * @details Permit to init internal structure Layer with empty values
 * @param n pointer where Neuron would be init
 * @param input_count number of weight and in consequence,
 *      previous Neurons will be input.
 */
void network_layer_init(Layer *l, unsigned int neurons_count,
                        unsigned int previous_count);

/**
 * @author Antoine
 * @date Start 16/04/2021
 * @details Permit to copy a Layer in a new memory space
 * @param l pointer where Neuron would be init
 * @param previous_count number of weight and in consequence,
 *      previous Neurons will be input.
 * @param reference Original layer where values will be come.
 */
void network_layer_copy(Layer * l, unsigned int previous_count,
                        Layer *reference);

/**
 * @author Antoine
 * @date Start 16/04/2021
 * @details Permit to free in memory a Layer from system.
 * @param layer Layer target to be free.
 */
void network_layer_free(Layer * layer);

/**
 * @author Antoine
 * @date Start 16/04/2021
 * @details Make compute of output for Neurons
 *      from previous layer on this Layer
 * @param layer Layer will be has own output updated.
 * @param activation Function of activation
 *      with double in param and return a double.
 * @param prev_layer Previous layer of neurons.
 */
void network_layer_update_output(Layer * layer,
                                 double (*activation)( double),
                                 Layer *prev_layer);
#endif //AI_MONTECARLO_NETWORK_LAYER_H
