#include "fft/battle.h"
#include "psx/types.h"

extern battle_action_data_t* g_target_current_action;
extern void battle_store_pa_and_x(void);
extern void battle_apply_attack_up_and_martial_arts(void);
extern void battle_apply_attacker_berserk_frog(void);
extern void func_80184964(void);
extern void battle_store_xa_plus_ya_status_damage(void);
extern void func_80187510(void);
extern void func_80187F24(void);

/* Formula 0x33: hit (PA+X)%. */
void battle_formula_hit_pa_x_percent(void) {
    battle_store_pa_and_x();
    battle_apply_attack_up_and_martial_arts();
    battle_apply_attacker_berserk_frog();
    func_80184964();
    battle_store_xa_plus_ya_status_damage();
    func_80187510();
    if (g_target_current_action->hit != 0) {
        func_80187F24();
    }
}
