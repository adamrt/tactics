#include "psx/types.h"

extern void world_copy_bytes(void* destination, const void* source, s32 count);

void battle_copy_32_bytes(void* destination, const void* source) {
    world_copy_bytes(destination, source, 0x20);
}
