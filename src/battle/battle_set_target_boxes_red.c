#include "fft/battle.h"

extern battle_misc_data_t* battle_get_source_unit_misc_data(void);
extern void battle_stop_game_flow(void);
extern void set_partial_tile_color(s32 a, s32 b);
extern void battle_store_name_and_data_of_unit_selected_by_cursor_2(void);
extern void set_at_list_active(void);
extern void battle_clear_at_list_active(void);
extern void select_target_tile(void);
extern void open_idle_action_menu(void);
extern s32 g_battle_game_state;

s32 battle_set_target_boxes_red(void) {
    battle_misc_data_t* unit;

    unit = battle_get_source_unit_misc_data();
    unit->unit_check = 0;
    switch (unit->ability_preview_phase) {
    case 0:
    case 1:
        battle_stop_game_flow();
        g_battle_game_state = 0x17;
        set_partial_tile_color(2, 2);
        battle_store_name_and_data_of_unit_selected_by_cursor_2();
        if ((unit->team_flags & 8) != 0) {
            set_at_list_active();
        } else {
            battle_clear_at_list_active();
        }
        break;
    case 2:
        battle_stop_game_flow();
        select_target_tile();
        battle_store_name_and_data_of_unit_selected_by_cursor_2();
        break;
    case -1:
    case 3:
        open_idle_action_menu();
        break;
    }
    return unit->ability_preview_phase;
}
