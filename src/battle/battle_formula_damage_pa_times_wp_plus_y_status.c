#include "fft/battle.h"
#include "psx/types.h"

extern battle_action_data_t* g_target_current_action;
extern s32 battle_physical_evade_calculation(void);
extern void battle_store_pa_and_weapon_power_plus_y(void);
extern void battle_apply_weapon_element_strengthen(void);
extern void battle_calculate_physical_damage(void);
extern void battle_elemental_damage_modification(void);
extern void battle_elemental_absorption(void);
extern void battle_apply_status(void);

/* Formula 0x2D: damage (PA * (WP + Y)), 100% status. */
void battle_formula_damage_pa_times_wp_plus_y_status(void) {
    if (battle_physical_evade_calculation() == 0) {
        battle_store_pa_and_weapon_power_plus_y();
        battle_apply_weapon_element_strengthen();
        battle_calculate_physical_damage();
        battle_elemental_damage_modification();
        if (g_target_current_action->hit != 0) {
            battle_elemental_absorption();
            battle_apply_status();
        }
    }
}
