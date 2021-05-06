/**
 * @author Antoine
 * @date 24/04/2021
 * @details Header of file for Activation Neuron
 */
#ifndef AI_MONTECARLO_NETWORK_ACTIVATION_H
#define AI_MONTECARLO_NETWORK_ACTIVATION_H

/*
 * TODO ?
 * Sigmoide
 * Tangente hyperbolique
 * Identitée
 * Gausienne
 * ...
 */

/**
 * @author Antoine
 * @date 24/04/2021
 * @details Sigmoid Function of Neuron Activation
 *      Formula: f(x) = 1/(1+e^(-x))
 * @param input Input value of activation
 * @return Output value get by math function.
 */
double network_activation_sigmoid(double input);

//Usage: void network_network_update_output(Network * network, unsigned int (*activation)(unsigned double));
#endif //AI_MONTECARLO_NETWORK_ACTIVATION_H
