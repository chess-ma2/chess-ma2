/**
 * @author Antoine
 * @date Start 16/04/2021
 * @details Source of representation of Layer in Neuronal Network.
 */
#ifndef AI_MONTECARLO_NETWORK_LAYER_C
#define AI_MONTECARLO_NETWORK_LAYER_C

#include "layer.h"

void network_layer_init(Layer *l,
                        unsigned int neurons_count,
                        unsigned int previous_count)
{
    l->neurons_count = neurons_count;
    l->neurons = malloc(sizeof(Neuron) * neurons_count);

    for (unsigned int i = 0; i < neurons_count; ++i)
        network_neuron_init((l->neurons + i), previous_count);
}

void network_layer_copy(Layer * l,
                        unsigned int previous_count,
                        Layer *reference)
{
    l->neurons_count = reference->neurons_count;
    l->neurons = malloc(sizeof(Neuron) * reference->neurons_count);

    for (unsigned int i = 0; i < reference->neurons_count; ++i)
        network_neuron_copy((l->neurons + i), previous_count,
                            (reference->neurons + i));
}

void network_layer_free(Layer * layer)
{
    for (unsigned int i = 0; i < layer->neurons_count; ++i)
        network_neuron_free((layer->neurons + i));

    free(layer);
}

void network_layer_update_output(Layer * layer,
                                 double (*activation)( double),
                                 Layer *prev_layer)
{
    for (unsigned int i = 0; i < layer->neurons_count; ++i)
        network_neuron_update_output((layer->neurons + i),
                                     activation,
                                     prev_layer->neurons_count,
                                     prev_layer->neurons);
}
#endif //AI_MONTECARLO_NETWORK_LAYER_C
