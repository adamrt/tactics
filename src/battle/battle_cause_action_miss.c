#include "fft/battle.h"
#include "psx/types.h"

extern battle_action_data_t* g_target_current_action;

void battle_cause_action_miss(void) {
    g_target_current_action->hit = 0;
    g_target_current_action->miss_type = 6;
}
