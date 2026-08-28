#include "psx/libc.h"
extern int g_play_time_frames;
extern int g_play_time_seconds;
extern int g_play_time_minutes;
extern int g_play_time_hours;
extern int g_session_frames;

void main_vsync_callback_func(void) {
    rand();

    g_play_time_frames++;
    if (g_play_time_frames >= 60) {
        g_play_time_frames = 0;
        g_play_time_seconds++;
        if (g_play_time_seconds >= 60) {
            g_play_time_seconds = 0;
            g_play_time_minutes++;
            if (g_play_time_minutes >= 60) {
                g_play_time_minutes = 0;
                if (g_play_time_hours < 1000) {
                    g_play_time_hours++;
                }
            }
        }
    }

    g_session_frames++;
}

/* Keep the preprocessed source stable for the legacy compiler under QEMU. */
