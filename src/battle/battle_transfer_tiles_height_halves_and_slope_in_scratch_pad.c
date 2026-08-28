#include "psx/types.h"

extern u8* g_battle_scratch_pad_ptr;

void battle_transfer_tiles_height_halves_and_slope_in_scratch_pad(void) {
    u8* ctx = g_battle_scratch_pad_ptr;
    ctx[0x4C] = (*(u8**)ctx)[2] << 1;
    ctx[0x56] = (*(u8**)ctx)[3] & 0x1F;
    ctx[0x58] = (*(u8**)ctx)[4];
}
