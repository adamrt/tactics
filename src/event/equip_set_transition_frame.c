#include "psx/types.h"

extern s8 g_equip_transition_frame;

void equip_set_transition_frame(s32 value) {
    g_equip_transition_frame = value;
}
