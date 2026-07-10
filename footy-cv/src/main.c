#include <stdio.h>
#include <stdlib.h>
#include "../include/Vision.h"

int main() {
    printf("--- Initializing Vision Engine ---\n");
    
    // 1. Turn on the webcam (Index 0 is usually the default camera)
    void* camera = vision_init(0);
    
    if (camera == NULL) {
        printf("ERROR: Could not open the webcam. (Is it plugged in or in use?)\n");
        return 1;
    }
    printf("Webcam successfully opened! Hardware is active.\n");

    // 2. Capture a frame (We'll shrink it to 64x64 for the neural network)
    int width = 64;
    int height = 64;
    printf("Capturing a %dx%d frame...\n", width, height);
    
    float* frame_data = vision_capture_frame(camera, width, height);
    
    if (frame_data != NULL) {
        printf("Frame captured successfully!\n");
        
        // Print a few pixels from the exact center of the image to prove data is flowing
        int center_index = (height / 2) * width + (width / 2);
        printf("Pixel data at center [32,32]: %f (0.0 is black, 1.0 is white)\n", frame_data[center_index]);
        printf("Pixel data at [32,33]: %f\n", frame_data[center_index + 1]);
        printf("Pixel data at [32,34]: %f\n", frame_data[center_index + 2]);
        
        // Always free the data allocated by the bridge!
        free(frame_data); 
    } else {
        printf("ERROR: Captured an empty frame.\n");
    }

    // 3. Teardown
    printf("Shutting down the webcam...\n");
    vision_free(camera);
    printf("Vision Engine offline. Memory secured.\n");

    return 0;
}