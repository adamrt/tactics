#include "fft/battle.h"
#include "psx/types.h"

extern battle_action_data_t* g_target_current_action;
extern void battle_store_pa_and_x(void);
extern void battle_apply_attack_up_and_martial_arts(void);
extern void func_80184964(void);
extern void battle_store_xa_plus_ya_status_damage(void);
extern void func_80187510(void);
extern s32 battle_apply_status_and_check_undead(void);
extern void battle_calculate_hp_percent_damage(void);
extern void battle_undead_reversal(void);

/* Formula 0x35: heal (Y)% of max HP, hit (PA+X)%. */
void battle_formula_heal_y_percent_hit_pa_x_percent(void) {
    battle_store_pa_and_x();
    battle_apply_attack_up_and_martial_arts();
    func_80184964();
    battle_store_xa_plus_ya_status_damage();
    func_80187510();
    if (g_target_current_action->hit != 0 && battle_apply_status_and_check_undead() != 0) {
        battle_calculate_hp_percent_damage();
        battle_undead_reversal();
    }
}
