#include "fft/data.h"

extern u32* g_world_event_words;

void world_initialize_camera_yaw_angle(void) {
    g_world_event_words[WORLD_EVENT_WORD_CAMERA_YAW] = (g_world_event_words[WORLD_EVENT_WORD_CAMERA_YAW] + 0xa000) & 0x0fff;
}
