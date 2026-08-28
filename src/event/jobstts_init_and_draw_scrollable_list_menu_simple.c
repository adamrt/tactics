#include "psx/types.h"

extern void jobstts_init_scrollable_list_menu_core(const s16* entries,
    s32 selected_index,
    const void* data);
extern void func_801e3698(const u8* data);

void jobstts_init_and_draw_scrollable_list_menu_simple(const s16* entries,
    s32 selected_index,
    const void* data,
    const u8* commands) {
    jobstts_init_scrollable_list_menu_core(entries, selected_index, data);
    func_801e3698(commands);
}
