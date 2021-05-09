/**
 * @author Antoine
 * @date Start 15/04/2021
 * @details Source file of neuron contain function for structure neuron.
 */
#ifndef AI_MONTECARLO_NETWORK_NEURON_C
#define AI_MONTECARLO_NETWORK_NEURON_C

#include "neuron.h"


void network_neuron_init(Neuron * n, unsigned int input_count)
{
    n->weight = calloc(sizeof(double), input_count);
    n->bias = 0;
    n->output = 0;
}

void network_neuron_copy(Neuron * n, unsigned int input_count,
                         Neuron *reference)
{
    n->bias = reference->bias;
    n->output = reference->output;
    n->weight = malloc(sizeof(double) * input_count);

    for (int i = 0; i < input_count; i++)
        *(n->weight + i) = *(reference->weight + i);

}

void network_neuron_free(Neuron * neuron)
{
    free(neuron);
}

void network_neuron_update_output(Neuron * neuron,
                                  double (*activation)(double),
                                  unsigned int input_count,
                                  Neuron *prev_layer)
{
    double sum = neuron->bias;

    for (int i = 0; i < input_count; i++)
        sum += (prev_layer+i)->output * (*(neuron->weight + i));
    //*(neuron->weight + i) * (*(prev_layer + i)->output);

    neuron->output = (*activation) (sum);
}

#endif //AI_MONTECARLO_NETWORK_NEURON_C
