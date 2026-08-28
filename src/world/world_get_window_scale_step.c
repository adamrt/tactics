#include "psx/types.h"

extern s8 g_world_window_scale_step;

/* Returns the current window open/close scaling animation step. */
s8 world_get_window_scale_step(void) {
    return g_world_window_scale_step;
}
