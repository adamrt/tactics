#include "psx/types.h"

extern void world_copy_bytes(void* destination, const void* source, u32 size);
extern const u8 D_8016E44C[8];

void world_func_8010a690(u8* record) {
    *(s16*)(record + 0x1c) = 0;
    *(s16*)(record + 0x26) = 0;
    world_copy_bytes(record + 0x20, D_8016E44C, 8);
}
