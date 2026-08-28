#include "psx/types.h"

extern s32 g_animation_speed;

s32 battle_set_animation_speed(s32 speed) {
    if ((u32)(speed - 1) < 2) {
        g_animation_speed = speed;
        return 0;
    }
    return -1;
}
