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

}

#endif //AI_MONTECARLO_NETWORK_SAVE_C
