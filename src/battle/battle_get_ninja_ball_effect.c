#include "psx/types.h"

extern u8 D_801B8544[];

s32 battle_get_ninja_ball_effect(s32 arg) {
    s32 i;

    if (arg != 0) {
        for (i = 0; i < 9; i++) {
            if ((arg & D_801B8544[i]) != 0) {
                break;
            }
        }
        arg = i;
    }
    return arg;
}
