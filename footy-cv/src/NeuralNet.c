#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/NeuralNet.h"

void layer_free(Layer *l){
    if(l == NULL) return;
    matrix_free(l->biases);
    matrix_free(l->weights);
    free(l);
}

Layer* layer_init(size_t input_size, size_t output_size){
    Layer* l = malloc(sizeof(Layer));
    if(l == NULL) return NULL;

    l->weights = matrix_allocate(input_size, output_size);
    l->biases = matrix_allocate(1, output_size);
    if(l->weights == NULL || l->biases == NULL){
        layer_free(l);
        return NULL;
    }

    for (size_t i = 0; i < input_size * output_size; i++) {
        l->weights->data[i] = (float) rand()/RAND_MAX;
    }

    return l;
}

Matrix* layer_forward(Layer *l, Matrix *input){
    if(l == NULL || input == NULL) return NULL;

    Matrix* dot_result = matrix_dot(input, l->weights);
    Matrix* Z = matrix_add(dot_result, l->biases);
    matrix_free(dot_result);
    matrix_sigmoid(Z);

    return Z;
}
