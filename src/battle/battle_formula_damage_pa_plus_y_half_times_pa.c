#include "fft/battle.h"
#include "psx/types.h"

extern battle_action_data_t* g_target_current_action;

extern s32 calculate_physical_evade(void);
extern void battle_store_pa_and_pa_plus_y_divided_by_two(void);
extern void battle_apply_elemental_strengthen(void);
extern void battle_apply_attack_up_and_martial_arts(void);
extern void battle_apply_physical_status_support_compatibility(void);
extern void calculate_critical_hit(void);
extern void battle_store_xa_times_ya_damage(void);
extern void apply_weather_elemental_effects(void);
extern void apply_ability_elemental_effects(void);
extern void apply_elemental_absorption(void);
extern s32 conditional_status_proc_roll(void);
extern void apply_status_to_action(void);

void battle_formula_damage_pa_plus_y_half_times_pa(void) {
    if (calculate_physical_evade() == 0) {
        battle_store_pa_and_pa_plus_y_divided_by_two();
        battle_apply_elemental_strengthen();
        battle_apply_attack_up_and_martial_arts();
        battle_apply_physical_status_support_compatibility();
        calculate_critical_hit();
        battle_store_xa_times_ya_damage();
        apply_weather_elemental_effects();
        apply_ability_elemental_effects();
        if (g_target_current_action->hit != 0) {
            apply_elemental_absorption();
            if (conditional_status_proc_roll() == 0) {
                apply_status_to_action();
            }
        }
    }
}
