#include "psx/types.h"

extern s16 g_equip_scroll_base_index;
extern void equip_init_scrollable_list_menu_core(const s16* entries,
    s32 selected_index,
    const void* entry_data);

void equip_init_scrollable_list_menu(const s16* entries, s32 selected_index,
    s32 scroll_base_index,
    const void* entry_data) {
    equip_init_scrollable_list_menu_core(entries, selected_index, entry_data);
    g_equip_scroll_base_index = scroll_base_index;
}
