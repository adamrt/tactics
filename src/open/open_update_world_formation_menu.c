#include "psx/types.h"

extern u32 g_open_runtime_flags;
extern u32 g_open_formation_entry_mask;
extern s32 g_active_graphics_buffer_index;
extern u32 g_open_otags[2][16];
extern s32 g_open_formation_otag_index;
extern u32 g_open_current_button_input;

extern void world_set_formation_menu_entry_mask(u32 mask);
extern void func_80107e10(u32* otag, u32 button_input);

void open_update_world_formation_menu(void) {
    if (g_open_runtime_flags & 0x400) {
        u32 entry_mask = g_open_formation_entry_mask;

        g_active_graphics_buffer_index ^= 1;
        world_set_formation_menu_entry_mask(~entry_mask);
        func_80107e10(&g_open_otags[g_active_graphics_buffer_index ^ 1]
                                   [g_open_formation_otag_index],
            g_open_current_button_input);
        g_active_graphics_buffer_index ^= 1;
    }
}
