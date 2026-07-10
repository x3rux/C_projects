#ifndef VISION_H
#define VISION_H

#ifdef __cplusplus
extern "C" {
#endif

void* vision_init(int camera_index);

float* vision_capture_frame(void* cap, int target_width, int target_height);

void vision_free(void* cap);

#ifdef __cplusplus
}
#endif

#endif