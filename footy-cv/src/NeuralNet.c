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

Matrix* layer_backward(Layer *l, Matrix *input, Matrix *output, Matrix *output_error, float learning_rate){
    if(l == NULL || input == NULL || output == NULL || output_error == NULL) return NULL;

    //dZ 
    Matrix* output_clone = matrix_clone(output);
    matrix_sigmoid_derivative(output_clone);
    Matrix* dZ = matrix_multiply(output_clone, output_error);
    matrix_free(output_clone);

    //dW 
    Matrix* input_transpose = matrix_transpose(input);
    Matrix* dW = matrix_dot(input_transpose, dZ);
    matrix_free(input_transpose);

    //new weights
    matrix_scale(dZ, learning_rate);
    matrix_scale(dW, learning_rate);
    Matrix* new_weights = matrix_add(dW, l->weights);
    Matrix* new_biases  = matrix_add(dZ, l->biases);
    matrix_free(l->biases);
    matrix_free(l->weights);
    l->biases = new_biases;
    l->weights = new_weights;

    //calculate error
    Matrix* weights_Transpose = matrix_transpose(l->weights);
    Matrix* input_error = matrix_dot(dZ, weights_Transpose);
    matrix_free(weights_Transpose);

    matrix_free(dW);
    matrix_free(dZ);
    return input_error;
}
