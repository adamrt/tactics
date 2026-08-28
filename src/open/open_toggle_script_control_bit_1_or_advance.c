#include "psx/types.h"

extern u32 g_open_script_dispatch_flags;
extern u32 g_open_script_byte_offset;

void open_toggle_script_control_bit_1_or_advance(void) {
    u32* control = &g_open_script_dispatch_flags;
    u32 state = *control;
    u32 result;

    if (!(state & 0x38)) {
        goto advance;
    }

    result = state ^ 2;
    *control = result;
    return;

advance:
    result = g_open_script_byte_offset;
    g_open_script_byte_offset = result + 2;
}
