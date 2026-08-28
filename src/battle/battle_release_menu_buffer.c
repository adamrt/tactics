#include "psx/types.h"

extern s32 g_battle_menu_buffer_slots[6];
extern u8 D_8016e324[];
extern u8 D_8016e328[];
extern u8 g_battle_menu_buffer_records[];
extern u8 g_battle_menu_buffer_thread_ids_base[];

void stop_current_event_thread(void);

void battle_release_menu_buffer(s32 buffer) {
    s32 slot;
    s32 offset;
    s32 empty;

    if (buffer == -1) {
        return;
    }

    slot = 0;
    empty = -1;
    offset = 0x118;
    do {
        if (g_battle_menu_buffer_slots[slot] == buffer) {
            g_battle_menu_buffer_slots[slot] = empty;
            g_battle_menu_buffer_slots[slot + 1] = empty;
            *(s32*)&D_8016e324[offset] = 0;
            *(s32*)&g_battle_menu_buffer_records[offset] = 0;
            *(s32*)&D_8016e328[offset] = 0;
            *(s32*)&g_battle_menu_buffer_thread_ids_base[offset] = 0;
            return;
        }
        offset += 0x230;
        slot += 2;
    } while (slot < 6);

    stop_current_event_thread();
}
