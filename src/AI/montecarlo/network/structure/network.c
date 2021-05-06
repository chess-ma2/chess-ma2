/**
 * @author Antoine
 * @date Start 22/04/2021
 * @details Source of representation of Network in Neuronal Network.
 */
#ifndef AI_MONTECARLO_NETWORK_NETWORK_C
#define AI_MONTECARLO_NETWORK_NETWORK_C

#include "network.h"

void network_network_init(Network * network, unsigned char hidden_count,
                               unsigned int input_size,
                               unsigned int hidden_size,
                               unsigned int output_size)
{
    network->hidden_count = hidden_count;
    network->input = malloc(sizeof(Layer));
    network->hidden = malloc(sizeof(Layer) * hidden_count);
    network->output = malloc(sizeof(Layer));

    network_layer_init(network->input, input_size, 0);

    //Has hidden layer
    if (hidden_count > 0)
    {
        //Special case, number of input
        network_layer_init(network->hidden, hidden_size, input_size);

        //Global case (Note: fully connected)
        for (int i = 1; i < hidden_count; i++)
            network_layer_init((network->hidden + i),
                               hidden_size, hidden_size);

        network_layer_init(network->output, output_size, hidden_size);
    }
    else
    {
        network_layer_init(network->output, output_size, input_size);
    }
}

void network_network_copy(Network *reference, Network *network)
{
    network->hidden_count = reference->hidden_count;
    network->input = malloc(sizeof(Layer));
    network->hidden = malloc(sizeof(Layer) * reference->hidden_count);
    network->output = malloc(sizeof(Layer));

    network_layer_copy(network->input, 0, reference->input);

    //Has hidden layer
    if (network->hidden_count > 0)
    {
        //Special case, number of input
        network_layer_copy(network->hidden, network->input->neurons_count,
                           reference->hidden);

        //Global case (Note: fully connected)
        for (int i = 1; i < network->hidden_count; i++)
            network_layer_copy((network->hidden + i),
                               (reference->hidden + i - 1)->neurons_count,
                               (reference->hidden + i));


        network_layer_copy(network->output,
                           (network->hidden +
                           network->hidden_count - 1)->neurons_count,
                           reference->output);

    }
    else
    {
        network_layer_copy(network->output, network->input->neurons_count,
                           reference->output);
    }
}

void network_network_free(Network * network)
{
    network_layer_free(network->input);
    for (unsigned char i = 0; i < network->hidden_count; ++i)
        network_layer_free((network->hidden + i));
    network_layer_free(network->output);

    free(network);
}

//Note: Input is not update
void network_network_update_output(Network * network,
                                   double (*activation)(double))
{
    if (network->hidden_count > 0)
    {
        network_layer_update_output(network->hidden,
                                    activation,
                                    network->input);

        for (unsigned char i = 1; i < network->hidden_count; i++)
            network_layer_update_output((network->hidden + i),
                                        activation,
                                        (network->hidden + i - 1));

        network_layer_update_output(network->output,
                                    activation,
                                    (network->hidden
                                    + network->hidden_count - 1));
    }
    else
    {
        network_layer_update_output(network->output,
                                    activation,
                                    network->input);
    }
}
#endif //AI_MONTECARLO_NETWORK_NETWORK_C
