#include "psx/types.h"

extern void battle_handle_free_cursor_input(void);
extern s32 main_get_otag(void);
extern void render_menu_selection_data(s32, s32);
extern s32 battle_load_map_data_stage_0x76(void);
extern u8* battle_get_unit_misc_data_by_misc_id(s32);
extern void battle_update_display_by_misc_id(u8);
extern s32 g_controller_input_raw;
extern s32 g_deep_dungeon_map_load_in_progress;

/* Per-frame tick while the Deep Dungeon overworld map is up: poll the
   cursor, render the menu, drive the map-load state machine, then when
   the map is fully loaded refresh every live unit's display and clear
   the load-in-progress flag (g_deep_dungeon_map_load_in_progress). */
s32 battle_deep_dungeon_map_and_animation(void) {
    s32 misc_id;

    battle_handle_free_cursor_input();
    render_menu_selection_data(main_get_otag(), g_controller_input_raw);
    if (battle_load_map_data_stage_0x76() != 0) {
        return 0;
    }
    misc_id = 0;
    do {
        u8* misc = battle_get_unit_misc_data_by_misc_id(misc_id & 0xFFFF);
        misc_id++;
        if (misc != 0) {
            battle_update_display_by_misc_id(misc[4]);
        }
    } while (misc_id < 0x10);
    g_deep_dungeon_map_load_in_progress = 0;
    return 1;
}

/* padding */
