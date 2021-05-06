/**
 * @author Antoine
 * @date Start 26/04/2021
 * @details Source of file who is algorithm of evolution specialized for XOR.
 */
#ifndef AI_MONTECARLO_NETWORK_XOR_EVALUATE_C
#define AI_MONTECARLO_NETWORK_XOR_EVALUATE_C

#include "evaluate.h"

//Dual for xor is tests 4 tests, each 25% of accuracy
NEvaluate *network_xor_dual(Network* network1, Network* network2)
{
    //Todo useless here for xor
    // but for chess a multi thread to generate max games
    NEvaluate *nEvaluate = malloc(sizeof(NEvaluate));
    nEvaluate->accuracy1 = 0;
    nEvaluate->accuracy2 = 0;
    nEvaluate->won = 0;

    //0 | 0 --> 0
    (network1->input->neurons)->output = 0;
    (network1->input->neurons+1)->output = 0;

    (network2->input->neurons)->output = 0;
    (network2->input->neurons+1)->output = 0;

    network_network_update_output(network1, network_activation_sigmoid);
    network_network_update_output(network2, network_activation_sigmoid);
    if (network1->output->neurons->output < 0.5)
        nEvaluate->accuracy1 += 25;
    if (network2->output->neurons->output < 0.5)
        nEvaluate->accuracy2 += 25;

    //printf("Evaluate 0|0: %f %f\n", network1->output->neurons->output ,
    // network2->output->neurons->output);

    //0 | 1 --> 1
    (network1->input->neurons+1)->output = 1;

    (network2->input->neurons+1)->output = 1;

    network_network_update_output(network1, network_activation_sigmoid);
    network_network_update_output(network2, network_activation_sigmoid);
    if (network1->output->neurons->output > 0.5)
        nEvaluate->accuracy1 += 25;
    if (network2->output->neurons->output > 0.5)
        nEvaluate->accuracy2 += 25;

    //1 | 1 --> 1
    (network1->input->neurons)->output = 1;

    (network2->input->neurons)->output = 1;

    network_network_update_output(network1, network_activation_sigmoid);
    network_network_update_output(network2, network_activation_sigmoid);
    if (network1->output->neurons->output > 0.5)
        nEvaluate->accuracy1 += 25;
    if (network2->output->neurons->output > 0.5)
        nEvaluate->accuracy2 += 25;

    //1 | 0 --> 0
    (network1->input->neurons+1)->output = 0;

    (network2->input->neurons+1)->output = 0;

    network_network_update_output(network1, network_activation_sigmoid);
    network_network_update_output(network2, network_activation_sigmoid);
    if (network1->output->neurons->output < 0.5)
        nEvaluate->accuracy1 += 25;
    if (network2->output->neurons->output < 0.5)
        nEvaluate->accuracy2 += 25;

    //Result
    if (nEvaluate->accuracy1 > nEvaluate->accuracy2)
        nEvaluate->won = 1;
    if (nEvaluate->accuracy1 < nEvaluate->accuracy2)
        nEvaluate->won = 2;

    return nEvaluate;
}


Network *network_xor_init_table(unsigned int count)
{
    Network * table = malloc(sizeof(Network)* count);

    for (unsigned int i = 0; i < count; ++i)
    {
        network_network_init((table+i), 1, 2, 2, 1);
        network_random_fill((table+i), network_random_uniform_gen, -1, 1);
    }

    return table;
}


#endif //AI_MONTECARLO_NETWORK_XOR_EVALUATE_C
