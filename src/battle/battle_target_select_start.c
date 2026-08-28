#include "fft/battle.h"

extern void battle_stop_game_flow(void);
extern battle_misc_data_t* battle_get_casting_unit_misc_data(void);
extern s32 system_function_setup(s32, s32, u8, s32, s32);
extern void set_at_list_active(void);
extern s32 g_battle_game_state;

void battle_target_select_start(void) {
    battle_misc_data_t* unit;
    battle_stats_t* stats;

    battle_stop_game_flow();
    g_battle_game_state = 0x1F;
    unit = battle_get_casting_unit_misc_data();
    stats = unit->battle_data;
    system_function_setup(1, 0, stats->misc_unit_id, 0, 1);
    set_at_list_active();
}
