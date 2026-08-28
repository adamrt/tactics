#include "fft/battle.h"
#include "psx/types.h"

extern battle_action_data_t* g_target_current_action;
extern battle_stats_t* g_target_unit_data;
extern battle_stats_t* g_current_attacker;
extern void battle_store_ma_and_x(void);
extern void func_80184964(void);
extern void battle_store_xa_plus_ya_status_damage(void);
extern void func_80187510(void);
extern void battle_force_attack_miss(void);
extern void func_80187F24(void);

/* Formula 0x29: opposite sex only, hit (MA+X)%. */
void battle_formula_opposite_sex_hit_ma_x_percent(void) {
    battle_store_ma_and_x();
    func_80184964();
    battle_store_xa_plus_ya_status_damage();
    func_80187510();
    if (g_target_current_action->hit != 0) {
        if ((g_target_unit_data->unit_flags & 0xE0) == (g_current_attacker->unit_flags & 0xE0)) {
            battle_force_attack_miss();
        } else {
            func_80187F24();
        }
    }
}
