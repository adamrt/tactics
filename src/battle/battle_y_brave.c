#include "fft/battle.h"
#include "psx/types.h"

extern u8 g_current_ability_y;
extern battle_action_data_t* g_target_current_action;

void battle_y_brave(void) {
    g_target_current_action->brave_change = g_current_ability_y & 0x7F;
    g_target_current_action->attack_type = 1;
}
