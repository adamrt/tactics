#include "psx/types.h"

extern u8 g_spritesheet_data[];

u32 battle_get_spritesheet_graphic_height(u32 spritesheet_id) {
    return g_spritesheet_data[((spritesheet_id & 0xffff) << 2) + 2];
}
