/**
 * @author Antoine
 * @date Start 25/04/2021
 * @details Header of file who is algorithm of evolution
 */
#ifndef AI_MONTECARLO_NETWORK_EVALUATE_H
#define AI_MONTECARLO_NETWORK_EVALUATE_H

#include "../structure/network.c"
#include "random.c"
#include "mutate.c"
#include "crossing.c"


#include <stdlib.h>
#include <stdio.h>

/**
 * @author Antoine
 * @date Start 27/04/2021
 * @details Alias for structure NEvaluate
 */
typedef struct NEvaluate NEvaluate;

/**
 * @author Antoine
 * @date Start 26/04/2021
 * @details Structure who contain output of dual
 *      for genetic evaluation algorithm.
 * @param won who has win,
 *      0 Equality or NAN
 *      1 Win by Bot 1
 *      2 Win By Bot 2
 * @param accuracy1 Accuracy of bot 1 (over 100)
 * @param accuracy2 Accuracy of bot 2 (over 100)
 * @note accuracy1 + accuracy2 is between 0 and 200.
 */
struct NEvaluate
{
    char won;//0 = NO WINNER SELECTED, 1 n1, 2, n2
    char accuracy1;
    char accuracy2;
};

/**
 * @author Antoine
 * @date Start 30/04/2021
 * @details Alias for structure PEvaluate
 */
typedef struct PEvaluate PEvaluate;

/**
 * @author Antoine
 * @date Start 30/04/2021
 * @details Structure who contain parameters of cross/mutate/new
 *      Action will be choose randomly weighted by this value.
 * @note cross+mutate+new >= 1
 * @param cross weighted of cross.
 * @param mutate weighted of mutate.
 * @param new weighted of mutate.
 */
struct PEvaluate
{
    unsigned char cross;
    unsigned char mutate;
    unsigned char new;
};

/**
 * @author Antoine
 * @date Start 26/04/2021
 * @details Generic recursive function to train Network X turns.
 * @param network Array of network need to be tested.
 * @param eval Local function of test and make a dual between 2 network
 * @param turn Amount of turn need to be train.
 * @param pop_input Size of array network.
 *      NOTE: It's a necessary to be pop_input%2==0 and we preconized %4==0.
 * @return Output a network array of best network.
 *      But it's important to think, we are generated new in this array,
 *      because it's a recursive function. In consequence, save only %4.
 *
 */
Network * network_train_turn(Network * network,
                             NEvaluate* (*eval) (Network*, Network*),
                             unsigned int turn,
                             unsigned int pop_input,
                             PEvaluate pe);

#endif //AI_MONTECARLO_NETWORK_EVALUATE_H
