#include "psx/types.h"

extern void* allocate_battle_memory(s32 bytes);

/* Thin public entry point for the BATTLE menu-buffer allocator. */
void* battle_allocate_menu_buffer(s32 bytes) {
    return allocate_battle_memory(bytes);
}
