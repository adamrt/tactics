#include "psx/types.h"

extern u32 g_open_script_dispatch_flags;
extern s32 g_open_script_byte_offset;
extern s32 g_open_script_fade_elapsed_frames;
extern s32 g_open_script_fade_duration_frames;
extern s32 g_open_script_fade_intensity;

void open_parse_start_control_0x80(const s16* command) {
    s32 value = command[1];
    register u32* control __asm__("$4") = &g_open_script_dispatch_flags;
    u32 flags;
    s32 next;

    g_open_script_fade_elapsed_frames = 0;
    g_open_script_fade_intensity = 0x80;
    flags = *control;
    next = g_open_script_byte_offset;
    *control = flags | 0x80;
    g_open_script_fade_duration_frames = value;
    g_open_script_byte_offset = next + 4;
}
