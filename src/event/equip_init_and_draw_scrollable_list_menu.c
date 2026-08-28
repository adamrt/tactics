#include "psx/types.h"

extern void equip_init_scrollable_list_menu(const s16* entries,
    s32 selected_index,
    s32 scroll_base_index,
    const void* entry_data);
extern void equip_draw_scrollable_list_menu(const u8* commands);

void equip_init_and_draw_scrollable_list_menu(const s16* entries,
    s32 selected_index,
    s32 scroll_base_index,
    const void* entry_data,
    const u8* commands) {
    equip_init_scrollable_list_menu(entries, selected_index, scroll_base_index,
        entry_data);
    equip_draw_scrollable_list_menu(commands);
}
