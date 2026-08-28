#include "fft/battle.h"
#include "psx/types.h"

extern battle_action_data_t* g_target_current_action;
extern int calculate_golem_accuracy(void);

void battle_formula_set_golem(void) {
    if (calculate_golem_accuracy() == 0) {
        /* Halfword store over special_effect/special_flags_2: Golem = 0x01. */
        g_target_current_action->special_effect = 1;
        g_target_current_action->attack_type = 1;
    }
}
