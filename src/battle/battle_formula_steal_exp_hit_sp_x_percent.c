#include "fft/battle.h"
#include "psx/types.h"

extern battle_action_data_t* g_target_current_action;
extern s32 g_battle_action_state;

extern s32 calculate_physical_evade(void);
extern void battle_store_speed_and_x(void);
extern void battle_apply_attack_up_and_martial_arts(void);
extern void battle_apply_attacker_berserk_frog(void);
extern void apply_defense_up(void);
extern void apply_physical_target_status_modifiers(void);
extern void apply_compatibility(void);
extern void battle_store_xa_plus_ya_status_damage(void);
extern void calculate_hp_damage_accuracy(void);
extern void func_80186814(void);

void battle_formula_steal_exp_hit_sp_x_percent(void) {
    if (calculate_physical_evade() == 0) {
        battle_store_speed_and_x();
        battle_apply_attack_up_and_martial_arts();
        battle_apply_attacker_berserk_frog();
        apply_defense_up();
        apply_physical_target_status_modifiers();
        apply_compatibility();
        battle_store_xa_plus_ya_status_damage();
        calculate_hp_damage_accuracy();
        if (g_target_current_action->hit != 0 || g_battle_action_state != 0) {
            func_80186814();
        }
    }
}
