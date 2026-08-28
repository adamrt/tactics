#include "psx/types.h"

extern u8 g_require_fade_rgb[3];
extern void switch_to_next_event_thread(void);

void require_fade_rgb_31_frames(s32 target_0, s32 target_1, s32 target_2) {
    s32 current[3];
    s32 interpolated[3];
    s32 target[3];
    s32 frame;
    s32 i;

    frame = 0;
    target[0] = target_0 * 8;
    target[1] = target_1 * 8;
    target[2] = target_2 * 8;
    current[0] = g_require_fade_rgb[0];
    current[1] = g_require_fade_rgb[1];
    current[2] = g_require_fade_rgb[2];
    do {
        i = 0;
        do {
            interpolated[i] = (((target[i] - current[i]) * frame) / 30) + current[i];
            g_require_fade_rgb[i] = interpolated[i];
            i++;
        } while (i < 3);
        frame++;
        switch_to_next_event_thread();
    } while (frame < 31);
}
