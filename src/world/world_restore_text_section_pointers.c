#include "psx/types.h"

extern void world_copy_bytes(void* destination, const void* source, u32 size);

extern u8* g_world_text_section_pointers[32];
extern u8* D_801A2574[32];
extern s32 D_80154DA8;

void world_restore_text_section_pointers(void) {
    world_copy_bytes(g_world_text_section_pointers, D_801A2574,
        sizeof(g_world_text_section_pointers));
    D_80154DA8 = 0;
}
