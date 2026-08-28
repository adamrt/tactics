#include "psx/types.h"

extern void open_set_sound_type_and_volume(s32 control, s32 value);
extern u32 g_open_script_dispatch_flags;
extern s32 g_open_script_byte_offset;
extern s32 g_open_script_control_0x10_state;

void open_parse_start_control_0x10(void) {
    u32* control = &g_open_script_dispatch_flags;
    u32 state = *control;
    s32 result;

    if (state & 4) {
        if (state & 0x10) {
            result = state ^ 2;
            *control = result;
            return;
        }
        result = g_open_script_byte_offset;
        state ^= 4;
        *control = state;
        goto advance;
    }
    if (state & 0x28)
        goto start;
    result = g_open_script_byte_offset;

advance:
    g_open_script_byte_offset = result + 2;
    goto done;

start:
    result = (state & ~0x3a) | 0x14;
    g_open_script_control_0x10_state = 0;
    *control = result;
    open_set_sound_type_and_volume(0, 1);

done:;
}
