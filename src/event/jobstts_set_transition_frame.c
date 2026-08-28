#include "psx/types.h"

extern s8 g_jobstts_transition_frame;

void jobstts_set_transition_frame(s32 frame) {
    g_jobstts_transition_frame = frame;
}
