#include "psx/types.h"

extern void open_set_sound_type_and_volume(s32 sound_type, s32 duration);
extern u32 g_open_script_dispatch_flags;
extern s32 g_open_script_byte_offset;
extern s32 g_open_script_control_parameter;
extern s32 g_open_script_control_state;

void open_parse_start_control_0x20(const u8* command) {
    u32* control = &g_open_script_dispatch_flags;
    u32 state = *control;

    if (state & 4) {
        if (state & 0x20) {
            *control = state ^ 2;
            return;
        }
        {
            s32 script_offset = g_open_script_byte_offset;

            *control = state ^ 4;
            g_open_script_byte_offset = script_offset + 4;
            return;
        }
    }
    if (state & 0x38) {
        s32 script_offset = g_open_script_byte_offset;

        g_open_script_byte_offset = script_offset + 4;
        return;
    }

    {
        s32 parameter = *(const s16*)(command + 2);

        g_open_script_control_state = 0;
        *control = (state & ~0x3a) | 0x24;
        g_open_script_control_parameter = parameter;
        open_set_sound_type_and_volume(0, 1);
    }
}
