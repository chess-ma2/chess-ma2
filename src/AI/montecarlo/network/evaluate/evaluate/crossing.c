/**
 * @author Antoine
 * @date Start 23/04/2021
 * @details Source of file for cross network.
 */
#ifndef AI_MONTECARLO_NETWORK_CROSS_C
#define AI_MONTECARLO_NETWORK_CROSS_C

#include "crossing.h"

void network_cross_network(Network * network, Network * father1, Network * father2)
{
    network_cross_layer(network->hidden, network->input->neurons_count,
                        father1->hidden, father2->hidden);

    for (int i = 1; i < network->hidden_count; ++i)
    {
        network_cross_layer(network->hidden + i,
                             (network->hidden + i - 1)->neurons_count,
                             father1->hidden + i, father2->hidden + i);
    }
    network_cross_layer(network->output,
                         (network->hidden +
                         network->hidden_count - 1)->neurons_count,
                         father1->output, father2->output);
}

void network_cross_layer(Layer * layer, unsigned int count,
                          Layer * father1, Layer * father2)
{
    for (unsigned int i = 0; i < layer->neurons_count; ++i)
    {
        network_cross_neuron(layer->neurons + i, count,
                             father1->neurons + i, father2->neurons +i);
    }
}

void network_cross_neuron(Neuron * neuron, unsigned int count,
                          Neuron * father1, Neuron * father2)
{
    for (unsigned int i = 0; i < count; ++i)
    {
        network_cross_double(neuron->weight + i,
                             father1->weight + i,
                             father2->weight + i);
    }
    network_cross_double(&neuron->bias, &father1->bias, &father2->bias);

}

void network_cross_double(double * d, double * d1, double * d2)
{
    if (rand()%2 >= 1)
        *d = *d1;
    else
        *d = *d2;
}
#endif //AI_MONTECARLO_NETWORK_MUTATE_C
