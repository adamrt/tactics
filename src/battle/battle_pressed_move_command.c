#include "fft/battle.h"

extern s32 g_battle_game_state;
extern void battle_stop_game_flow(void);
extern battle_misc_data_t* get_acting_unit_misc_data(void);
extern void system_function_setup(s32, s32, s32, s32, s32);

void battle_pressed_move_command(void) {
    battle_misc_data_t* unit;

    battle_stop_game_flow();
    g_battle_game_state = BATTLE_GAME_STATE_UNIT_MOVE;
    unit = get_acting_unit_misc_data();
    system_function_setup(1, 0, unit->battle_data->misc_unit_id, 0,
        unit->team_flags & 8);
}
