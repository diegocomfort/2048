#include "neuralnetwork.h"

#include <stdlib.h>
#include <time.h>

Network newNetwork()
{
    Network network = {0};

    for (int i = 0; i < HIDDEN_LAYERS - 1; ++i)
        for (int j = 0; j < LAYER_LENGTH; ++j)
            for (int k = 0; k < LAYER_LENGTH; ++k)
                    network.hiddenLayerWeights[i][j][k] = ((float) rand()) / RAND_MAX;

    

    return network;
}