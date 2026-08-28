#include "fft/battle.h"
#include "psx/types.h"

extern battle_action_data_t* g_target_current_action;
extern battle_stats_t* g_current_target;
extern s32 battle_magical_evade_calculation(void);
extern s32 battle_calculate_magic_accuracy_without_faith(void);
extern void battle_force_attack_miss(void);

/* Formula 0x59: -Level (1), hit (MA+X)%. */
void battle_formula_lower_level_by_one(void) {
    battle_action_data_t* action;

    if (battle_magical_evade_calculation() == 0) {
        if (battle_calculate_magic_accuracy_without_faith() == 0) {
            if (g_current_target->level < 2) {
                battle_force_attack_miss();
            }
            action = g_target_current_action;
            /* special_effect/special_flags_2 written as one halfword: -1 Level. */
            action->special_effect = 0x100;
            action->attack_type = 1;
        }
    }
}
