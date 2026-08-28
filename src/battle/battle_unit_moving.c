#include "fft/battle.h"
#include "psx/types.h"

extern void battle_stop_game_flow(void);
extern void battle_store_name_and_data_of_unit_selected_by_cursor(void);
extern battle_misc_data_t* battle_get_casting_unit_misc_data(void);
extern void battle_save_unit_previous_state(battle_misc_data_t* unit);
extern battle_misc_data_t* battle_get_unit_misc_data_by_misc_id(s32 misc_id);
extern void battle_clear_at_list_active(void);
extern s32 g_battle_game_state;
extern s32 g_animation_continue_check;

void battle_unit_moving(void) {
    battle_misc_data_t* unit;

    battle_stop_game_flow();
    g_battle_game_state = BATTLE_GAME_STATE_UNIT_MOVING;
    battle_store_name_and_data_of_unit_selected_by_cursor();
    unit = battle_get_casting_unit_misc_data();
    battle_save_unit_previous_state(unit);
    if (unit->mount_rider_value == 2) {
        battle_misc_data_t* mount = battle_get_unit_misc_data_by_misc_id(unit->mount_rider_id);
        if (mount != 0) {
            battle_save_unit_previous_state(mount);
        }
    }
    *(s32*)&unit->_pad03c[0] = 0x2000;
    unit->movement_path_offset = 0;
    g_animation_continue_check = 0;
    battle_clear_at_list_active();
}
