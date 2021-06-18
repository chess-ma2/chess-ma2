/**
 * @author Antoine
 * @details This file is responsible
 */

#ifndef AI_MONTECARLO_SAVE_C
#define AI_MONTECARLO_SAVE_C

#include "save.h"

char * network_save_export(Network * network)
{
    int i = 1;
    char * str = malloc(sizeof(char)*256);
    int s = 256;
    *str = '(';
//	printf("Start EX\n");
    int pl = network->input->neurons_count;
    network_save_export_layer(str, &s, &i, network->input, 0);
//	printf("Start HI\n");
    for (int j = 0; j < network->hidden_count; j++)
    {
	network_save_export_layer(str, &s, &i, (network->hidden + j), pl);
	pl = (network->hidden + j)->neurons_count;
    }
    network_save_export_layer(str, &s, &i, network->output, pl);

    if (s < i +2)
	str = realloc(str, s+2);

    *(str+i) = ')';
    *(str+i+1) = 0;

    return str;
}

void network_save_export_layer(char * str,  int * s, int * i, Layer * layer, int pl)
{
//	printf("Start LA\n");
    if (*s < *i)
    {
	str = realloc(str, (*s)*2);
        *s = (*s) *2;
    }
    *(str + *i) = '(';
    *i = *i +1;
    for (int j = 0; j < layer->neurons_count; j++)
	network_save_export_neurons(str, s, i, (layer->neurons+j), pl);
    if (*s < *i)
    {
	str = realloc(str, (*s)*2);
	*s = (*s) *2;
    }
    *(str+*i) = ')';
    *i = *i+1;
//	printf("END LA\n");
}

void network_save_export_neurons(char * str, int *s, int * i, Neuron * neuron, int c)
{
//	printf("Start NN\n");
    if (*s < 10 + *i)
    {
	str = realloc(str, (*s)*2);
	*s = (*s) *2;
    }
    *i += sprintf((str+*i), "(%f ", neuron->bias);
//	printf("PP NN\n");
    for (int w = 0; w < c; w++)
    {
	if (*s < 10 + *i)
	{
	    str = realloc(str, (*s)*2);
	    *s = (*s) *2;
	}
	*i += sprintf((str+*i), "%f ",*(neuron->weight + w));
    }
    *(str+*i) = ')';
    *i = *i +1;
//	printf("End NN\n%i  %i", *s, *i);
}

void network_save_import(char * str, Network * network)
{
    int i = 1;
    int layer = -2;
    //Network find end
    while (*(str+i) != ')' && *(str+i) != 0)
    {
        //Layer Find start
        while (*(str+i) != '(' && *(str+i) != 0)
        {
            layer++;
            Layer *l = network->input;
            if (layer >= 0 && layer < network->hidden_count)
                l = network->hidden + layer;
            else if (layer >= network->hidden_count)
                l = network->output;

            int neuron = -1;
            //Layer find end
            while (*(str+i) != ')' && *(str+i) != 0)
            {
                //Neurons find start
                while (*(str+i) != '(' && *(str+i) != 0)
                {
                    neuron ++;
                    Neuron *n = l->neurons + neuron;
                    int v = -2;
                    //Neurons find end
                    while (*(str+i) != ')' && *(str+i) != 0)
                    {
                        if (*(str+i) == ' ')
                        {
                            v++;
                            double f = atof(str+i);
                            if (v == -1)
                                n->bias = f;
                            else
                                *(n->weight + v) = f;
                        }

                        i++;
                    }
                    i++;
                }
                i++;
            }
            i++;
        }
        i++;
    }
}

#endif //AI_MONTECARLO_NETWORK_SAVE_C
