#include "psx/types.h"

void battle_store_halfword(u8* dst, u16 value) {
    dst[0] = value & 0xff;
    dst[1] = value >> 8;
}
