#include <opencv2/opencv.hpp>
#include <stdlib.h>
#include "../include/Vision.h"

// 1. Initialization
void* vision_init(int camera_index) {
    // Allocate the camera object on the Heap (like Java's 'new' keyword)
    cv::VideoCapture* camera = new cv::VideoCapture(camera_index);

    if (!camera->isOpened()) {
        delete camera;
        return NULL;
    }

    // Hide the C++ object as a generic void pointer so C can use it
    return static_cast<void*>(camera);
}

// 2. Capture and Translate
float* vision_capture_frame(void* cap, int target_width, int target_height) {
    if (cap == NULL) return NULL;
    
    // Un-hide the pointer back into a C++ object
    cv::VideoCapture* camera = static_cast<cv::VideoCapture*>(cap);
    
    cv::Mat frame;
    *camera >> frame; // Grab a frame from the webcam
    
    if (frame.empty()) return NULL;
    
    // Shrink the image so the neural network doesn't freeze the CPU
    cv::Mat resized;
    cv::resize(frame, resized, cv::Size(target_width, target_height));
    
    // Convert to Grayscale (Black and White)
    cv::Mat gray;
    cv::cvtColor(resized, gray, cv::COLOR_BGR2GRAY);
    
    // Allocate a standard C array for our neural network
    int total_pixels = target_width * target_height;
    float* data = (float*)malloc(total_pixels * sizeof(float));
    if (data == NULL) return NULL;
    
    // Unpack the 2D OpenCV matrix into our 1D float array
    for (int r = 0; r < gray.rows; r++) {
        for (int c = 0; c < gray.cols; c++) {
            // Grab the pixel value (0 to 255)
            uint8_t pixel = gray.at<uchar>(r, c);
            
            // Normalize it to a float between 0.0 and 1.0
            data[r * gray.cols + c] = (float)pixel / 255.0f;
        }
    }
    
    return data;
}

// 3. Teardown
void vision_free(void* cap) {
    if (cap == NULL) return;
    
    cv::VideoCapture* camera = static_cast<cv::VideoCapture*>(cap);
    camera->release(); // Turn off the physical webcam hardware
    delete camera;     // Free the C++ memory
}