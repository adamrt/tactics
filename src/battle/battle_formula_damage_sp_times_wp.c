#include "fft/battle.h"
#include "psx/types.h"

extern battle_action_data_t* g_target_current_action;
extern battle_stats_t* g_current_attacker;
extern u8 g_current_ability_weapon_power;
extern s16 g_current_ability_xa;
extern s16 g_current_ability_ya;

extern void battle_catch(void);
extern s32 battle_physical_evade_calculation(void);
extern void battle_apply_physical_status_support_compatibility(void);
extern void battle_store_xa_times_ya_damage(void);
extern void battle_elemental_damage_modification(void);
extern void battle_elemental_absorption(void);

void battle_formula_damage_sp_times_wp(void) {
    battle_catch();
    if (g_target_current_action->hit == 0) {
        return;
    }
    if (battle_physical_evade_calculation() != 0) {
        return;
    }
    g_current_ability_xa = g_current_attacker->attributes[2];
    g_current_ability_ya = g_current_ability_weapon_power;
    battle_apply_physical_status_support_compatibility();
    battle_store_xa_times_ya_damage();
    battle_elemental_damage_modification();
    if (g_target_current_action->hit == 0) {
        return;
    }
    battle_elemental_absorption();
}
