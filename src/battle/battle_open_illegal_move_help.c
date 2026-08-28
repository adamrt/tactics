#include "fft/battle.h"
#include "psx/types.h"

extern void battle_stop_game_flow(void);
extern battle_misc_data_t* battle_get_source_unit_misc_data(void);
extern s32 g_battle_game_state;
extern void system_function_setup(s32 a, s32 b, u8 c, s32 d, s32 e);

void battle_open_illegal_move_help(void) {
    battle_misc_data_t* unit;
    battle_stop_game_flow();
    g_battle_game_state = BATTLE_GAME_STATE_ILLEGAL_MOVE_MENU;
    unit = battle_get_source_unit_misc_data();
    system_function_setup(2, 2, unit->battle_data->misc_unit_id, 0, unit->team_flags & 8);
}
