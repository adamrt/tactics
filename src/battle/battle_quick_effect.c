#include "fft/battle.h"
#include "psx/types.h"

extern battle_action_data_t* g_target_current_action;

void battle_quick_effect(void) {
    g_target_current_action->ct_change = 0xFF;
    g_target_current_action->attack_type = 1;
}
