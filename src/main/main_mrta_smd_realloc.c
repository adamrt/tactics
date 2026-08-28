#include "psx/types.h"

extern u8 g_smd_allocator_table[];
extern u8 g_smd_heap_base[];

s32 main_mrta_smd_realloc(void* ptr) {
    u32 index;
    s32 tag;
    u8* entry;

    index = ((u32)ptr - (u32)g_smd_heap_base) >> 11;
    tag = g_smd_allocator_table[index];
    if (((index == 0) | (tag != g_smd_allocator_table[index - 1])) == 0) {
        return 0;
    }
    entry = &g_smd_allocator_table[index];
    do {
        *entry = 0;
        entry += 1;
    } while (*entry == tag);
    return 1;
}
