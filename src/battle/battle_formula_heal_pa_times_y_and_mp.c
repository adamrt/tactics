#include "fft/battle.h"
#include "psx/types.h"

extern battle_action_data_t* g_target_current_action;
extern void battle_store_pa_and_y(void);
extern void battle_apply_attack_up_and_martial_arts(void);
extern void func_80184964(void);
extern void battle_store_xa_times_ya_damage(void);

/* Formula 0x34: heal (PA*Y) HP and (PA*Y/2) MP. */
void battle_formula_heal_pa_times_y_and_mp(void) {
    battle_action_data_t* action;
    u16 amount;

    battle_store_pa_and_y();
    battle_apply_attack_up_and_martial_arts();
    func_80184964();
    battle_store_xa_times_ya_damage();
    action = g_target_current_action;
    amount = action->hp_damage;
    action->hp_damage = 0;
    action->hp_healing = amount;
    action->attack_type = 0x50;
    /* hp_healing is re-read signed (lh) for the halving. */
    action->mp_healing = *(s16*)&action->hp_healing / 2;
}
