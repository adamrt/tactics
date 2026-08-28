#include "psx/types.h"

extern void world_copy_bytes(void* destination, const void* source, u32 size);
extern const u8 g_debugchr_primitive_tail_template[8];

void debugchr_initialize_portrait_primitive_tail(u8* primitive) {
    *(s16*)(primitive + 0x1c) = 0;
    *(s16*)(primitive + 0x26) = 0;
    world_copy_bytes(primitive + 0x20, g_debugchr_primitive_tail_template, 8);
}
