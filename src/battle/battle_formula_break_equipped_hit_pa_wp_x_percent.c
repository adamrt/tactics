#include "fft/battle.h"
#include "psx/types.h"

extern battle_action_data_t* g_target_current_action;
extern u8 g_battle_801938e9;

extern s32 func_801879C8(void);
extern void battle_switch_ability_to_default_attack(void);
extern s32 battle_physical_evade_calculation(void);
extern void battle_store_pa_and_weapon_power_plus_y(void);
extern s32 battle_calculate_physical_accuracy(void);
extern void battle_maintenance(void);

void battle_formula_break_equipped_hit_pa_wp_x_percent(void) {
    battle_action_data_t* action;

    if (func_801879C8() != 0) {
        g_battle_801938e9 = 1;
        battle_switch_ability_to_default_attack();
        return;
    }
    g_battle_801938e9 = 0;
    if (battle_physical_evade_calculation() != 0) {
        return;
    }
    battle_store_pa_and_weapon_power_plus_y();
    if (battle_calculate_physical_accuracy() != 0) {
        /* The target stores special_effect/special_flags_2 as one halfword. */
        g_target_current_action->special_effect = 0;
        return;
    }
    battle_maintenance();
    action = g_target_current_action;
    if (action->hit != 0) {
        action->special_effect = 4;
    }
}
