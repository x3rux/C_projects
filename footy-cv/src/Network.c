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

void network_train(Network* net, Matrix* input, Matrix* target, float learning_rate){
    if(net == NULL || input == NULL || target == NULL) return;

    Matrix** history = malloc((net->num_layers + 1) * sizeof(Matrix*));
    if(history == NULL) return;

    history[0] = input;
    for (size_t i = 0; i < net->num_layers; i++) { //store forward pass data
        history[i+1] = layer_forward(net->layers[i], history[i]);
    }

    Matrix* error = matrix_subtract(history[net->num_layers], target);
    
    Matrix* curr_error = error;
    for (int i = net->num_layers - 1; i >= 0; i--) {
        Matrix* prev_error = layer_backward(net->layers[i], history[i], history[i+1], curr_error, learning_rate);
        if(curr_error != error) matrix_free(curr_error);
        curr_error = prev_error;
    }

    matrix_free(curr_error);
    for (size_t i = 1; i <= net->num_layers; i++) {
        matrix_free(history[i]);
    }
    free(history);
}