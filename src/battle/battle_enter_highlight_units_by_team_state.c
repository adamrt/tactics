#include "fft/battle.h"

extern s32 g_battle_controller_input;
extern s32 g_controller_input_copy_12;
extern s32 g_battle_game_state;
extern void battle_start_game_flow(void);
extern void highlight_units_by_team_2(void);
extern void battle_clear_at_list_active(void);

void battle_enter_highlight_units_by_team_state(void) {
    battle_start_game_flow();
    g_battle_game_state = BATTLE_GAME_STATE_HIGHLIGHT_UNITS;
    g_controller_input_copy_12 = g_battle_controller_input;
    g_battle_controller_input = 2;
    highlight_units_by_team_2();
    battle_clear_at_list_active();
}
