#include "psx/types.h"

extern s8 g_bunit_transition_frame;

s32 bunit_advance_transition_frame_and_value(s32 value) {
    if (g_bunit_transition_frame < 4) {
        g_bunit_transition_frame++;
    }
    return value + 1;
}
