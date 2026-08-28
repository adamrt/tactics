#include "psx/types.h"

extern u8 g_bunit_decreasing_fade_active;
extern u8 g_bunit_increasing_fade_active;

s32 bunit_get_fade_state(void) {
    s32 second;
    s32 first;

    second = g_bunit_increasing_fade_active;
    first = g_bunit_decreasing_fade_active;
    second *= 2;
    return first + second;
}
