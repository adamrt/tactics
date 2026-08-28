#include "psx/types.h"

extern s32 g_battle_graphics_nibble_phase;
extern s32 g_battle_compressed_graphics_offset;
extern u8* g_battle_compressed_graphics_data;

u32 battle_read_compressed_graphics_nibble(void) {
    u32 nibble;
    u8 value;

    if (g_battle_graphics_nibble_phase == 0) {
        nibble = g_battle_compressed_graphics_data
                     [g_battle_compressed_graphics_offset]
            >> 4;
    } else {
        value = g_battle_compressed_graphics_data
            [g_battle_compressed_graphics_offset];
        g_battle_compressed_graphics_offset++;
        nibble = value & 0xf;
    }
    g_battle_graphics_nibble_phase ^= 1;
    return nibble;
}
