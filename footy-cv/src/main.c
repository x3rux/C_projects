#include <stdio.h>
#include <stdlib.h>
#include "../include/Vision.h"
#include "../include/Network.h"
#include "../include/Matrix.h"

int main() {
    printf("--- Booting Training Engine ---\n");

    int layers = 2;
    int layer_sizes[] = {4096, 128, 2};
    Network* net = network_init(layers, layer_sizes);
    
    void* camera = vision_init(0);
    if (!camera) return 1;

    // Define what we want the network to learn
    // We want the network to look at the webcam and output [1.0, 0.0]
    Matrix* target = matrix_allocate(1, 2);
    target->data[0] = 1.0f;
    target->data[1] = 0.0f;

    int epochs = 100;
    float learning_rate = 0.1f;

    for (int epoch = 1; epoch <= epochs; epoch++) {
        // 1. Grab fresh data
        float* frame_data = vision_capture_frame(camera, 64, 64);
        Matrix* input = matrix_allocate(1, 4096);
        for (int i = 0; i < 4096; i++) {
            input->data[i] = frame_data[i];
        }

        // 2. See what the network currently guesses
        Matrix* prediction = network_forward(net, input);
        printf("Epoch %d | Prediction: [%.4f, %.4f]\n", epoch, prediction->data[0], prediction->data[1]);

        // 3. Run Backpropagation (Train the network to get closer to the target)
        network_train(net, input, target, learning_rate);

        // 4. Memory cleanup for this loop iteration
        matrix_free(prediction);
        matrix_free(input);
        free(frame_data);
    }

    printf("\nTraining complete. Shutting down...\n");
    matrix_free(target);
    vision_free(camera);
    network_free(net);

    return 0;
}