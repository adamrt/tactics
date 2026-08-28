#include "fft/battle.h"

extern u8 g_spritesheet_data[];
extern u8 g_spritesheet_record_data[];
extern u8 g_spritesheet_fallback[];
extern u8 g_spritesheet_data[];

u8* battle_get_spritesheet_shp_data_address(u32 index) {
    s32 value;

    value = g_spritesheet_data[(index & 0xFFFF) * 4];
    if (value < 5) {
        return g_spritesheet_record_data + value * 0x688;
    }
    return g_spritesheet_fallback;
}
