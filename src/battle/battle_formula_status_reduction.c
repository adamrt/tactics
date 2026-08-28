#include "fft/battle.h"
#include "psx/types.h"

extern battle_action_data_t* g_target_current_action;
extern int calculate_magical_evade(void);
extern void battle_store_ma_and_y(void);
extern void battle_apply_elemental_strengthen(void);
extern void battle_apply_magical_support_status_compatibility(void);
extern void battle_store_xa_plus_ya_status_damage(void);
extern void apply_faith_to_damage(void);
extern void calculate_hp_damage_accuracy(void);
extern void apply_status_reduction(void);

void battle_formula_status_reduction(void) {
    if (calculate_magical_evade() == 0) {
        battle_store_ma_and_y();
        battle_apply_elemental_strengthen();
        battle_apply_magical_support_status_compatibility();
        battle_store_xa_plus_ya_status_damage();
        apply_faith_to_damage();
        calculate_hp_damage_accuracy();
        if (g_target_current_action->hit == 0) {
            /* The target clears the bit in the special_effect halfword. */
            g_target_current_action->special_effect &= ~4;
        } else {
            apply_status_reduction();
        }
    }
}
