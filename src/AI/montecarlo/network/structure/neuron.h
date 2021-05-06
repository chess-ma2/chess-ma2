/**
 * @author Antoine
 * @date Start 15/04/2021
 * @details Header file of neuron contain header function
 *      for structure neuron and structure of Neuron.
 */
#ifndef AI_MONTECARLO_NETWORK_NEURON_H
#define AI_MONTECARLO_NETWORK_NEURON_H

#include <stdlib.h>

/**
 * @author Antoine
 * @date Start 15/04/2021
 * @details Alias for structure Neuron.
 */
typedef struct Neuron Neuron;

/**
 * @author Antoine
 * @date Start 15/04/2021
 * @details Structure of Neuron for his general representation
 * @param weight array of double for each weight of compute output value
 * @param bias bias for the compute value
 * @param output where is store latest value compute by neuron,
 *      where is never compute or just import, can be = 0
 */
struct Neuron
{
    double *weight;
    double bias;
    double output;
};

/**
 * @author Antoine
 * @date Start 15/04/2021
 * @details Permit to init internal structure Neuron with empty values
 * @param n pointer where Neuron would be init
 * @param input_count number of weight and in consequence,
 *      previous Neurons will be input.
 */
void network_neuron_init(Neuron * n, unsigned int input_count);

/**
 * @author Antoine
 * @date Start 15/04/2021
 * @details Permit to copy a Neuron in a new memory space
 * @param n pointer where Neuron would be init
 * @param input_count number of weight and in consequence,
 *      previous Neurons will be input.
 * @param reference Original neurons where values will be come.
 */
void network_neuron_copy(Neuron * n, unsigned int input_count,
                         Neuron *reference);

/**
 * @author Antoine
 * @date Start 15/04/2021
 * @details Permit to free in memory a Neuron from system.
 * @param neuron Neuron target to be free.
 */
void network_neuron_free(Neuron * neuron);

/**
 * @author Antoine
 * @date Start 15/04/2021
 * @details Make compute of output for Neuron
 *      from previous neuron on this Neuron
 * @param neuron Neuron will be has own output updated.
 * @param activation Function of activation
 *      with double in param and return a double.
 * @param input_count Number of neuron wil be give in input.
 * @param prev_layer Array of neurons input for make compute.
 */
void network_neuron_update_output(Neuron * neuron,
                                  double (*activation)(double),
                                  unsigned int input_count,
                                  Neuron *prev_layer);

#endif //AI_MONTECARLO_NETWORK_NEURON_H
