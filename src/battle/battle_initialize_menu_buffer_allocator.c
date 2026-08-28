#include "psx/types.h"

extern s32 g_battle_menu_allocator_slot_records[16][2];
extern u8 g_battle_menu_buffer_allocation_map[53];
extern s32 g_battle_menu_slot_owner_thread_ids[3];
extern s32 g_battle_menu_slot_states[3];

void battle_initialize_menu_buffer_allocator(void) {
    s32 index;
    u8* allocation_byte;

    index = 15;
    do {
        g_battle_menu_allocator_slot_records[index][0] = -1;
        index--;
    } while (index >= 0);

    index = 52;
    allocation_byte = &g_battle_menu_buffer_allocation_map[52];
    do {
        *allocation_byte = 0;
        index--;
        allocation_byte--;
    } while (index >= 0);

    index = 0;
    do {
        g_battle_menu_slot_owner_thread_ids[index] = 0;
        g_battle_menu_slot_states[index] = 0;
        index++;
    } while (index < 3);
}
