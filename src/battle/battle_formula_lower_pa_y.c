#include "fft/battle.h"
#include "psx/types.h"

extern battle_action_data_t* g_target_current_action;
extern u8 g_current_ability_y;
extern s32 battle_magical_evade_calculation(void);
extern s32 battle_calculate_magic_accuracy_without_faith(void);

/* Formula 0x55: -PA (Y), hit (MA+X)%. */
void battle_formula_lower_pa_y(void) {
    if (battle_magical_evade_calculation() != 0) {
        return;
    }
    if (battle_calculate_magic_accuracy_without_faith() != 0) {
        return;
    }
    g_target_current_action->pa_change = g_current_ability_y & 0x7F;
    g_target_current_action->attack_type = 1;
}
