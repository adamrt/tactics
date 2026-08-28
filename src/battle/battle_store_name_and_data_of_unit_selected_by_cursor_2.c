#include "fft/battle.h"

extern void battle_store_unit_names_and_some_event_block_data(s32 a, s32 b, u8 c);
extern battle_misc_data_t* battle_get_misc_data_at_map_coords_2(s32 x, s32 y, s32 z);
extern void battle_get_source_unit_misc_data(void);
extern s32 g_battle_cursor_x;
extern s32 g_battle_cursor_z;
extern s32 g_battle_cursor_y;

void battle_store_name_and_data_of_unit_selected_by_cursor_2(void) {
    battle_misc_data_t* misc = battle_get_misc_data_at_map_coords_2(g_battle_cursor_x, g_battle_cursor_y, g_battle_cursor_z);
    battle_get_source_unit_misc_data();
    if (misc != 0) {
        battle_store_unit_names_and_some_event_block_data(4, 0xFF, misc->battle_data->misc_unit_id);
    } else {
        battle_store_unit_names_and_some_event_block_data(1, 0xFF, 0xFF);
    }
}
