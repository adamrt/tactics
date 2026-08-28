#include "fft/battle.h"
#include "psx/types.h"

extern s32 g_battle_cursor_x;
extern s32 g_battle_cursor_z;
extern s32 g_battle_cursor_y;
extern battle_misc_data_t* battle_get_misc_data_at_map_coords_2(s32, s32, s32);
extern battle_misc_data_t* battle_get_source_unit_misc_data(void);
extern void battle_store_unit_names_and_some_event_block_data(s32, u8, u8);

void battle_store_casting_units_name_and_data_selected_by_cursor(void) {
    battle_misc_data_t* target;
    battle_misc_data_t* source;

    target = battle_get_misc_data_at_map_coords_2(g_battle_cursor_x, g_battle_cursor_y, g_battle_cursor_z);
    source = battle_get_source_unit_misc_data();
    if (target != 0) {
        battle_store_unit_names_and_some_event_block_data(5, source->battle_data->misc_unit_id, target->battle_data->misc_unit_id);
    } else {
        battle_store_unit_names_and_some_event_block_data(2, source->battle_data->misc_unit_id, 0xFF);
    }
}
