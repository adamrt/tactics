#include "fft/battle.h"

extern void battle_stop_game_flow(void);
extern battle_misc_data_t* battle_get_source_unit_misc_data(void);
extern void battle_move_cursor_to_unit(battle_misc_data_t* misc_data);
extern void store_unit_names_and_event_block_data(s32 mode, u8 unit_id,
    s32 misc_id);
extern s32 get_idle_action_menu_id(u8 unit_id);
extern void build_idle_action_menu(s32 menu_id);

extern s32 g_battle_casting_unit_id;
extern s32 g_battle_game_state;

void battle_open_active_unit_idle_action_menu(void) {
    battle_misc_data_t* misc_data;
    battle_stats_t* battle_stats;

    battle_stop_game_flow();
    misc_data = battle_get_source_unit_misc_data();
    g_battle_casting_unit_id = misc_data->unit_id;
    battle_move_cursor_to_unit(misc_data);
    g_battle_game_state = 4;

    if (misc_data != 0) {
        battle_stats = misc_data->battle_data;
        if (battle_stats == 0) {
            goto build_menu;
        }
        store_unit_names_and_event_block_data(3, battle_stats->misc_unit_id, 0);
    }
    battle_stats = misc_data->battle_data;

build_menu:
    build_idle_action_menu(get_idle_action_menu_id(battle_stats->misc_unit_id));
}
