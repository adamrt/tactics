#include "psx/types.h"

extern s8 g_bunit_transition_frame;

void bunit_set_transition_frame(s32 frame) {
    g_bunit_transition_frame = frame;
}
