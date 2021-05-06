/**
 * @author Antoine
 * @date 23/04/2021
 * @details Source of file for random elements generator.
 */
#ifndef AI_MONTECARLO_NETWORK_RANDOM_C
#define AI_MONTECARLO_NETWORK_RANDOM_C



#include <stdlib.h>
#include <math.h>
#include "random.h"

double network_random_uniform_gen(double min, double max)
{
    return ( (rand()%(1000*( ((int) (max-min) ) )+1))/1000.0)+min;
}

//For Gaussian generator
//Middle = u average of value
//step = o standard deviation,
//Please Note:
//[u-o; u+o] has 68%
//[u-2o; u+2o] (1.96) has 95%, for 95% between -1 and 1--> step =0.5
//[u-3o; u+3o] (1.96) has 99.7%, for 99.7% between -1 and 1--> step =1/3
//void network_random_gaussian_gen(double middle, double step);
double network_random_gaussian_gen(double u, double o)
{
    double u1 = rand()%1000/1000;
    double u2 = rand()%1000/1000;

    return (sqrt(-2 * log(u1)) * cos(2 * M_PI * u2) * o) + u;
}

void network_random_fill(Network * network, double (*f)(double, double),
                         double param1, double param2)
{
    for (unsigned char l = 0; l <= network->hidden_count; l++)
    {
        Layer *layer = network->output;
        if (l < network->hidden_count)
                layer = (network->hidden + l);
        int wmax = network->input->neurons_count;
        if (l > 0)
            wmax = (network->hidden+l-1)->neurons_count;

        for (int n = 0; n < layer->neurons_count; n++)
        {
            Neuron *neuron = (layer->neurons + n);
            neuron->bias = f(param1, param2);

            for (int w = 0; w < wmax; ++w)
                *(neuron->weight+w) = f(param1, param2);
        }
    }
}

#endif //AI_MONTECARLO_NETWORK_RANDOM_H
