#include "psx/types.h"

extern u32 g_open_runtime_flags;
extern u8* g_open_file_destination;
extern s32 g_open_current_openbk_image_id;
extern u8* g_open_opntex_data;
extern s32 D_80085CBC;
extern s32 D_80085CC0;
extern u32 g_open_previous_button_input;
extern u32 g_open_new_button_presses;
extern u32 g_open_current_button_input;
extern s32 g_open_formation_entry_mask;
extern s32 g_open_formation_otag_index;
extern u32 g_open_script_dispatch_flags;
extern s32 D_800855F0;

void open_initialize_runtime_state(void) {
    g_open_runtime_flags = 0x1041;
    g_open_file_destination = (u8*)0x801d0000;
    g_open_current_openbk_image_id = -1;
    g_open_opntex_data = (u8*)0x80140000;
    D_80085CBC = 2;
    D_80085CC0 = 2;
    g_open_previous_button_input = 0;
    g_open_new_button_presses = 0;
    g_open_current_button_input = 0;
    g_open_formation_entry_mask = 0;
    g_open_formation_otag_index = 4;
    g_open_script_dispatch_flags = 0;
    D_800855F0 = 0;
}
