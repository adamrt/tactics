#include "fft/battle.h"
#include "psx/types.h"

extern s32 g_battle_game_state;
extern s32 g_battle_cursor_x;
extern s32 g_battle_cursor_z;
extern s32 g_battle_cursor_y;

extern void battle_move_cursor_to_unit(s32);
extern void battle_store_name_and_data_of_unit_selected_by_cursor(void);
extern void battle_store_name_and_data_of_unit_selected_by_cursor_2(void);

void battle_free_cursor_selection_routine(battle_misc_data_t* unit, s32 misc_id) {
    s32 old_x;
    s32 old_z;
    s32 old_y;
    s32 nx;
    s32 nz;
    s32 ny;

    old_x = g_battle_cursor_x;
    old_z = g_battle_cursor_z;
    old_y = g_battle_cursor_y;
    if (misc_id != 0) {
        battle_move_cursor_to_unit(misc_id);
    } else {
        nx = unit->target_panel_x;
        nz = unit->target_map_level;
        ny = unit->target_panel_y;
        g_battle_cursor_x = nx;
        g_battle_cursor_z = nz;
        g_battle_cursor_y = ny;
    }
    if (((g_battle_cursor_x != old_x) | (g_battle_cursor_z != old_z) | (g_battle_cursor_y != old_y)) != 0) {
        switch (g_battle_game_state) {
        case BATTLE_GAME_STATE_FREE_CURSOR:
        case BATTLE_GAME_STATE_CLOSE_MOVE_HELP:
        case BATTLE_GAME_STATE_TARGET_SELECT:
            battle_store_name_and_data_of_unit_selected_by_cursor();
            break;
        case BATTLE_GAME_STATE_TARGETING_RANGE:
            battle_store_name_and_data_of_unit_selected_by_cursor_2();
            break;
        }
    }
}
