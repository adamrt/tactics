#include "psx/types.h"

extern s8 g_equip_transition_frame;

u8* equip_parse_advance_transition_frame(u8* data) {
    s32 current;
    s16 previous;
    s32 unused[2];

    current = g_equip_transition_frame;
    previous = current;
    if (current < 4) {
        g_equip_transition_frame = previous + 1;
    }
    return data + 1;
}
