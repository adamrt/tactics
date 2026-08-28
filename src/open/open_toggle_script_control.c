#include "psx/types.h"

extern u32 g_open_script_dispatch_flags;
extern u32 g_open_script_byte_offset;

void open_toggle_script_control(void) {
    u32* control = &g_open_script_dispatch_flags;
    u32 state = *control;

    if (!(state & 0x30)) {
        goto advance;
    }

    {
        u32 toggled = state ^ 2;

        *control = toggled;
        return;
    }

advance: {
    u32 script_offset = g_open_script_byte_offset;

    *control = state ^ 1;
    g_open_script_byte_offset = script_offset + 2;
}
}
