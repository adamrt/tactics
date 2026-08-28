#include "psx/types.h"

extern void jobstts_init_scrollable_list_menu(void* entries, void* selected,
    s32 value, void* data);
extern void func_801e3698(void* data);

void jobstts_init_and_draw_scrollable_list_menu(void* entries, void* selected,
    s32 value, void* data,
    void* commands) {
    jobstts_init_scrollable_list_menu(entries, selected, value, data);
    func_801e3698(commands);
}
