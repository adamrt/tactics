#include "fft/battle.h"
#include "psx/types.h"

extern void battle_stop_game_flow(void);
extern battle_misc_data_t* battle_get_casting_unit_misc_data(void);
extern battle_misc_data_t* battle_get_unit_misc_data_by_battle_id(u8 battle_id);
extern void battle_move_cursor_to_unit(battle_misc_data_t* unit);
extern void battle_rotate_camera_when_unit_tile_not_visible(battle_misc_data_t* unit);
extern void battle_store_unit_names_and_some_event_block_data(s32, s32, s32);
extern s32 g_battle_game_state;

void battle_target_display(void) {
    battle_stats_t* cast;
    battle_misc_data_t* unit;
    battle_stats_t* target;

    battle_stop_game_flow();
    g_battle_game_state = BATTLE_GAME_STATE_TARGET_DISPLAY;
    cast = battle_get_casting_unit_misc_data()->battle_data;
    unit = battle_get_unit_misc_data_by_battle_id(cast->auto_battle_target);
    battle_move_cursor_to_unit(unit);
    battle_rotate_camera_when_unit_tile_not_visible(unit);
    if (unit != 0) {
        target = unit->battle_data;
        if (target != 0) {
            battle_store_unit_names_and_some_event_block_data(3, target->misc_unit_id, 0);
        }
    }
}
