/**
 * @author Antoine
 * @date Start 25/04/2021
 * @details Header of file who is algorithm of evolution
 */
#ifndef AI_MONTECARLO_NETWORK_EVALUATE_C
#define AI_MONTECARLO_NETWORK_EVALUATE_C

#include "evaluate.h"

//pop_input need to be %2==0 or one net train for nothing
Network * network_train_turn(Network * network,
                             NEvaluate* (*eval) (Network*, Network*),
                             unsigned int turn, unsigned int pop_input,
                             PEvaluate pe)
{
    #ifdef DEBUG_AE
    printf("Turn: %u\n", turn);
    #endif

    if (turn == 0)
        return network;
    network = network_train_turn(network, eval, turn - 1, pop_input, pe);

    //Dual
    //TODO MULTI THREAD HERE
    for (int i = 0; i+1 < pop_input; i+=2)
    {
        NEvaluate *result = (*eval)(network+i, network+i+1);
        //If 0 or 1, stay net 1 in place, else replace net1 by net 2
        if (result->won == 2)
            *(network+i) = *(network+i+1);

        #ifdef DEBUG_AE
        printf("%u - %i Dual: %i VS %i\n", turn,
               i, result->accuracy1, result->accuracy1);
        #endif
    }

    //Todo add rotate in position of network for upgrade training performance
    int sum = pe.cross + pe.mutate + pe.new;
    //Generate Kids
    for (int i = 0; i+1 < pop_input; i+=2)
    {
        int r = rand()%sum;
        if (r < pe.new)
        {
            network_network_init((network+(i+3)%pop_input),
                                 network->hidden_count,
                                 network->input->neurons_count,
                                 network->hidden->neurons_count,
                                 network->output->neurons_count);
            network_random_fill((network+(i+3)%pop_input),
                                network_random_uniform_gen, -1, 1);
        }
        else if (r < pe.new + pe.mutate)
        {
            network_network_copy(network+i,
                                 network+(i+3)%pop_input);
            network_mutate_network(network+(i+3)%pop_input);
        }

        //(network+i+2) = network_train_mutate(network+i); Todo crossover here
        //(network+i+3) = network_train_random(network+i);
        /*
        network_network_init((network+i+1), 1, 2, 2, 1);
        network_random_fill((network+i+1), network_random_uniform_gen, -1, 1);
        network_network_init((network+i+2), 1, 2, 2, 1);
        network_random_fill((network+i+2), network_random_uniform_gen, -1, 1);
        network_network_init((network+i+3), 1, 2, 2, 1);
        network_random_fill((network+i+3), network_random_uniform_gen, -1, 1);
        */
    }

    #ifdef DEBUG_AE
    printf("Turn: %u is finish!\n", turn);
    #endif

    return network;
}


#endif //AI_MONTECARLO_NETWORK_EVALUATE_C
