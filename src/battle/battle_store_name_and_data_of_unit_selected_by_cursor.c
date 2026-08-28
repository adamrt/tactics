#include "fft/battle.h"

extern battle_misc_data_t* battle_get_misc_data_at_map_coords_2(s32 map_x, s32 map_y, s32 map_z);
extern void store_unit_names_and_event_block_data(s32 arg0, s32 arg1, s32 arg2);
extern s32 g_battle_cursor_x;
extern s32 g_battle_cursor_y;
extern s32 g_battle_cursor_z;

void battle_store_name_and_data_of_unit_selected_by_cursor(void) {
    battle_misc_data_t* misc;
    s32 mode;
    s32 arg1;

    misc = battle_get_misc_data_at_map_coords_2(g_battle_cursor_x, g_battle_cursor_y, g_battle_cursor_z);
    if (misc != 0) {
        mode = 2;
        arg1 = misc->battle_data->misc_unit_id;
    } else {
        mode = 1;
        arg1 = 0xFF;
    }
    store_unit_names_and_event_block_data(mode, arg1, 0xFF);
}
