#ifndef AI_MONTECARLO_NETWORK_XOR_DEMO_C
#define AI_MONTECARLO_NETWORK_XOR_DEMO_C

#include "xor_demo.h"

void network_xor_demo(int turn)
{
    PEvaluate pe = {0, 1, 1};
    Network * network = network_xor_init_table(20);
    network_train_turn(network, network_xor_dual, turn, 20, pe);

    //Print best NN
    printf("\n\nValue of best NN found:\n");

    for (int l = 0; l <= network->hidden_count; ++l) {
        Layer * later = network->output;
        if (l <network->hidden_count)
            later = network->hidden+l;

        printf("  Layer %i with %i neurons:\n", l, later->neurons_count);

        for (int i = 0; i < later->neurons_count; ++i) {
            printf("    N%i : %f", i, (later->neurons+i)->bias);
            int bmax = l - 1;
            if (bmax < 0)
                bmax = network->input->neurons_count;
            else
                bmax = (network->hidden + bmax)->neurons_count;
            for (int b = 0; b < bmax; ++b)
            {
                printf("  %f", *((later->neurons + i)->weight + b));
            }
            printf("\n");
        }
    }
    //Print accuracy found
    NEvaluate *ne = network_xor_dual(network, network);
    printf("\n\nRésultat: %i%%\n", ne->accuracy1);
}

int main(int argc, char ** argv)
{
    //To init random
    srand(time(NULL));

    network_xor_demo((argc != 2 ? 200 : atoi(argv[1])));

    return 0;
}

#endif //AI_MONTECARLO_NETWORK_XOR_DEMO_C
