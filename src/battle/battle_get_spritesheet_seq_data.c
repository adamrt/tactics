#include "psx/types.h"

extern u8 g_spritesheet_data[];
extern u8 g_spritesheet_seq_data[];

u8* battle_get_spritesheet_seq_data(u32 spritesheet_id) {
    return g_spritesheet_seq_data + g_spritesheet_data[(spritesheet_id & 0xffff) << 2] * 3136;
}
