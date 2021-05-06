/**
 * @author Antoine
 * @date Start 23/04/2021
 * @details Header of file for random elements generator.
 */
#ifndef AI_MONTECARLO_NETWORK_RANDOM_H
#define AI_MONTECARLO_NETWORK_RANDOM_H

#include <stdlib.h>
#include "../structure/network.c"

/**
 * @author Antoine
 * @date Start 23/04/2021
 * @details Generate a 'random' number double between min and max give.
 * @param min Min double value.
 * @param max Max double value.
 * @return A random double number in interval [min; max].
 */
double network_random_uniform_gen(double min, double max);



/**
 * @author Antoine
 * @date Start 27/04/2021
 * @details Generate a 'random' number double
 *      who follow a Gaussian Distribution.
 * @param u Average who is center the gaussian
 * @param o Standard Deviation
 *      [u-o; u+o] has 68%
 *      [u-2o; u+2o] has 95%, for 95% between -1 and 1--> step = 0.5
 *      [u-3o; u+3o] has 99.7%, for 99.7% between -1 and 1--> step = 1/3
 * @return A random double number who follow Gaussian Distribution.
 */
double network_random_gaussian_gen(double u, double o);

/**
 * @author Antoine
 * @date Start 23/04/2021
 * @details Fill Neuronal Network parameters with numbers.
 * @param network Neuronal network need to fill.
 * @param f Function who choose number.
 * @param param1 Parameter 1 of f function.
 * @param param2 Parameter 2 of f function.
 */
void network_random_fill(Network * network, double (*f)(double, double),
                         double param1, double param2);

#endif //AI_MONTECARLO_NETWORK_RANDOM_H
