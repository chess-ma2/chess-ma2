/**
 * @author Antoine
 * @details This file is responsible
 */

#ifndef AI_MONTECARLO_SAVE_H
#define AI_MONTECARLO_SAVE_H

#include "../structure/network.c"

char * network_save_export(Network * network);

void network_save_export_layer(char * str,  int * s, int * i, Layer * layer, int pl);

void network_save_export_neurons(char * str, int *s, int * i, Neuron * neuron, int c);

void network_save_import(char * str, Network * network);

#endif //AI_MONTECARLO_NETWORK_SAVE_H
