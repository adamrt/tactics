#include "fft/battle.h"
#include "psx/types.h"

extern s32 g_battle_cursor_x;
extern s32 g_battle_cursor_y;
extern s32 g_battle_cursor_z;
extern s32 g_battle_game_state;
extern s32 g_battle_status_flag;

extern battle_misc_data_t* battle_get_misc_data_at_map_coords_2(s32, s32, s32);
extern void battle_stop_game_flow(void);
extern void store_unit_names_and_event_block_data(s32 arg0, s32 arg1, s32 arg2);
extern s32 get_idle_action_menu_id(s32 unit_id);
extern void build_idle_action_menu(s32 menu_id);

void battle_non_active_unit_idle_action_menu(void) {
    battle_misc_data_t* misc;
    battle_stats_t* unit;
    s32 menu_id;

    misc = battle_get_misc_data_at_map_coords_2(g_battle_cursor_x, g_battle_cursor_y,
        g_battle_cursor_z);
    if (misc == 0) {
        return;
    }
    battle_stop_game_flow();
    unit = misc->battle_data;
    g_battle_game_state = 4;
    store_unit_names_and_event_block_data(3, unit->misc_unit_id, 0);
    menu_id = get_idle_action_menu_id(misc->battle_data->misc_unit_id);
    if (g_battle_status_flag != 0) {
        if (menu_id == 0xF) {
            menu_id = 0x11;
        } else if (menu_id == 0x10) {
            menu_id = 0x12;
        }
    }
    build_idle_action_menu(menu_id);
}
