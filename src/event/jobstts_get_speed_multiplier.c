#include "psx/types.h"

extern s8 g_jobstts_speed_multiplier;

s32 jobstts_get_speed_multiplier(void) {
    s32 value = g_jobstts_speed_multiplier;

    if (value == 0) {
        return 1;
    }
    return value;
}
