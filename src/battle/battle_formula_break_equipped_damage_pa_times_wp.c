#include "fft/battle.h"
#include "psx/types.h"

extern battle_action_data_t* g_target_current_action;

extern s32 battle_physical_evade_calculation(void);
extern s32 func_801879C8(void);
extern void battle_nullify_action(void);
extern void battle_maintenance(void);
extern void battle_store_pa_and_weapon_power(void);
extern void battle_apply_weapon_element_strengthen(void);
extern void battle_calculate_physical_damage(void);
extern void battle_elemental_damage_modification(void);
extern void battle_elemental_absorption(void);

void battle_formula_break_equipped_damage_pa_times_wp(void) {
    battle_action_data_t* action;

    if (battle_physical_evade_calculation() != 0) {
        return;
    }
    if (func_801879C8() != 0) {
        battle_nullify_action();
        g_target_current_action->miss_type = 7;
        return;
    }
    battle_maintenance();
    action = g_target_current_action;
    if (action->hit == 0) {
        return;
    }
    /* special_effect/special_flags_2 are written as one halfword (sh). */
    action->special_effect = 4;
    battle_store_pa_and_weapon_power();
    battle_apply_weapon_element_strengthen();
    battle_calculate_physical_damage();
    battle_elemental_damage_modification();
    if (g_target_current_action->hit == 0) {
        return;
    }
    battle_elemental_absorption();
}
