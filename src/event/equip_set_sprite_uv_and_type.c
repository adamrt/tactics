#include "psx/types.h"

void equip_set_sprite_uv_and_type(s16* arg0, u32 arg1) {
    arg0[0] = (arg1 & 0x3F) << 4;
    arg0[1] = (arg1 & 0xFFFF) >> 6;
    arg0[2] = 0x10;
    arg0[3] = 1;
}
