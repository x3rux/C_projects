#ifndef NEURALNET_H
#define NEURALNET_H
#include <stddef.h>

#include "Matrix.h"

typedef struct {
    Matrix *weights;
    Matrix *biases;
} Layer;

Layer* layer_init(size_t input_size, size_t output_size);
Matrix* layer_forward(Layer *l, Matrix *input);
void layer_free(Layer *l);

#endif