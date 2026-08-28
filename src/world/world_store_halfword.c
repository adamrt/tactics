#include "psx/types.h"

void world_store_halfword(u8* destination, u16 value) {
    destination[0] = value;
    destination[1] = value >> 8;
}
