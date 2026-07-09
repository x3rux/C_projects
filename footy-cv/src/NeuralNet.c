#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/NeuralNet.h"

Layer* layer_init(size_t input_size, size_t output_size){
    Layer* l = malloc(sizeof(Layer));
    if(l == NULL) return NULL;

    l->weights = matrix_allocate(input_size, output_size);
    l->biases = matrix_allocate(1, output_size);

    for (size_t i = 0; i < input_size * output_size; i++) {
        l->weights->data[i] = (float) rand()/RAND_MAX;
    }

    return l;
}

Matrix* layer_forward(Layer *l, Matrix *input){
    
    Matrix* W = l->weights;
    Matrix* B = l->biases;
    Matrix* Z = matrix_dot(W, input);
    Z = matrix_add(Z, B);
    matrix_sigmoid(Z);

    return Z;
}

void layer_free(Layer *l){
    matrix_free(l->biases);
    matrix_free(l->weights);
    free(l);
}