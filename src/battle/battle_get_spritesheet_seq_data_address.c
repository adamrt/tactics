#include "fft/battle.h"

extern u8 g_spritesheet_data[];
extern u8 g_spritesheet_alt_data[];
extern u8 g_spritesheet_alt_fallback[];

u8* battle_get_spritesheet_seq_data_address(u32 index) {
    s32 value;

    value = g_spritesheet_data[((index & 0xFFFF) * 4) + 1];
    if (value < 5) {
        return g_spritesheet_alt_data + value * 0x408;
    }
    return g_spritesheet_alt_fallback;
}
