#include <stdio.h>
#include "../include/NeuralNet.h"

int main() {
    printf("--- Initializing Neural Network Layer ---\n");
    // Create a layer with 3 inputs and 2 outputs (neurons)
    Layer *l = layer_init(3, 2);
    if (l == NULL) {
        printf("Layer allocation failed.\n");
        return 1;
    }

    printf("--- Creating Input Data ---\n");
    // Create a 1x3 input matrix (1 row, 3 columns)
    Matrix *input = matrix_allocate(1, 3);
    input->data[0] = 0.5f;
    input->data[1] = 0.8f;
    input->data[2] = 0.2f;

    printf("Input Matrix (1x3):\n");
    matrix_print(input);

    printf("\n--- Running Forward Propagation ---\n");
    Matrix *output = layer_forward(l, input);
    
    if (output != NULL) {
        printf("Output Matrix (1x2):\n");
        matrix_print(output);
    }

    printf("\n--- Cleaning Up ---\n");
    matrix_free(input);
    matrix_free(output);
    layer_free(l);

    printf("Forward pass complete. Memory freed.\n");
    return 0;
}