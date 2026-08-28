#include "fft/battle.h"
#include "psx/types.h"

extern battle_action_data_t* g_target_current_action;

void battle_force_attack_miss(void) {
    g_target_current_action->hit = 0;
    g_target_current_action->miss_type = 7;
    /* The accuracy field is cleared as a halfword (sh). */
    g_target_current_action->attack_accuracy = 0;
}
