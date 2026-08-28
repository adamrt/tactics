#include "psx/types.h"

extern s8 g_bunit_transition_frame;

s32 bunit_get_transition_frame(void) {
    return g_bunit_transition_frame;
}
