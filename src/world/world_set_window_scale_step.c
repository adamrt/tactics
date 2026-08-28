#include "psx/types.h"

extern s8 g_world_window_scale_step;

/* Sets the step of the window open/close scaling animation. Steps 0-3 index
 * the percentage table at 0x8018e048 ({10, 60, 90, 95}); any step >= 4 means
 * "no scaling", so callers pass 10 to draw the window at full size. */
void world_set_window_scale_step(s8 step) {
    g_world_window_scale_step = step;
}
