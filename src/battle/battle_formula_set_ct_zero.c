#include "fft/battle.h"
#include "psx/types.h"

extern battle_action_data_t* g_target_current_action;
extern int calculate_magical_evade(void);
extern int battle_calculate_magic_accuracy_no_elemental(void);

void battle_formula_set_ct_zero(void) {
    if (calculate_magical_evade() == 0) {
        if (battle_calculate_magic_accuracy_no_elemental() == 0) {
            g_target_current_action->ct_change = 0x7f;
            g_target_current_action->attack_type = 1;
        }
    }
}
