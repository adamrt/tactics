#include "psx/types.h"

extern u8 g_game_allocator_table[];
extern u32 g_high_overlay_load_address;

u8* main_scus_mrta_realloc(u32 addr, u32 size) {
    u32 base;
    s32 start;
    u32 nblocks;
    s32 id;
    u32 i;
    u32 j;

    base = g_high_overlay_load_address;
    id = 1;
    start = (s32)(addr - base) / 2048;
    nblocks = size >> 11;
    if ((size & 0x7FF) != 0) {
        nblocks += 1;
    }
    if (addr < base) {
        return 0;
    }
    if (addr < base + 0x20000) {
        do {
            for (i = 0; i < 64; i++) {
                if (g_game_allocator_table[i] == id) {
                    id += 1;
                    break;
                }
            }
        } while (i != 64);

        for (i = start; i < start + nblocks; i++) {
            if (g_game_allocator_table[i] != 0) {
                break;
            }
        }
        if (i == start + nblocks) {
            for (j = 0; j < nblocks; j++) {
                g_game_allocator_table[start + j] = id;
            }
            return (u8*)((start << 11) + g_high_overlay_load_address);
        }
    }
    return 0;
}
