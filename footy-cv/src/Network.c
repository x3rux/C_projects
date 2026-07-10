#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/Network.h"

Network* network_init(int num_layers, int* layer_sizes){
    Network* net = malloc(sizeof(Network));
    if(net == NULL) return NULL;

    net->num_layers = num_layers;
    net->layers = malloc(num_layers * sizeof(Layer*));
    if(net->layers == NULL) return NULL;

    for (size_t i = 0; i < num_layers; i++) {
        net->layers[i] = layer_init(layer_sizes[i], layer_sizes[i+1]);
        if(net->layers[i] == NULL){
            printf("ERROR: Not able to allocate current layer: %d", (int)i);
        }
    }

    return net;
}

void network_free(Network *net){
    for (size_t i = 0; i < net->num_layers; i++) {
        if(net->layers[i] != NULL){
            layer_free(net->layers[i]);
        }
    }
    if(net->layers != NULL) free(net->layers);
    if(net != NULL) free(net);
}

Matrix* network_forward(Network* net, Matrix* input){
    Matrix* curr = input;
    for (size_t i = 0; i < net->num_layers; i++) {
        Matrix* old = curr;
        if(i == 0){
            curr = layer_forward(net->layers[i], input);
            continue;
        }
        else{
            curr = layer_forward(net->layers[i], curr);
        }
        matrix_free(old);
    }
    return curr;
}