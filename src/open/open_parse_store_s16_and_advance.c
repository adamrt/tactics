#include "psx/types.h"

extern s32 g_open_script_timing_step;
extern s32 g_open_script_timing_fraction;
extern s32 g_open_script_external_counter;
extern s32 g_open_script_byte_offset;

void open_parse_store_s16_and_advance(const s16* command) {
    s32 value = command[1];
    s32 next = g_open_script_byte_offset + 4;

    g_open_script_external_counter = 0;
    g_open_script_timing_fraction = 0;
    g_open_script_timing_step = value;
    g_open_script_byte_offset = next;
}
