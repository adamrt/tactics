#include "psx/types.h"

extern s8 g_jobstts_transition_frame;

s32 jobstts_get_transition_frame(void) {
    return g_jobstts_transition_frame;
}
