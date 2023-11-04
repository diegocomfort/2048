#ifndef NEURAL_NEWTWORK_2048_H
#define NEURAL_NEWTWORK_2048_H

#define HIDDEN_LAYERS 3
#define LAYER_LENGTH 16

float relu(double x)
{
    return x > 0 ? (float) x : 0.0F;
}

typedef struct
{
    float hiddenLayers[HIDDEN_LAYERS][LAYER_LENGTH];
    float hiddenLayerWeights[HIDDEN_LAYERS - 1][LAYER_LENGTH][LAYER_LENGTH];
    float outputLayer[4];
    float outputLayerWeights[LAYER_LENGTH][4];
}
Network;

Network newNetwork();

#endif