#include "psx/types.h"

extern void* g_battle_scratch_pad_ptr;

void battle_set_spreading_tile_x_and_y_coordinates(void) {
    u8* p = (u8*)g_battle_scratch_pad_ptr;
    *(s16*)(p + 0x30) = *(u16*)(p + 0x26) + *(u16*)(p + 0x3A);
    *(s16*)(p + 0x32) = *(u16*)(p + 0x28) + *(u16*)(p + 0x3C);
}
