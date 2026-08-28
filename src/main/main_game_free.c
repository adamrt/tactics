#include "psx/types.h"

extern u8* g_high_overlay_load_address;
extern u8 g_game_allocator_table[];

s32 main_game_free(void* pointer) {
    u32 page_index = (u32)((u8*)pointer - g_high_overlay_load_address) >> 11;
    s32 allocation_id = g_game_allocator_table[page_index];
    s32 previous_id = g_game_allocator_table[page_index - 1];

    if ((page_index < 1) | (allocation_id != previous_id)) {
        u8* table = g_game_allocator_table;
        u8* entry = &table[page_index];

        do {
            *entry++ = 0;
        } while (*entry == allocation_id);
        return 1;
    }
    return 0;
}
