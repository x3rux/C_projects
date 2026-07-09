#include <stdio.h>
#include "../include/NeuralNet.h"
#include "../include/Matrix.h"

int main() {
    printf("--- Building the OR Gate Neural Network ---\n");
    
    // 1. Initialize the Layer (2 inputs, 1 output)
    Layer *layer = layer_init(2, 1);
    if (layer == NULL) return 1;

    // 2. Prepare the Training Data
    Matrix *inputs[4];
    Matrix *targets[4];

    for (int i = 0; i < 4; i++) {
        inputs[i] = matrix_allocate(1, 2);
        targets[i] = matrix_allocate(1, 1);
    }

    // [0, 0] -> [0]
    inputs[0]->data[0] = 0.0f; inputs[0]->data[1] = 0.0f; targets[0]->data[0] = 0.0f;
    // [0, 1] -> [1]
    inputs[1]->data[0] = 0.0f; inputs[1]->data[1] = 1.0f; targets[1]->data[0] = 1.0f;
    // [1, 0] -> [1]
    inputs[2]->data[0] = 1.0f; inputs[2]->data[1] = 0.0f; targets[2]->data[0] = 1.0f;
    // [1, 1] -> [1]
    inputs[3]->data[0] = 1.0f; inputs[3]->data[1] = 1.0f; targets[3]->data[0] = 1.0f;

    // 3. The Training Loop (10,000 Epochs)
    printf("Training for 10,000 epochs...\n");
    float learning_rate = 0.1f;

    for (int epoch = 0; epoch < 10000; epoch++) {
        for (int i = 0; i < 4; i++) {
            // A. Forward Pass (Make a guess)
            Matrix *prediction = layer_forward(layer, inputs[i]);
            
            // B. Calculate Error (Target - Guess)
            Matrix *error = matrix_subtract(targets[i], prediction);
            
            // C. Backward Pass (Learn from the mistake)
            Matrix *input_error = layer_backward(layer, inputs[i], prediction, error, learning_rate);
            
            // D. Cleanup temporary memory for this step
            matrix_free(prediction);
            matrix_free(error);
            matrix_free(input_error);
        }
    }

    // 4. The Final Test
    printf("\n--- Final Predictions after Training ---\n");
    for (int i = 0; i < 4; i++) {
        Matrix *final_pred = layer_forward(layer, inputs[i]);
        printf("Input: [%.0f, %.0f] -> Prediction: %.4f (Target: %.0f)\n", 
                inputs[i]->data[0], inputs[i]->data[1], 
                final_pred->data[0], targets[i]->data[0]);
        matrix_free(final_pred);
    }

    // 5. Total Teardown
    for (int i = 0; i < 4; i++) {
        matrix_free(inputs[i]);
        matrix_free(targets[i]);
    }
    layer_free(layer);

    printf("\nEngine shutdown complete. All memory freed.\n");
    return 0;
}