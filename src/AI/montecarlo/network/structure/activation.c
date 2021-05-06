/**
 * @author Antoine
 * @date 24/04/2021
 * @details Source of file for Activation Neuron
 */
#ifndef AI_MONTECARLO_NETWORK_ACTIVATION_H
#define AI_MONTECARLO_NETWORK_ACTIVATION_H

#include "activation.h"
#include <math.h>

//f(x) = 1/(1+e^(-x))
double network_activation_sigmoid(double input)
{
    return 1/(1+exp(-1*input));
}

#endif //AI_MONTECARLO_NETWORK_ACTIVATION_H
