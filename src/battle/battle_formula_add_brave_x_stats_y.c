#include "fft/battle.h"
#include "psx/types.h"

extern battle_action_data_t* g_target_current_action;
extern u8 g_current_ability_x;
extern u8 g_current_ability_y;

/* Formula 0x3B: +Brave (X), +PA/MA/Speed (Y). */
void battle_formula_add_brave_x_stats_y(void) {
    s32 y;

    g_target_current_action->brave_change = g_current_ability_x | 0x80;
    y = g_current_ability_y | 0x80;
    g_target_current_action->pa_change = y;
    g_target_current_action->ma_change = y;
    g_target_current_action->sp_change = y;
    g_target_current_action->attack_type = 1;
}
