#include "fft/battle.h"
#include "psx/types.h"

extern battle_action_data_t* g_target_current_action;
extern int calculate_magical_evade(void);
extern int battle_calculate_magic_accuracy(void);
extern void battle_calculate_hp_percent_damage(void);
extern void apply_weather_elemental_effects(void);
extern void apply_ability_elemental_effects(void);
extern int battle_apply_elemental_absorption_and_status_proc(void);
extern void apply_status_to_action(void);

void battle_formula_magic_hp_percent_damage(void) {
    if (calculate_magical_evade() == 0) {
        if (battle_calculate_magic_accuracy() == 0) {
            battle_calculate_hp_percent_damage();
            apply_weather_elemental_effects();
            apply_ability_elemental_effects();
            if (g_target_current_action->hit != 0) {
                if (battle_apply_elemental_absorption_and_status_proc() == 0) {
                    apply_status_to_action();
                }
            }
        }
    }
}
