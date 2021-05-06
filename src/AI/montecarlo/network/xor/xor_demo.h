/**
 * @author Antoine
 * @date Start 28/04/2021
 * @details Header of demo file to output an example of learn with XOR.
 */
#ifndef AI_MONTECARLO_NETWORK_XOR_DEMO_H
#define AI_MONTECARLO_NETWORK_XOR_DEMO_H

/**
 * @author Antoine
 * @date Start 28/04/2021
 * @details Use to enable printf in AE to view learning
 */
#define DEBUG_AE

#include <time.h>

#include "evaluate.c"

/**
 * @author Antoine
 * @date Start 28/04/2021
 * @details Run an example of train of XOR Network with pop = 4
 * @param turn Amount of turn of train.
 */
void network_xor_demo(int turn);

/**
 * @author Antoine
 * @date Start 28/04/2021
 * @details Launch xor demo.
 */
int main(int argc, char ** argv);
#endif //AI_MONTECARLO_NETWORK_XOR_DEMO_H
