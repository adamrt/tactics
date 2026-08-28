#include "fft/battle.h"
#include "psx/types.h"

extern battle_action_data_t* g_target_current_action;
extern u8 g_current_ability_y;

/* Formula 0x36: +PA (Y). */
void battle_formula_add_pa_y(void) {
    g_target_current_action->pa_change = g_current_ability_y | 0x80;
    g_target_current_action->attack_type = 1;
}
