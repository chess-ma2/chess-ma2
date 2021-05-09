/**
 * @author Antoine
 * @date Start 23/04/2021
 * @details Source of file for mutate network.
 */
#ifndef AI_MONTECARLO_NETWORK_MUTATE_C
#define AI_MONTECARLO_NETWORK_MUTATE_C

#include "mutate.h"

void network_mutate_network(Network * network)
{
    network_mutate_layer(network->hidden, network->input->neurons_count);

    for (int i = 1; i < network->hidden_count; ++i)
    {
        network_mutate_layer(network->hidden + i,
                             (network->hidden + i - 1)->neurons_count);
    }
    network_mutate_layer(network->output,
                         (network->hidden +
                         network->hidden_count - 1)->neurons_count);
}

void network_mutate_layer(Layer * layer, unsigned int count)
{
    for (unsigned int i = 0; i < layer->neurons_count; ++i)
    {
        network_mutate_neuron(layer->neurons + i, count);
    }
}

void network_mutate_neuron(Neuron * neuron, unsigned int count)
{
    for (unsigned int i = 0; i < count; ++i)
    {
        network_mutate_double(neuron->weight + i);
    }
    network_mutate_double(&neuron->bias);

}

void network_mutate_double(double * d)
{
    if (rand()%2 >= 1)
        return;
    *d += network_random_gaussian_gen(0, 1/3);
}
#endif //AI_MONTECARLO_NETWORK_MUTATE_C
