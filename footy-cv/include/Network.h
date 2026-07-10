#ifndef NETWORK_H
#define NETWORK_H

#include "Matrix.h"
#include "NeuralNet.h"

typedef struct {
    int num_layers;
    Layer** layers; // An array of Layer pointers
} Network;

Network* network_init(int num_layers, int* layer_sizes);

Matrix* network_forward(Network* net, Matrix* input);

void network_free(Network* net);

#endif