#include "fft/battle.h"
#include "psx/types.h"

extern void battle_stop_game_flow(void);
extern battle_misc_data_t* battle_get_source_unit_misc_data(void);
extern void battle_system_function_setup_routine(s32, s32, u8, s32, s32);
extern s32 g_battle_game_state;

void battle_target_out_of_range(void) {
    battle_misc_data_t* unit;
    battle_stats_t* stats;

    battle_stop_game_flow();
    g_battle_game_state = BATTLE_GAME_STATE_ILLEGAL_RANGE;
    unit = battle_get_source_unit_misc_data();
    stats = unit->battle_data;
    battle_system_function_setup_routine(4, 5, stats->misc_unit_id, 0, unit->team_flags & 8);
}
